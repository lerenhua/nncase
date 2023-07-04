﻿// Copyright (c) Canaan Inc. All rights reserved.
// Licensed under the Apache license. See LICENSE file in the project root for full license information.

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Nncase.Diagnostics;
using Nncase.IR;
using Nncase.IR.Tensors;
using Nncase.Passes;
using Nncase.Passes.Rules.Neutral;
using Nncase.Quantization;
using Nncase.Tests.TestFixture;
using Nncase.Tests.TransformTest;
using Nncase.Utilities;
using Xunit;
using Xunit.Abstractions;
using static Nncase.IR.F.Math;
using static Nncase.IR.F.NN;
using static Nncase.IR.F.Tensors;

namespace Nncase.Tests.Rules;

[AutoSetupTestMethod(InitSession = true)]
public class ShapeBucketTest : TransformTestBase
{
    [Fact]
    public void TestFindVar()
    {
        var v1 = new Var(new TensorType(DataTypes.Int32, Shape.Scalar));
        var v2 = new Var(new TensorType(DataTypes.Int32, Shape.Scalar));
        var expr = ((v1 * 4) + (v2 * 3)) * 2;
        var visitor = new FindVar();
        visitor.Visit(expr);
        Assert.Equal(visitor.Vars, new HashSet<Var>(new[] { v1, v2 }));
    }

    [Fact]
    public void TestBucketPad()
    {
        var input = Testing.Rand<float>(1, 2, 16, 16);
        var fixedShape = new[] { 1, 3, 24, 24 };
        var p = new Call(new BucketPad(), input, fixedShape);
        var (_, kmodel) = Testing.BuildKModel("test", new IRModule(new Function(p)), CompileSession);
        var result = Testing.RunKModel(kmodel, "call_arg", Array.Empty<Tensor>());
        var pads = fixedShape - Cast(ShapeOf(input), DataTypes.Int32);
        var paddings = Transpose(
            Stack(new IR.Tuple(Enumerable.Repeat(0, fixedShape.Length).ToArray(), pads), 0),
            new[] { 1, 0 });
        var fixedInput = IR.F.NN.Pad(input, paddings, PadMode.Constant, Cast(0, input.ElementType));
        var fixedResult = new Call(new FixShape(), fixedInput, fixedShape);
        var origin = fixedResult.Evaluate();
        var cos = Comparator.CosSimilarity(origin, result)[0];
        Assert.True(cos > 0.999);
    }

    private Var Scalar(string name) => new Var(new TensorType(DataTypes.Int32, Shape.Scalar));
}

[AutoSetupTestMethod(InitSession = true)]
public class TestMergePrevCallToFusion : TransformTestBase
{
    [Fact]
    public void TestMergePrevCallSingleInput()
    {
        var input = Testing.Rand<float>(1, 3, 24, 24);
        var inputVar = new Var(new TensorType(input.ElementType, input.Shape));
        var transpose = Transpose(inputVar, new[] { 3, 2, 1, 0 });
        var v = new Var(transpose.CheckedType);
        var abs = Abs(v);
        var f = new BucketFusion("stackvm", abs, new[] { v }, new Var[] { });
        var c = new Call(f, transpose);
        TestMatched<MergePrevCallToFusion>(c, new Dictionary<Var, IValue> { { inputVar, Value.FromTensor(input) } });
    }

    [Fact]
    public void TestBodyMultiInputMergeLeft()
    {
        var mainInput0 = Testing.Rand<float>(1, 3, 24, 24);
        var mainInput1 = Testing.Rand<float>(1, 3, 24, 24);
        var mainVar0 = new Var(new TensorType(mainInput0.ElementType, mainInput0.Shape));
        var mainVar1 = new Var(new TensorType(mainInput0.ElementType, mainInput0.Shape));
        var fusionVar0 = new Var(new TensorType(mainInput0.ElementType, mainInput0.Shape));
        var fusionVar1 = new Var(new TensorType(mainInput1.ElementType, mainInput1.Shape));
        var concat = Concat(new IR.Tuple(fusionVar0, fusionVar1), 0);
        var f = new BucketFusion("stackvm", concat, new[] { fusionVar0, fusionVar1 }, new Var[] { });
        var abs = Abs(mainVar0);
        var c = new Call(f, abs, mainVar1);
        TestMatched<MergePrevCallToFusion>(c,
            new Dictionary<Var, IValue>
            {
                { mainVar0, Value.FromTensor(mainInput0) }, { mainVar1, Value.FromTensor(mainInput1) },
            });
    }

