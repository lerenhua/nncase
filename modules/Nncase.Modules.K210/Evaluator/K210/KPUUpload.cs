﻿using System;
using System.Collections.Generic;
using System.Linq;
using NetFabric.Hyperlinq;
using Nncase.CostModel;
using Nncase.IR;
using Nncase.IR.K210;
using OrtKISharp;
using static Nncase.Evaluator.EvaluatorUtil;

using System;
using Nncase.CostModel;
using Nncase.IR;
using Nncase.IR.K210;
using OrtKISharp;

namespace Nncase.Evaluator.K210;

/// <summary>
/// Evaluator for <see cref="KPUUpload"/>.
/// </summary>
internal sealed class KPUUploadEvaluator : IEvaluator<KPUUpload>, ITypeInferencer<KPUUpload>
{
    /// <inheritdoc/>
    public IValue Visit(IEvaluateContext context, KPUUpload target)
    {
        var input = context.GetArgumentValue(target, KPUUpload.Input);
        return input;
    }

    /// <inheritdoc/>
    public IRType Visit(ITypeInferenceContext context, KPUUpload target)
    {
        var input = context.CheckArgumentType<TensorType>(target, KPUUpload.Input);
        return Visit(target, input);
    }

    private IRType Visit(KPUUpload target, TensorType input)
    {
        return input;
    }
}