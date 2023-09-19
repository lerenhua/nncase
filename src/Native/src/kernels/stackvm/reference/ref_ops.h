/* This file is generated by tools/stackvm_gen/IsaGen at 2022/5/14 下午6:47:34
 * +08:00.
 *
 * Copyright 2019-2021 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include <nncase/kernels/apply.h>
#include <nncase/kernels/kernel_context.h>
#include <nncase/kernels/kernel_utils.h>
#include <nncase/runtime/datatypes.h>
#include <nncase/runtime/error.h>
#include <nncase/runtime/result.h>
#include <nncase/runtime/stackvm/opcode.h>
#include <nncase/tensor.h>
#include <nncase/value.h>

BEGIN_NS_NNCASE_KERNELS_MODULE(stackvm)
namespace reference {

NNCASE_API result<void>
batchnorm(const float *input, const float *scale, const float *bias,
          const float *input_mean, const float *input_var, float *output,
          gsl::span<const size_t> in_shape, gsl::span<const size_t> in_strides,
          gsl::span<const size_t> out_strides, float epsilon);

NNCASE_API result<void> layer_norm(const float *input, float *output,
                                   const float *scale, const float *bias,
                                   gsl::span<const size_t> in_shape,
                                   int32_t axis, float epsilon);

NNCASE_API result<void>
batch_to_space(tensor input, tensor block_shape, tensor crops,
               tensor output = nullptr,
               kernel_context &context = default_kernel_context());

NNCASE_API result<void> binary(
    typecode_t typecode, nncase::runtime::stackvm::binary_op_t op,
    const gsl::byte *lhs, const gsl::byte *rhs, gsl::byte *output,
    gsl::span<const size_t> lhs_shape, gsl::span<const size_t> lhs_strides,
    gsl::span<const size_t> rhs_shape, gsl::span<const size_t> rhs_strides,
    gsl::span<const size_t> out_shape, gsl::span<const size_t> out_strides,
    NNCASE_UNUSED kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void> broadcast(
    typecode_t typecode, const gsl::byte *input, gsl::byte *output,
    gsl::span<const size_t> input_shape, gsl::span<const size_t> input_strides,
    gsl::span<const size_t> out_shape, gsl::span<const size_t> out_strides,
    kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
cast(typecode_t new_type, tensor input, tensor output = nullptr,
     kernel_context &context = default_kernel_context());

NNCASE_API result<void>
celu(tensor input, tensor alpha, tensor output = nullptr,
     kernel_context &context = default_kernel_context());

NNCASE_API result<void> clamp(
    typecode_t type, const gsl::byte *input, const gsl::byte *min,
    const gsl::byte *max, gsl::byte *output, gsl::span<const size_t> in_shape,
    gsl::span<const size_t> in_strides, gsl::span<const size_t> out_strides,
    NNCASE_UNUSED kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void> compare_impl(
    typecode_t typecode, nncase::runtime::stackvm::compare_op_t op,
    const gsl::byte *lhs, const gsl::byte *rhs, gsl::byte *output,
    gsl::span<const size_t> lhs_shape, gsl::span<const size_t> lhs_strides,
    gsl::span<const size_t> rhs_shape, gsl::span<const size_t> rhs_strides,
    gsl::span<const size_t> out_shape, gsl::span<const size_t> out_strides,
    NNCASE_UNUSED kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
concat(datatype_t type, gsl::span<const gsl::byte *const> inputs,
       gsl::byte *output, gsl::span<const size_t> out_shape,
       gsl::span<const dims_t> in_strides, gsl::span<const size_t> out_strides,
       size_t axis, gsl::span<const size_t> concat_dims,
       kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void> constant_of_shape(datatype_t dt, const gsl::byte *value,
                                          gsl::byte *output,
                                          gsl::span<const size_t> shape);

NNCASE_API result<void> conv2d(
    const float *input, const float *weights, const float *bias, float *output,
    gsl::span<const size_t> in_shape, gsl::span<const size_t> in_strides,
    gsl::span<const size_t> w_shape, gsl::span<const size_t> w_strides,
    gsl::span<const size_t> bias_strides, gsl::span<const size_t> out_strides,
    const padding &padding_h, const padding &padding_w, int32_t groups,
    int32_t stride_h, int32_t stride_w, int32_t dilation_h, int32_t dilation_w,
    value_range<float> fused_activation,
    NNCASE_UNUSED kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
conv2d_transpose(const float *input, float *output, const float *weights,
                 const float *bias, gsl::span<const size_t> in_shape,
                 int32_t groups, gsl::span<const size_t> out_shape,
                 int32_t filter_h, int32_t filter_w, int32_t stride_h,
                 int32_t stride_w, int32_t dilation_h, int32_t dilation_w,
                 const padding &padding_h, const padding &padding_w,
                 const value_range<float> &fused_activation) noexcept;
NNCASE_API result<void>
cum_sum(tensor input, tensor axis, tensor exclusive, tensor reverse,
        tensor output = nullptr,
        kernel_context &context = default_kernel_context());

NNCASE_API result<void> dequantize(datatype_t in_type, datatype_t out_type,
                                   const gsl::byte *input, gsl::byte *output,
                                   gsl::span<const size_t> in_shape,
                                   gsl::span<const size_t> in_strides,
                                   gsl::span<const size_t> out_strides,
                                   float scale, float bias,
                                   kernel_context &context) noexcept;

NNCASE_API result<void> elu(tensor input, tensor alpha, tensor output = nullptr,
                            kernel_context &context = default_kernel_context());

NNCASE_API result<void> expand(
    typecode_t typecode, const gsl::byte *input, gsl::byte *output,
    gsl::span<const size_t> input_shape, gsl::span<const size_t> input_strides,
    gsl::span<const size_t> out_shape, gsl::span<const size_t> out_strides,
    NNCASE_UNUSED kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
flatten(tensor input, tensor axis, tensor output = nullptr,
        kernel_context &context = default_kernel_context());

NNCASE_API result<void>
gather(datatype_t type, const gsl::byte *input, gsl::byte *output,
       gsl::span<const size_t> in_shape, gsl::span<const size_t> out_shape,
       gsl::span<const size_t> in_strides, gsl::span<const size_t> out_strides,
       datatype_t indices_type, const gsl::byte *indices,
       gsl::span<const size_t> indices_shape, size_t axis,
       kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void> gather_elements(
    datatype_t type, const gsl::byte *input, gsl::byte *output,
    gsl::span<const size_t> in_shape, gsl::span<const size_t> out_shape,
    gsl::span<const size_t> in_strides, gsl::span<const size_t> out_strides,
    datatype_t indices_type, const gsl::byte *indices,
    gsl::span<const size_t> indices_shape, size_t axis,
    kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API
result<void>
gather_nd(datatype_t type, const gsl::byte *input, gsl::byte *output,
          gsl::span<const size_t> in_shape, gsl::span<const size_t> out_shape,
          gsl::span<const size_t> in_strides,
          gsl::span<const size_t> out_strides, datatype_t indices_type,
          const gsl::byte *indices, gsl::span<const size_t> indices_shape,
          size_t batch_dims,
          kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API
result<void>
scatter_nd(datatype_t type, const gsl::byte *input, gsl::byte *output,
           gsl::span<const size_t> in_shape, datatype_t indices_type,
           const gsl::byte *indices, gsl::span<const size_t> indices_shape,
           const gsl::byte *updates, gsl::span<const size_t> updates_shape,
           kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
get_item(tensor input, tensor index, tensor output = nullptr,
         kernel_context &context = default_kernel_context());

NNCASE_API result<void>
hard_sigmoid(tensor input, tensor alpha, tensor beta, tensor output = nullptr,
             kernel_context &context = default_kernel_context());

NNCASE_API result<void>
hard_swish(tensor input, tensor output = nullptr,
           kernel_context &context = default_kernel_context());

NNCASE_API result<void>
hardmax(tensor input, tensor axis, tensor output = nullptr,
        kernel_context &context = default_kernel_context());

NNCASE_API result<void> instance_norm(const float *input, const float *scale,
                                      const float *bias, float *output,
                                      gsl::span<const size_t> in_shape,
                                      gsl::span<const size_t> in_strides,
                                      gsl::span<const size_t> out_strides,
                                      float epsilon);

NNCASE_API result<void>
l2_normalization(tensor input, tensor output = nullptr,
                 kernel_context &context = default_kernel_context());

NNCASE_API result<void>
leaky_relu(tensor input, tensor alpha, tensor output = nullptr,
           kernel_context &context = default_kernel_context());

NNCASE_API result<void>
lp_normalization(tensor input, tensor axis, tensor p, tensor output = nullptr,
                 kernel_context &context = default_kernel_context());

NNCASE_API result<void> lrn(const float *input, float alpha, float beta,
                            float bias, int size, float *output,
                            gsl::span<const size_t> in_shape,
                            gsl::span<const size_t> in_strides,
                            gsl::span<const size_t> out_strides);

NNCASE_API result<void>
lstm(const float *input, const float *w_xc, const float *w_rc,
     const float *bias, const float *init_h, const float *init_c, float *output,
     float *output_h, float *output_c, gsl::span<const size_t> in_shape,
     gsl::span<const size_t> init_h_shape, gsl::span<const size_t> init_c_shape,
     gsl::span<const size_t> out_shape, gsl::span<const size_t> w_xc_shape,
     gsl::span<const size_t> w_rc_shape,
     runtime::stackvm::lstmdirection_t direction);

NNCASE_API result<void>
matmul(typecode_t typecode, const gsl::byte *input_a, const gsl::byte *input_b,
       gsl::byte *output, gsl::span<const size_t> in_a_shape,
       gsl::span<const size_t> in_b_shape,
       kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
normal(typecode_t type, tensor mean, tensor scale, tensor seed, tensor shape,
       tensor output = nullptr,
       kernel_context &context = default_kernel_context());

NNCASE_API result<void>
normal_like(typecode_t type, tensor input, tensor mean, tensor scale,
            tensor seed, tensor shape, tensor output = nullptr,
            kernel_context &context = default_kernel_context());

NNCASE_API result<void> one_hot(datatype_t type, datatype_t indices_type,
                                const gsl::byte *indices, gsl::byte *output,
                                gsl::span<const size_t> indices_shape,
                                gsl::span<const size_t> out_shape,
                                gsl::span<const size_t> out_strides,
                                size_t depth, gsl::byte *values, size_t axis,
                                runtime::stackvm::one_hot_mode_t mode,
                                kernel_context &context) noexcept;

NNCASE_API result<void>
pad(datatype_t type, const gsl::byte *input, gsl::byte *output,
    gsl::span<const size_t> in_shape, gsl::span<const size_t> in_strides,
    gsl::span<const size_t> out_strides, const paddings_t &paddings,
    runtime::stackvm::pad_mode_t mode, const gsl::byte *pad_value,
    kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
prelu(const float *input, const float *slope, float *output,
      gsl::span<const size_t> in_shape, gsl::span<const size_t> input_strides,
      gsl::span<const size_t> slope_shape,
      gsl::span<const size_t> slope_strides, gsl::span<const size_t> out_shape,
      gsl::span<const size_t> out_strides,
      kernel_context &context = default_kernel_context());

NNCASE_API result<void>
prod(tensor input, tensor output = nullptr,
     kernel_context &context = default_kernel_context());

NNCASE_API result<void>
quant_param_of(runtime::stackvm::quant_mode_t quant_mode, tensor range,
               tensor bits, tensor output = nullptr,
               kernel_context &context = default_kernel_context());

NNCASE_API result<void> quantize(datatype_t in_type, datatype_t out_type,
                                 const gsl::byte *input, gsl::byte *output,
                                 gsl::span<const size_t> in_shape,
                                 gsl::span<const size_t> in_strides,
                                 gsl::span<const size_t> out_strides,
                                 float scale, float bias,
                                 kernel_context &context) noexcept;

NNCASE_API result<void> random_normal(typecode_t type, gsl::byte *output,
                                      gsl::span<const size_t> out_shape,
                                      float mean, float std,
                                      float seed) noexcept;

NNCASE_API result<void> random_uniform(typecode_t type, gsl::byte *output,
                                       gsl::span<const size_t> out_shape,
                                       float low, float high,
                                       float seed) noexcept;

NNCASE_API result<void>
range(tensor begin, tensor end, tensor step, tensor output = nullptr,
      kernel_context &context = default_kernel_context());

NNCASE_API result<void>
range_of(tensor input, tensor output = nullptr,
         kernel_context &context = default_kernel_context());

NNCASE_API result<void>
reduce(typecode_t typecode, nncase::runtime::stackvm::reduce_op_t op,
       const gsl::byte *init_value, const gsl::byte *input, gsl::byte *output,
       gsl::span<const size_t> in_shape, gsl::span<const size_t> axis,
       gsl::span<const size_t> in_strides, gsl::span<const size_t> out_strides,
       bool keep_dims,
       kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
reduce_arg(runtime::stackvm::reduce_arg_op_t reduce_arg_op, tensor input,
           tensor axis, tensor keep_dims, tensor select_last_index,
           tensor output = nullptr,
           kernel_context &context = default_kernel_context());

NNCASE_API result<void>
reduce_window2d(runtime::stackvm::reduce_op_t reduce_op, tensor input,
                tensor init_value, tensor filter, tensor stride, tensor padding,
                tensor dilation, tensor ceil_mode, tensor count_include_pad,
                tensor output = nullptr,
                kernel_context &context = default_kernel_context());

NNCASE_API result<void>
relu(tensor input, tensor output = nullptr,
     kernel_context &context = default_kernel_context());

NNCASE_API result<void>
relu6(tensor input, tensor output = nullptr,
      kernel_context &context = default_kernel_context());

NNCASE_API result<void>
require(std::string message, tensor predicate, tensor value,
        tensor output = nullptr,
        kernel_context &context = default_kernel_context());

NNCASE_API result<void>
reshape(tensor input, tensor shape, tensor output = nullptr,
        kernel_context &context = default_kernel_context());

NNCASE_API result<void>
resize_bilinear(typecode_t type, const gsl::byte *input, gsl::byte *output,
                gsl::span<const size_t> in_shape,
                gsl::span<const size_t> in_strides,
                gsl::span<const size_t> out_strides, int32_t out_h,
                int32_t out_w, bool align_corners, bool half_pixel_centers,
                kernel_context &context) noexcept;

NNCASE_API result<void> resize_nearest_neighbor(
    typecode_t type, const gsl::byte *input, gsl::byte *output,
    gsl::span<const size_t> in_shape, gsl::span<const size_t> in_strides,
    gsl::span<const size_t> out_strides, int32_t out_h, int32_t out_w,
    bool align_corners, bool half_pixel_centers,
    get_coordinate_func_t get_coordinate_func,
    get_nearest_pixel_func_t get_nearset_func,
    kernel_context &context) noexcept;

NNCASE_API result<void> reverse_sequence(
    datatype_t dt, const gsl::byte *input, gsl::byte *output,
    gsl::span<const size_t> in_shape, gsl::span<const size_t> sequence_lens,
    int64_t batch_axis, int64_t time_axis, gsl::span<const size_t> in_strides,
    gsl::span<const size_t> out_strides,
    NNCASE_UNUSED kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
select(tensor predicate, tensor true_value, tensor false_value,
       tensor output = nullptr,
       kernel_context &context = default_kernel_context());

NNCASE_API result<void>
selu(tensor input, tensor alpha, tensor gamma, tensor output = nullptr,
     kernel_context &context = default_kernel_context());

NNCASE_API result<void>
shape_of(tensor input, tensor output = nullptr,
         kernel_context &context = default_kernel_context());

NNCASE_API result<void>
sigmoid(tensor input, tensor output = nullptr,
        kernel_context &context = default_kernel_context());

NNCASE_API result<void>
size_of(tensor input, tensor output = nullptr,
        kernel_context &context = default_kernel_context());

NNCASE_API result<void>
slice(datatype_t type, const gsl::byte *input, gsl::byte *output,
      gsl::span<const size_t> in_shape, gsl::span<const size_t> in_strides,
      gsl::span<const size_t> out_strides, const axes_t &begins,
      const axes_t &ends, const axes_t &strides,
      kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
softmax(const float *input, float *output, gsl::span<const size_t> in_shape,
        gsl::span<const size_t> in_strides, gsl::span<const size_t> out_strides,
        int64_t axis, float beta, bool needLog = false) noexcept;

NNCASE_API result<void> log_softmax(const float *input, float *output,
                                    gsl::span<const size_t> in_shape,
                                    gsl::span<const size_t> in_strides,
                                    gsl::span<const size_t> out_strides,
                                    int32_t axis) noexcept;

NNCASE_API result<void>
softplus(tensor input, tensor output = nullptr,
         kernel_context &context = default_kernel_context());

NNCASE_API result<void>
softsign(tensor input, tensor output = nullptr,
         kernel_context &context = default_kernel_context());

NNCASE_API result<void> space_to_batch(
    datatype_t dt, const gsl::byte *input, gsl::byte *output,
    gsl::span<const size_t> in_shape, gsl::span<const size_t> block_shape,
    const paddings_t &paddings, gsl::span<const size_t> in_strides,
    gsl::span<const size_t> out_shape, gsl::span<const size_t> out_strides,
    NNCASE_UNUSED kernel_context &context = default_kernel_context());

NNCASE_API
result<void> split(datatype_t type, const gsl::byte *input,
                   gsl::span<gsl::byte *> output,
                   gsl::span<const size_t> in_shape,
                   gsl::span<const size_t> in_strides,
                   gsl::span<strides_t> out_strides, size_t axis,
                   gsl::span<const size_t> sections,
                   kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
squeeze(tensor input, tensor dim, tensor output = nullptr,
        kernel_context &context = default_kernel_context());

NNCASE_API
result<void> stack(datatype_t type, gsl::span<const gsl::byte *const> inputs,
                   gsl::byte *output, gsl::span<const size_t> out_shape,
                   gsl::span<const dims_t> in_strides,
                   gsl::span<const size_t> out_strides, size_t axis,
                   kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
tile(datatype_t dt, const gsl::byte *input, gsl::byte *output,
     gsl::span<const size_t> in_shape, gsl::span<const size_t> out_shape,
     gsl::span<const size_t> in_strides, gsl::span<const size_t> out_strides,
     gsl::span<const size_t> repeats);

NNCASE_API result<void> topk(typecode_t typecode, const gsl::byte *input,
                             gsl::byte *output_values, int64_t *output_indices,
                             gsl::span<const size_t> in_shape,
                             gsl::span<const size_t> in_strides,
                             gsl::span<const size_t> output_values_shape,
                             gsl::span<const size_t> output_values_strides,
                             gsl::span<const size_t> output_indices_shape,
                             gsl::span<const size_t> output_indices_strides,
                             const int64_t k, const int32_t axis,
                             const bool largest, const bool sorted) noexcept;

NNCASE_API result<void>
transpose(datatype_t type, const gsl::byte *src, gsl::byte *dest,
          gsl::span<const size_t> in_shape, gsl::span<const size_t> perm,
          gsl::span<const size_t> in_strides,
          gsl::span<const size_t> out_strides,
          kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
trilu(datatype_t type, const gsl::byte *input, gsl::byte *output,
      gsl::span<const size_t> in_shape, gsl::span<const size_t> in_strides,
      gsl::span<const size_t> out_strides, int64_t k, bool upper) noexcept;

NNCASE_API result<void>
unary(typecode_t dtype, runtime::stackvm::unary_op_t op, const gsl::byte *input,
      gsl::byte *output, gsl::span<const size_t> input_shape,
      gsl::span<const size_t> input_strides, gsl::span<const size_t> out_shape,
      gsl::span<const size_t> out_strides,
      kernel_context &context = default_kernel_context()) noexcept;

NNCASE_API result<void>
uniform(typecode_t type, tensor high, tensor low, tensor seed, tensor shape,
        tensor output = nullptr,
        kernel_context &context = default_kernel_context());

NNCASE_API result<void>
uniform_like(typecode_t type, tensor input, tensor high, tensor low,
             tensor seed, tensor shape, tensor output = nullptr,
             kernel_context &context = default_kernel_context());

NNCASE_API result<void>
unsqueeze(tensor input, tensor dim, tensor output = nullptr,
          kernel_context &context = default_kernel_context());

NNCASE_API result<void>
where(datatype_t dt, const bool *cond, const gsl::byte *x, const gsl::byte *y,
      gsl::byte *output, gsl::span<const size_t> cond_shape,
      gsl::span<const size_t> x_shape, gsl::span<const size_t> y_shape,
      gsl::span<const size_t> out_shape, gsl::span<const size_t> cond_strides,
      gsl::span<const size_t> x_strides, gsl::span<const size_t> y_strides,
      gsl::span<const size_t> out_strides);
} // namespace reference
END_NS_NNCASE_KERNELS_MODULE