    [Fact]
    public void TestBodyMultiInputMergeRight()
    {
        var mainInput0 = Testing.Rand<float>(1, 3, 24, 24);
        var mainInput1 = Testing.Rand<float>(1, 3, 24, 24);
        var mainVar0 = new Var(new TensorType(mainInput0.ElementType, mainInput0.Shape));
        var mainVar1 = new Var(new TensorType(mainInput0.ElementType, mainInput0.Shape));
        var fusionVar0 = new Var(new TensorType(mainInput0.ElementType, mainInput0.Shape));
        var fusionVar1 = new Var(new TensorType(mainInput1.ElementType, mainInput1.Shape));
        var concat = Concat(new IR.Tuple(fusionVar0, fusionVar1), 0);
        var f = new BucketFusion("stackvm", concat, new[] { fusionVar0, fusionVar1 }, new Var[] { });
        var abs = Abs(mainVar1);
        var c = new Call(f, Softmax(mainInput0, 0), abs);
        TestMatched<MergePrevCallToFusion>(c,
            new Dictionary<Var, IValue>
            {
                { mainVar0, Value.FromTensor(mainInput0) }, { mainVar1, Value.FromTensor(mainInput1) },
            });
    }

    [Fact]
    public void TestPrevMultiInputForDynamicReshape()
    {
        // fusion
        var fusionVar = new Var(new TensorType(DataTypes.Float32, new[] { 1, 3, 24, 24 }));
        var transpose = Transpose(fusionVar, new[] { 3, 2, 1, 0 });
        var f = new BucketFusion("stackvm", transpose, new[] { fusionVar }, new Var[] { });

        // input
        var input = Testing.Rand<float>(3, 24, 24);
        var inputVar = new Var(new TensorType(input.ElementType, input.Shape));
        var newShape = Concat(new IR.Tuple(new[] { 1L }, ShapeOf(inputVar)), 0);
        var reshape = Reshape(Abs(inputVar), newShape);
        var c = new Call(f, reshape);
        TestMatched<MergePrevCallToFusion>(c, new Dictionary<Var, IValue> { { inputVar, Value.FromTensor(input) } });
    }

    [Fact]
    public void TestForMergeConcat()
    {
        var input0 = Testing.Rand<float>(1, 3, 24, 24);
        var input1 = Testing.Rand<float>(1, 3, 24, 24);
        var inputVar0 = new Var(new TensorType(input0.ElementType, input0.Shape));
        var inputVar1 = new Var(new TensorType(input1.ElementType, input1.Shape));
        var concat = Concat(new IR.Tuple(inputVar0, inputVar1), 0);
        var v = new Var(concat.CheckedType);
        var abs = Abs(v);
        var f = new BucketFusion("stackvm", abs, new[] { v }, new Var[] { });
        var c = new Call(f, concat);
        TestMatched<MergePrevCallToFusion>(c,
            new Dictionary<Var, IValue>
            {
                { inputVar0, Value.FromTensor(input0) }, { inputVar1, Value.FromTensor(input1) }
            });
    }

    [Fact]
    public void TestMatMulAndConcat()
    {
        var lhs = new Var(new TensorType(DataTypes.Float32, new[] { 1, 3, 24, 24 }));
        var rhs = new Var(new TensorType(DataTypes.Float32, new[] { 2, 3, 24, 24 }));
        var mm = IR.F.Math.MatMul(lhs, rhs);
        var f = new BucketFusion("stackvm", mm, new[] { lhs, rhs }, new Var[] { });

        var input0 = Testing.Rand<float>(1, 3, 24, 24);
        var input1 = Testing.Rand<float>(1, 3, 24, 24);
        var input2 = Testing.Rand<float>(1, 3, 24, 24);
        var inputVar0 = new Var(new TensorType(input0.ElementType, input0.Shape));
        var inputVar1 = new Var(new TensorType(input1.ElementType, input1.Shape));
        var inputVar2 = new Var(new TensorType(input2.ElementType, input2.Shape));
        var concat = Concat(new IR.Tuple(inputVar1, inputVar2), 0);
        var c = new Call(f, Softmax(inputVar0, 0), concat);
        TestMatched<MergePrevCallToFusion>(c,
            new Dictionary<Var, IValue>
            {
                { inputVar0, Value.FromTensor(input0) },
                { inputVar1, Value.FromTensor(input1) },
                { inputVar2, Value.FromTensor(input2) },
            });
    }

