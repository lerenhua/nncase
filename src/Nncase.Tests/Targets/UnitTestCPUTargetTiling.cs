﻿// Copyright (c) Canaan Inc. All rights reserved.
// Licensed under the Apache license. See LICENSE file in the project root for full license information.

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Extensions.DependencyInjection;
using Nncase.CodeGen;
using Nncase.IR;
using Nncase.IR.Tensors;
using Nncase.Runtime.Interop;
using Nncase.Targets;
using Nncase.Tests.TestFixture;
using Nncase.Utilities;
using Xunit;
using static Nncase.IR.F.Tensors;
using GetItem = Nncase.IR.Tensors.GetItem;

namespace Nncase.Tests.Targets;

[AutoSetupTestMethod(InitSession = true)]
public class UnitTestCPUTargetTiling : TestClassBase
{
    public UnitTestCPUTargetTiling()
    {
        DefaultTargetName = CPUTarget.Kind;
#if DEBUG
        CompileOptions.DumpFlags = Diagnostics.DumpFlags.PassIR | Diagnostics.DumpFlags.Rewrite | Diagnostics.DumpFlags.CodeGen | Diagnostics.DumpFlags.EGraphCost | Diagnostics.DumpFlags.Tiling;
#endif
    }

    [Theory]

    // [ClassData(typeof(TilingCaseMHA))]
    [ClassData(typeof(TilingCaseBinaryMul))]
    [ClassData(typeof(TilingCaseUnary))]
    [ClassData(typeof(TilingCaseMatmul))]
    [ClassData(typeof(TilingCaseMatmulUnary))]
    public async Task TestCpuFunction(Function main, Tensor[] inputs)
    {
        var module = new IR.IRModule(main);
        using (var _ = new Diagnostics.DumpScope(main.Name, CompileOptions.DumpFlags))
        {
            await Compile(module);
            var output = Testing.RunKModel(File.ReadAllBytes(Path.Join(Diagnostics.DumpScope.Current.Directory, "test.kmodel")), Diagnostics.DumpScope.Current.Directory, inputs);
            var cos = Tests.Comparator.CosSimilarity(output, Value.FromTensor(inputs[^1]))[0];
            Assert.True(cos > 0.999);
        }
    }

    private async Task Compile(IRModule module)
    {
        var compiler = CompileSession.Compiler;
        compiler.ImportIRModule(module);
        await compiler.CompileAsync();
        using (var fs = Diagnostics.DumpScope.Current.OpenFile("test.kmodel"))
        {
            compiler.Gencode(fs);
        }
    }
}

internal sealed class TilingCaseMHA : TheoryData<Function>
{
    public TilingCaseMHA()
    {
        var hid_in = new Var("hidden_in", new TensorType(DataTypes.Float32, new[] { 1, 384, 8192 }));
        var pos_ids = new Var("position_ids", new TensorType(DataTypes.Int64, new[] { 1, 384 }));

        Fusion fusion;
        {
            var scale = IR.F.Tensors.ConstantOfShape(new[] { 8192 }, 1.0f).Evaluate().AsTensor();
            var bias = IR.F.Tensors.ConstantOfShape(new[] { 8192 }, 0.0f).Evaluate().AsTensor();
            var weights = IR.F.Random.Normal(DataTypes.Float32, new[] { 1, 64, 8192, 128 }).Evaluate().AsTensor();
            var gdata = IR.F.Random.Normal(DataTypes.Float32, new[] { 384, 128 }).Evaluate().AsTensor();

            var fin = new Var("input", new TensorType(DataTypes.Float32, new[] { 1, 384, 8192 }));
            var fin2 = new Var("input2", new TensorType(DataTypes.Int64, new[] { 1, 384 }));
            var v0 = new Call(new IR.CPU.CPUKernelOp(new IR.NN.LayerNorm(2, 1e-6f, false)), fin, scale, bias);
            var v1 = new Call(new IR.CPU.CPUKernelOp(new IR.Tensors.Unsqueeze()), v0, new[] { 0 });
            var v2 = new Call(new IR.CPU.CPUKernelOp(new IR.Math.MatMul()), v1, weights);
            var v3 = new Call(new IR.CPU.CPUKernelOp(new IR.Tensors.Slice()), v2, new[] { 64 }, new[] { 128 }, new[] { 3 }, new[] { 1 });
            var v4 = new Call(new IR.CPU.CPUKernelOp(new IR.Math.Unary(UnaryOp.Neg)), v3);
            var v5 = new Call(new IR.CPU.CPUKernelOp(new IR.Tensors.Slice()), v2, new[] { 0 }, new[] { 64 }, new[] { 3 }, new[] { 1 });
            var v6 = new Call(new IR.CPU.CPUKernelOp(new IR.Tensors.Concat(3)), new IR.Tuple(v4, v5));

            var v7 = new Call(new IR.CPU.CPUKernelOp(new IR.Tensors.Gather(0)), gdata, fin2);
            var v8 = new Call(new IR.CPU.CPUKernelOp(new IR.Tensors.Unsqueeze()), v7, new[] { 0 });

            var v9 = new Call(new IR.CPU.CPUKernelOp(new IR.Math.Binary(BinaryOp.Mul)), v2, v8);
            var v10 = new Call(new IR.CPU.CPUKernelOp(new IR.Math.Binary(BinaryOp.Mul)), v6, v8);
            var v11 = new Call(new IR.CPU.CPUKernelOp(new IR.Math.Binary(BinaryOp.Add)), v9, v10);

            fusion = new Fusion("cpu", v11, fin, fin2);
        }

        var main = new Function("mha_qk", new Call(fusion, hid_in, pos_ids), new[] { hid_in, pos_ids });
        Add(main);
    }
}

