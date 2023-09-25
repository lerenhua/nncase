﻿// Copyright (c) Canaan Inc. All rights reserved.
// Licensed under the Apache license. See LICENSE file in the project root for full license information.

using System.Reactive;
using System.Runtime.CompilerServices;
using Nncase.IR;
using Nncase.IR.CPU;
using Nncase.IR.Tensors;

[assembly: InternalsVisibleTo("Nncase.Tests")]

namespace Nncase.Passes.Tile;

internal sealed class AutoDistributedConvertVisitor : ExprVisitor<Dictionary<IRType, List<Expr>>, Unit>
{
    public AutoDistributedConvertVisitor(TileOptions tileOptions)
    {
        TileOptions = tileOptions;
        Placement = new Placement(Placement.DeviceKind.CPU, tileOptions.Hierarchy, "bt");
    }

    public TileOptions TileOptions { get; }

    public Placement Placement { get; }

    public static IReadOnlyList<Expr> GetLeafCandidateBoxings(Expr expr, Placement placement)
    {
        return Utilities.DistributedUtility.GetLeafCandidateNDSBPs((TensorType)expr.CheckedType, placement).
            Select(ndsbp => IR.F.CPU.Boxing(expr, new DistributedType((TensorType)expr.CheckedType, ndsbp, placement))).
            ToArray();
    }

    public Expr Convert(Expr body)
    {
        var equivalents = Visit(body).Select(g => IR.F.CPU.Boxing(g.Value[0], body.CheckedType)).ToArray();
        using (new ExprPinner(equivalents))
        {
            BranchCut();
        }

        var graph = new EGraph();
        foreach (var (exprKey, buckets) in ExprMemo.Where(kv => kv.Key is not Op))
        {
            foreach (var (typeKey, bucket) in buckets.Where(kv => kv.Value.Any()))
            {
                Unions(graph, bucket);
            }
        }

        var root = Unions(graph, equivalents);
        return graph.Extract(root, null, out _);
    }

    protected override Dictionary<IRType, List<Expr>> DefaultVisitLeaf(Expr expr)
    {
        return new();
    }

    protected override Dictionary<IRType, List<Expr>> VisitLeafTuple(IR.Tuple expr)
    {
        return expr.Fields.ToArray().
                Select(Visit).
                CartesianProduct().
                Select(e => new IR.Tuple(e.Select(e => e.Value[0]).ToArray())).
                GroupBy(tp => tp.CheckedType).
                ToDictionary(g => g.Key, g => g.ToList<Expr>());
    }

    protected override Dictionary<IRType, List<Expr>> VisitLeafCall(Call expr)
    {
        if (expr.Target is not Op op)
        {
            throw new NotSupportedException("not support auto distributed call function");
        }

        foreach (var param in op.Parameters)
        {
            VisitLeafArgument(param.ParameterKind, expr.Arguments[param.Index]);
        }

        return expr.Arguments.ToArray().
                    Select(Visit).
                    CartesianProduct().
                    Select(args => args.ToArray()).
                    Select(args => BuildEquivalCalls(op, args.Select(kv => kv.Value[0]).ToArray()).ToArray()).
                    SelectMany(i => i).
                    GroupBy(c => c.CheckedType).
                    ToDictionary(g => g.Key, g => new List<Expr>(g.ToList<Expr>()));
    }

    private Dictionary<IRType, List<Expr>> VisitLeafArgument(ParameterKind parameterKind, Expr expr)
    {
        var updateBuckets = (Dictionary<IRType, List<Expr>> buckets, IEnumerable<Expr> equivalents) =>
        {
            foreach (var eq in equivalents)
            {
                if (!buckets.TryGetValue(eq.CheckedType, out var bucket))
                {
                    bucket = new();
                    buckets.Add(eq.CheckedType, bucket);
                }

                bucket.Add(eq);
            }
        };

        var buckets = ExprMemo[expr];
        if (!buckets.Any())
        {
            switch (parameterKind, expr)
            {
                case (ParameterKind.Input, Expr e) when e is Const or Var:
                    updateBuckets(buckets, GetLeafCandidateBoxings(e, Placement));
                    break;
                case (ParameterKind.Input, Expr e) when e is IR.Tuple tp:
                    foreach (var f in tp.Fields)
                    {
                        VisitLeafArgument(parameterKind, f);
                    }

                    foreach (var (k, v) in VisitLeafTuple(tp))
                    {
                        buckets.Add(k, v);
                    }

                    break;
                case (ParameterKind.Attribute, Var e):
                    updateBuckets(buckets, new[] { e });
                    break;
                case (ParameterKind.Attribute, TensorConst e):
                    updateBuckets(buckets, new[] { e.With() }); // remove all old users.
                    break;
                default:
                    throw new InvalidOperationException();
            }
        }

        return buckets;
    }

