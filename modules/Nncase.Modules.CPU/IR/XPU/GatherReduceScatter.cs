﻿// Copyright (c) Canaan Inc. All rights reserved.
// Licensed under the Apache license. See LICENSE file in the project root for full license information.

namespace Nncase.IR.XPU;

public sealed partial class GatherReduceScatter : XPUKernelOp
{
    public static readonly ParameterInfo Input = new(typeof(GatherReduceScatter), 0, "input");

    public static readonly ParameterInfo Output = new(typeof(GatherReduceScatter), 1, "output");

    public IRArray<(int Hierarchy, SBP SBP)> ReducePosition { get; }

    public Placement Placement { get; }
}