internal sealed class TilingCaseBinaryMul : TheoryData<Function, Tensor[]>
{
    public TilingCaseBinaryMul()
    {
        var lhsShape = new[] { 1, 64, 384, 128 };
        var lhs = new Var("lhs", new TensorType(DataTypes.Float32, lhsShape));
        var rhsShape = new[] { 1, 1, 384, 128 };
        var rhs = new Var("lhs", new TensorType(DataTypes.Float32, rhsShape));
        var main = new Function("binary_mul", lhs * rhs, new[] { lhs, rhs });

        var lhs_tensor = IR.F.Random.Normal(DataTypes.Float32, 0, 1, 2, lhsShape).Evaluate().AsTensor();
        using (var fs = Diagnostics.DumpScope.Current.OpenFile("input_0.bin"))
        {
            fs.Write(lhs_tensor.BytesBuffer);
        }

        var rhs_tensor = IR.F.Random.Normal(DataTypes.Float32, 0, 1, 2, rhsShape).Evaluate().AsTensor();
        using (var fs = Diagnostics.DumpScope.Current.OpenFile("input_1.bin"))
        {
            fs.Write(rhs_tensor.BytesBuffer);
        }

        var feedDict = new Dictionary<Var, IValue>
        {
            { lhs, Value.FromTensor(lhs_tensor) },
            { rhs, Value.FromTensor(rhs_tensor) },
        };
        var output = main.Body.Evaluate(feedDict).AsTensor();

        Add(main, new[] { lhs_tensor, rhs_tensor, output });
    }
}

internal sealed class TilingCaseUnary : TheoryData<Function, Tensor[]>
{
    public TilingCaseUnary()
    {
        var shape = new[] { 1, 384, 2048 };
        var input = new Var("input", new TensorType(DataTypes.Float32, shape));
        var main = new Function("unary", IR.F.Math.Unary(UnaryOp.Asin, input), new[] { input });

        var input_tensor = IR.F.Random.Normal(DataTypes.Float32, 0, 1, 2, shape).Evaluate().AsTensor();
        using (var fs = Diagnostics.DumpScope.Current.OpenFile("input_0.bin"))
        {
            fs.Write(input_tensor.BytesBuffer);
        }

        var feedDict = new Dictionary<Var, IValue>
        {
            { input, Value.FromTensor(input_tensor) },
        };
        var output = main.Body.Evaluate(feedDict).AsTensor();

        Add(main, new[] { input_tensor, output });
    }
}

internal sealed class TilingCaseMatmul : TheoryData<Function, Tensor[]>
{
    public TilingCaseMatmul()
    {
        var lhsShape = new[] { 1, 64, 384, 8192 };
        var lhs = new Var("lhs", new TensorType(DataTypes.Float32, lhsShape));
        var rhsShape = new[] { 1, 64, 8192, 128 };
        var rhs = IR.F.Random.Normal(DataTypes.Float32, 0, 1, 0, rhsShape).Evaluate().AsTensor().Cast<float>();

        var main = new Function("matmul", IR.F.Math.MatMul(lhs, rhs), new[] { lhs });

        var lhs_tensor = IR.F.Random.Normal(DataTypes.Float32, 0, 1, 2, lhsShape).Evaluate().AsTensor();
        using (var fs = Diagnostics.DumpScope.Current.OpenFile("input_0.bin"))
        {
            fs.Write(lhs_tensor.BytesBuffer);
        }

        var feedDict = new Dictionary<Var, IValue>
        {
            { lhs, Value.FromTensor(lhs_tensor) },
        };
        var output = main.Body.Evaluate(feedDict).AsTensor();

        Add(main, new[] { lhs_tensor, output });
    }
}

internal sealed class TilingCaseMatmulUnary : TheoryData<Function, Tensor[]>
{
    public TilingCaseMatmulUnary()
    {
        var lhsShape = new[] { 1, 64, 384, 8192 };
        var lhs = new Var("lhs", new TensorType(DataTypes.Float32, lhsShape));
        var rhsShape = new[] { 1, 64, 8192, 128 };
        var rhs = IR.F.Random.Normal(DataTypes.Float32, 0, 1, 0, rhsShape).Evaluate().AsTensor().Cast<float>();
        Fusion fusion;
        Var fin;
        {
            fin = new Var("input", new TensorType(DataTypes.Float32, lhsShape));
            var v0 = new Call(new IR.CPU.CPUKernelOp(new IR.Math.MatMul()), fin, rhs);
            var v1 = new Call(new IR.CPU.CPUKernelOp(new IR.Math.Unary(UnaryOp.Neg)), v0);
            fusion = new Fusion("cpu", v1, fin);
        }

        var main = new Function("matmul_unary", new Call(fusion, lhs), new[] { lhs });

        var lhs_tensor = IR.F.Random.Normal(DataTypes.Float32, 0, 1, 2, lhsShape).Evaluate().AsTensor();
        using (var fs = Diagnostics.DumpScope.Current.OpenFile("input_0.bin"))
        {
            fs.Write(lhs_tensor.BytesBuffer);
        }

        var feedDict = new Dictionary<Var, IValue>
        {
            { fin, Value.FromTensor(lhs_tensor) },
        };
        var output = fusion.Body.Evaluate(feedDict).AsTensor();

        Add(main, new[] { lhs_tensor, output });
    }
}