    private IEnumerable<Call> BuildEquivalCalls(Op target, Expr[] args)
    {
        if (!target.Parameters.Where(p => p.ParameterKind == ParameterKind.Input).All(p => IsDistributed(args[p.Index].CheckedType)))
        {
            throw new InvalidDataException();
        }

        var calls = new List<Call>();
        var call = new Call(target, args);
        var valid = call.InferenceType();
        if (!valid)
        {
            // 1. dispose current call
            using var pinner = new ExprPinner(args);
            call.Dispose();

            if (target is CPUKernelOp { Target: Reshape } || target is Reshape)
            {
                // the reshape need force boxing.
                var newShape = ((TensorConst)args[1]).Value.ToArray<int>();
                var inType = (DistributedType)args[0].CheckedType;
                var tensorType = inType.TensorType with { Shape = newShape };
                foreach (var boxing in Utilities.DistributedUtility.GetLeafCandidateNDSBPs(tensorType, inType.Placement).
                    Select(ndsbp => IR.F.CPU.Boxing(args[0], new DistributedType(tensorType, ndsbp, inType.Placement))))
                {
                    if (boxing.CheckedType is InvalidType)
                    {
                        boxing.Dispose();
                    }
                    else
                    {
                        calls.Add(boxing);
                    }
                }
            }
            else
            {
                // todo expand search space.
                // calls.AddRange(Utilities.DistributedUtility.GetLeafCandidateNDSBPs(tensorType, inType.Placement).
                // Select(ndsbp => IR.F.CPU.Boxing(args[0], new DistributedType(tensorType, ndsbp, inType.Placement))));
            }
        }
        else
        {
            calls.Add(call);
            if (call.CheckedType is DistributedType distributedType)
            {
                calls.AddRange(Utilities.DistributedUtility.GetPartialCandidateNDSBPs(distributedType).
                    Select(ndsbp => IR.F.CPU.Boxing(call, distributedType with { NdSBP = ndsbp })));
            }
        }

        return calls;
    }

    private IReadOnlyList<Expr> GetReBoxings(Expr expr)
    {
        if (expr is IR.Tuple tuple)
        {
            var candidates = tuple.Fields.ToArray().
                Select(GetReBoxings).
                CartesianProduct();
            return candidates.Any() ? candidates.
                Select(fs => new IR.Tuple(fs.ToArray())).
                ToArray() : Array.Empty<Expr>();
        }

        var type = (DistributedType)expr.CheckedType;
        var tensorType = type.TensorType;
        var candidateNdsbps = new List<SBP>[type.Placement.Rank];
        for (int i = 0; i < type.Placement.Rank; i++)
        {
            candidateNdsbps[i] = new List<SBP> { SBP.B };
            for (int axis = 0; axis < tensorType.Shape.Rank; axis++)
            {
                if (tensorType.Shape[axis] is { IsFixed: true, Value: int s } && Utilities.DistributedUtility.IsDivisible(s, type.Placement.Hierarchy[i]))
                {
                    candidateNdsbps[i].Add(SBP.S(axis));
                }
            }
        }

        return candidateNdsbps.CartesianProduct().
            Select(ndsbp => new IRArray<SBP>(ndsbp)).
            Where(ndsbp => ndsbp != type.NdSBP).
            Select(ndsbp => new DistributedType(tensorType, new IRArray<SBP>(ndsbp), type.Placement)).
            Select(disttype => IR.F.CPU.Boxing(expr, disttype)).ToArray();
    }

    private bool IsDistributed(IRType type) => type switch
    {
        DistributedType => true,
        TupleType t => t.All(IsDistributed),
        _ => false,
    };

    private EClass Unions(EGraph graph, IEnumerable<Expr> equivalents)
    {
        var eids = equivalents.Select(graph.Add).ToArray();
        foreach (var cls in eids.Skip(1))
        {
            graph.Union(eids[0], cls);
        }

        graph.Rebuild();
        return eids[0];
    }

    private void BranchCut()
    {
        bool changed = true;
        while (changed)
        {
            changed = false;
            foreach (var (_, bukets) in ExprMemo)
            {
                foreach (var (_, buket) in bukets.Where(kv => kv.Value.Any()))
                {
                    if (!buket[0].Users.Any())
                    {
                        foreach (var item in buket)
                        {
                            using (new ExprPinner(item.Operands.ToArray()))
                            {
                                item.Dispose();
                            }
                        }

                        buket.Clear();
                        changed = true;
                    }
                }
            }
        }
    }
}