    [Fact]
    public void TestAfterMergeSameInput()
    {
        var input = Testing.Rand<float>(1, 3, 24, 24);
        var inputVar = new Var(new TensorType(input.ElementType, input.Shape));
        var abs = Abs(inputVar);

        var fusionVar0 = new Var(new TensorType(input.ElementType, input.Shape));
        var fusionVar1 = new Var(new TensorType(input.ElementType, input.Shape));
        var concat = Concat(new IR.Tuple(fusionVar0, fusionVar1), 0);
        var f = new BucketFusion("stackvm", concat, new Var[] { fusionVar0, fusionVar1 }, new Var[] { });
        var c = new Call(f, Sqrt(abs), Neg(abs));
        TestMatched<MergePrevCallToFusion>(c, new Dictionary<Var, IValue> { { inputVar, Value.FromTensor(input) } });
    }

    [Fact]
    public void TestMatMulReshape()
    {
        // 左边的表达式是右边表达式的一部分
        // 重新构造prev的call,使用新的var来替换，因此在替换%0的时候，ShapeOf()的参数也变成了var，但实际上ShapeOf的参数应当还是原始的
        // %0 = Add(BinaryOp.Add, %var_88: f32[1,3,24,24], const(f32[1] : {1f})) 2 -1378211376: // f32[1,3,24,24]
        // %1 = ShapeOf(%0) 1 2067123334: // i64[4]
        // %2 = Gather(%1, const(i64 : 0), const(i64 : 0)) 1 805902410: // i64
        // %3 = Reshape(%2, const(i64[1] : {1L})) 1 -466610003: // i64[1]
        // %4 = (%3, const(i64[1] : {3L}), const(i64[1] : {24L}), const(i64[1] : {24L})): // (i64[1], i64[1], i64[1], i64[1])
        //
        // %5 = Concat(%4, const(i32 : 0)) 1 80776753: // i64[4]
        // %6 = Reshape(%0, %5) 2 -1638748643: // f32[?,?,?,?]
        // %7 = (%6): // (f32[?,?,?,?])

        var input = Testing.Rand<float>(1, 3, 24, 24);
        var lhs = new Var(new TensorType(input.ElementType, input.Shape));
        var add = Add(lhs, new[] { 1f });
        var rhs = Reshape(add, Concat(
            new IR.Tuple(Reshape(Gather(ShapeOf(add), 0L, 0L), new[] { 1L }), new[]{3L}, new[]{24L}, new[]{24L}), 0));

        var lhsVar = new Var(new TensorType(input.ElementType, input.Shape));
        var rhsVar = new Var(new TensorType(input.ElementType, input.Shape));
        var mm = IR.F.Math.MatMul(lhsVar, rhsVar);
        var f = new BucketFusion("stackvm", mm, new Var[] { lhsVar, rhsVar }, new Var[] { });
        var c = new Call(f, lhs, rhs);
        TestMatched<MergePrevCallToFusion>(c, new Dictionary<Var, IValue> { { lhs, Value.FromTensor(input) } });
    }

    [Fact]
    public void TestMergeStackWithConstant()
    {
        var input0 = Testing.Rand<float>(1, 3, 24, 24);
        var input1 = Testing.Rand<float>(1, 3, 24, 24);
        var lhs = new Var(new TensorType(input0.ElementType, input0.Shape));
        var rhs = new Var(new TensorType(input1.ElementType, input1.Shape));

        var scalarInput = Testing.Rand<float>();
        var scalarInputVar = new Var(new TensorType(scalarInput.ElementType, scalarInput.Shape));
        var other = Stack(new IR.Tuple(scalarInputVar, 1f, 2f), 0);

        var lhsVar = new Var(new TensorType(input0.ElementType, input0.Shape));
        var rhsVar = new Var(new TensorType(input1.ElementType, input1.Shape));
        var otherVar = new Var(new TensorType(other.CheckedDataType, other.CheckedShape));
        var mm = IR.F.Math.MatMul(lhsVar, rhsVar);
        var f = new BucketFusion("stackvm", mm * otherVar[1], new Var[] { lhsVar, rhsVar, otherVar }, new Var[] { });
        var c = new Call(f, lhs, rhs, other);
        var result = TestMatched<MergePrevCallToFusion>(c, new Dictionary<Var, IValue>
        {
            { lhs, Value.FromTensor(input0) },
            { rhs, Value.FromTensor(input1) },
            { scalarInputVar, Value.FromTensor(scalarInput) },
        });
        var fusion = (BucketFusion)((Call)result).Target;
        // constant should not be var
        Assert.Equal(3, fusion.Parameters.Length);
    }
}
