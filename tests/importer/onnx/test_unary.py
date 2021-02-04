# Copyright 2019-2021 Canaan Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""System test: test unary"""
# pylint: disable=invalid-name, unused-argument, import-outside-toplevel
import pytest
import os
import torch
import numpy as np
import sys
import test_util


def _make_module():
    class UnaryModule(torch.nn.Module):
        def __init__(self):
            super(UnaryModule, self).__init__()

        def forward(self, x):
            outs = []
            outs.append(torch.abs(-x))
            outs.append(torch.ceil(x))
            outs.append(torch.cos(x))
            outs.append(torch.exp(x))
            outs.append(torch.floor(x))
            outs.append(torch.log(x))
            outs.append(torch.negative(x))
            outs.append(torch.round(x))
            outs.append(torch.rsqrt(x))
            outs.append(torch.sin(x))
            outs.append(torch.sqrt(x))
            outs.append(torch.square(x))
            outs.append(torch.tanh(x))
            outs.append(torch.sigmoid(x))
            return outs
    return UnaryModule()

in_shapes = [
    [3],
    [64, 3],
    [3, 64, 3],
    [8, 6, 16, 3]
]

@pytest.mark.parametrize('in_shape', in_shapes)
def test_unary(in_shape, request):
    module = _make_module()
    test_util.torch_module_to_onnx(request.node.name, module, in_shape)


if __name__ == "__main__":
    pytest.main(['-vv', 'test_unary.py'])
