/* This file is generated by tools/stackvm_gen/IsaGen at 2/16/2022 4:18:59 PM +08:00.
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
#include <nncase/codegen/stackvm/op_writer.h>

using namespace nncase;
using namespace nncase::codegen;
using namespace nncase::codegen::stackvm;
using namespace nncase::runtime;
using namespace nncase::runtime::stackvm;

op_builder::op_builder(ir::node &node, section_writer &writer)
    : writer_(writer)
{
    writer.add_symbol(node.name());
}

void op_builder::nop_()
{
    op_writer<nop_op_t>()(nop_op_t(), writer_);
}

void op_builder::br_(int32_t target)
{
    op_writer<br_op_t>()(br_op_t(target), writer_);
}

void op_builder::br_true_(int32_t target)
{
    op_writer<br_true_op_t>()(br_true_op_t(target), writer_);
}

void op_builder::br_false_(int32_t target)
{
    op_writer<br_false_op_t>()(br_false_op_t(target), writer_);
}

void op_builder::ret_()
{
    op_writer<ret_op_t>()(ret_op_t(), writer_);
}

void op_builder::call_(uint8_t args, int32_t target)
{
    op_writer<call_op_t>()(call_op_t(args, target), writer_);
}

void op_builder::ecall_(uint8_t args)
{
    op_writer<ecall_op_t>()(ecall_op_t(args), writer_);
}

void op_builder::throw_()
{
    op_writer<throw_op_t>()(throw_op_t(), writer_);
}

void op_builder::break_()
{
    op_writer<break_op_t>()(break_op_t(), writer_);
}

void op_builder::ldc_i4_(int32_t imm)
{
    op_writer<ldc_i4_op_t>()(ldc_i4_op_t(imm), writer_);
}

void op_builder::ldnull_()
{
    op_writer<ldnull_op_t>()(ldnull_op_t(), writer_);
}

void op_builder::ldc_i4_0_()
{
    op_writer<ldc_i4_0_op_t>()(ldc_i4_0_op_t(), writer_);
}

void op_builder::ldc_i4_1_()
{
    op_writer<ldc_i4_1_op_t>()(ldc_i4_1_op_t(), writer_);
}

void op_builder::ldc_r4_(float imm)
{
    op_writer<ldc_r4_op_t>()(ldc_r4_op_t(imm), writer_);
}

void op_builder::ldind_i1_()
{
    op_writer<ldind_i1_op_t>()(ldind_i1_op_t(), writer_);
}

void op_builder::ldind_i2_()
{
    op_writer<ldind_i2_op_t>()(ldind_i2_op_t(), writer_);
}

void op_builder::ldind_i4_()
{
    op_writer<ldind_i4_op_t>()(ldind_i4_op_t(), writer_);
}

void op_builder::ldind_i_()
{
    op_writer<ldind_i_op_t>()(ldind_i_op_t(), writer_);
}

void op_builder::ldind_u1_()
{
    op_writer<ldind_u1_op_t>()(ldind_u1_op_t(), writer_);
}

void op_builder::ldind_u2_()
{
    op_writer<ldind_u2_op_t>()(ldind_u2_op_t(), writer_);
}

void op_builder::ldind_u4_()
{
    op_writer<ldind_u4_op_t>()(ldind_u4_op_t(), writer_);
}

void op_builder::ldind_u_()
{
    op_writer<ldind_u_op_t>()(ldind_u_op_t(), writer_);
}

void op_builder::ldind_br2_()
{
    op_writer<ldind_br2_op_t>()(ldind_br2_op_t(), writer_);
}

void op_builder::ldind_r4_()
{
    op_writer<ldind_r4_op_t>()(ldind_r4_op_t(), writer_);
}

void op_builder::stind_i1_()
{
    op_writer<stind_i1_op_t>()(stind_i1_op_t(), writer_);
}

void op_builder::stind_i2_()
{
    op_writer<stind_i2_op_t>()(stind_i2_op_t(), writer_);
}

void op_builder::stind_i4_()
{
    op_writer<stind_i4_op_t>()(stind_i4_op_t(), writer_);
}

void op_builder::stind_i_()
{
    op_writer<stind_i_op_t>()(stind_i_op_t(), writer_);
}

void op_builder::stind_br2_()
{
    op_writer<stind_br2_op_t>()(stind_br2_op_t(), writer_);
}

void op_builder::stind_r4_()
{
    op_writer<stind_r4_op_t>()(stind_r4_op_t(), writer_);
}

void op_builder::lea_gp_(uint8_t gpid, int32_t offset)
{
    op_writer<lea_gp_op_t>()(lea_gp_op_t(gpid, offset), writer_);
}

void op_builder::lea_buffer_(memory_location_t location, uint8_t subres_id, uint32_t offset)
{
    op_writer<lea_buffer_op_t>()(lea_buffer_op_t(location, subres_id, offset), writer_);
}

void op_builder::ldelem_i1_()
{
    op_writer<ldelem_i1_op_t>()(ldelem_i1_op_t(), writer_);
}

void op_builder::ldelem_i2_()
{
    op_writer<ldelem_i2_op_t>()(ldelem_i2_op_t(), writer_);
}

void op_builder::ldelem_i4_()
{
    op_writer<ldelem_i4_op_t>()(ldelem_i4_op_t(), writer_);
}

void op_builder::ldelem_i_()
{
    op_writer<ldelem_i_op_t>()(ldelem_i_op_t(), writer_);
}

void op_builder::ldelem_u1_()
{
    op_writer<ldelem_u1_op_t>()(ldelem_u1_op_t(), writer_);
}

void op_builder::ldelem_u2_()
{
    op_writer<ldelem_u2_op_t>()(ldelem_u2_op_t(), writer_);
}

void op_builder::ldelem_u4_()
{
    op_writer<ldelem_u4_op_t>()(ldelem_u4_op_t(), writer_);
}

void op_builder::ldelem_u_()
{
    op_writer<ldelem_u_op_t>()(ldelem_u_op_t(), writer_);
}

void op_builder::ldelem_br2_()
{
    op_writer<ldelem_br2_op_t>()(ldelem_br2_op_t(), writer_);
}

void op_builder::ldelem_r4_()
{
    op_writer<ldelem_r4_op_t>()(ldelem_r4_op_t(), writer_);
}

void op_builder::stelem_i1_()
{
    op_writer<stelem_i1_op_t>()(stelem_i1_op_t(), writer_);
}

void op_builder::stelem_i2_()
{
    op_writer<stelem_i2_op_t>()(stelem_i2_op_t(), writer_);
}

void op_builder::stelem_i4_()
{
    op_writer<stelem_i4_op_t>()(stelem_i4_op_t(), writer_);
}

void op_builder::stelem_i_()
{
    op_writer<stelem_i_op_t>()(stelem_i_op_t(), writer_);
}

void op_builder::stelem_br2_()
{
    op_writer<stelem_br2_op_t>()(stelem_br2_op_t(), writer_);
}

void op_builder::stelem_r4_()
{
    op_writer<stelem_r4_op_t>()(stelem_r4_op_t(), writer_);
}

void op_builder::ldarg_(uint32_t index)
{
    op_writer<ldarg_op_t>()(ldarg_op_t(index), writer_);
}

void op_builder::ldarg_0_()
{
    op_writer<ldarg_0_op_t>()(ldarg_0_op_t(), writer_);
}

void op_builder::ldarg_1_()
{
    op_writer<ldarg_1_op_t>()(ldarg_1_op_t(), writer_);
}

void op_builder::ldarg_2_()
{
    op_writer<ldarg_2_op_t>()(ldarg_2_op_t(), writer_);
}

void op_builder::ldarg_3_()
{
    op_writer<ldarg_3_op_t>()(ldarg_3_op_t(), writer_);
}

void op_builder::ldarg_4_()
{
    op_writer<ldarg_4_op_t>()(ldarg_4_op_t(), writer_);
}

void op_builder::ldarg_5_()
{
    op_writer<ldarg_5_op_t>()(ldarg_5_op_t(), writer_);
}

void op_builder::stshape_(uint8_t rshape, uint8_t rank)
{
    op_writer<stshape_op_t>()(stshape_op_t(rshape, rank), writer_);
}

void op_builder::stpaddings_(uint8_t rpaddings, uint8_t rank)
{
    op_writer<stpaddings_op_t>()(stpaddings_op_t(rpaddings, rank), writer_);
}

void op_builder::dup_()
{
    op_writer<dup_op_t>()(dup_op_t(), writer_);
}

void op_builder::pop_()
{
    op_writer<pop_op_t>()(pop_op_t(), writer_);
}

void op_builder::neg_()
{
    op_writer<neg_op_t>()(neg_op_t(), writer_);
}

void op_builder::add_()
{
    op_writer<add_op_t>()(add_op_t(), writer_);
}

void op_builder::sub_()
{
    op_writer<sub_op_t>()(sub_op_t(), writer_);
}

void op_builder::mul_()
{
    op_writer<mul_op_t>()(mul_op_t(), writer_);
}

void op_builder::div_()
{
    op_writer<div_op_t>()(div_op_t(), writer_);
}

void op_builder::div_u_()
{
    op_writer<div_u_op_t>()(div_u_op_t(), writer_);
}

void op_builder::rem_()
{
    op_writer<rem_op_t>()(rem_op_t(), writer_);
}

void op_builder::rem_u_()
{
    op_writer<rem_u_op_t>()(rem_u_op_t(), writer_);
}

void op_builder::and_()
{
    op_writer<and_op_t>()(and_op_t(), writer_);
}

void op_builder::or_()
{
    op_writer<or_op_t>()(or_op_t(), writer_);
}

void op_builder::xor_()
{
    op_writer<xor_op_t>()(xor_op_t(), writer_);
}

void op_builder::not_()
{
    op_writer<not_op_t>()(not_op_t(), writer_);
}

void op_builder::shl_()
{
    op_writer<shl_op_t>()(shl_op_t(), writer_);
}

void op_builder::shr_()
{
    op_writer<shr_op_t>()(shr_op_t(), writer_);
}

void op_builder::shr_u_()
{
    op_writer<shr_u_op_t>()(shr_u_op_t(), writer_);
}

void op_builder::clt_()
{
    op_writer<clt_op_t>()(clt_op_t(), writer_);
}

void op_builder::clt_u_()
{
    op_writer<clt_u_op_t>()(clt_u_op_t(), writer_);
}

void op_builder::cle_()
{
    op_writer<cle_op_t>()(cle_op_t(), writer_);
}

void op_builder::cle_u_()
{
    op_writer<cle_u_op_t>()(cle_u_op_t(), writer_);
}

void op_builder::ceq_()
{
    op_writer<ceq_op_t>()(ceq_op_t(), writer_);
}

void op_builder::cge_()
{
    op_writer<cge_op_t>()(cge_op_t(), writer_);
}

void op_builder::cge_u_()
{
    op_writer<cge_u_op_t>()(cge_u_op_t(), writer_);
}

void op_builder::cgt_()
{
    op_writer<cgt_op_t>()(cgt_op_t(), writer_);
}

void op_builder::cgt_u_()
{
    op_writer<cgt_u_op_t>()(cgt_u_op_t(), writer_);
}

void op_builder::cne_()
{
    op_writer<cne_op_t>()(cne_op_t(), writer_);
}

void op_builder::conv_i1_()
{
    op_writer<conv_i1_op_t>()(conv_i1_op_t(), writer_);
}

void op_builder::conv_i2_()
{
    op_writer<conv_i2_op_t>()(conv_i2_op_t(), writer_);
}

void op_builder::conv_i4_()
{
    op_writer<conv_i4_op_t>()(conv_i4_op_t(), writer_);
}

void op_builder::conv_i_()
{
    op_writer<conv_i_op_t>()(conv_i_op_t(), writer_);
}

void op_builder::conv_u1_()
{
    op_writer<conv_u1_op_t>()(conv_u1_op_t(), writer_);
}

void op_builder::conv_u2_()
{
    op_writer<conv_u2_op_t>()(conv_u2_op_t(), writer_);
}

void op_builder::conv_u4_()
{
    op_writer<conv_u4_op_t>()(conv_u4_op_t(), writer_);
}

void op_builder::conv_u_()
{
    op_writer<conv_u_op_t>()(conv_u_op_t(), writer_);
}

void op_builder::conv_br2_()
{
    op_writer<conv_br2_op_t>()(conv_br2_op_t(), writer_);
}

void op_builder::conv_r4_()
{
    op_writer<conv_r4_op_t>()(conv_r4_op_t(), writer_);
}

void op_builder::tensor_batch_to_space_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, uint8_t rshape_block, uint8_t rpad_crops)
{
    op_writer<tensor_batch_to_space_op_t>()(tensor_batch_to_space_op_t(datatype, rshape_src, rstride_src, rstride_dest, rshape_block, rpad_crops), writer_);
}

void op_builder::tensor_broadcast_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rshape_dest, uint8_t rstride_dest)
{
    op_writer<tensor_broadcast_op_t>()(tensor_broadcast_op_t(datatype, rshape_src, rstride_src, rshape_dest, rstride_dest), writer_);
}

void op_builder::tensor_binary_(datatype_t datatype, uint8_t rshape_src1, uint8_t rstride_src1, uint8_t rshape_src2, uint8_t rstride_src2, uint8_t rshape_dest, uint8_t rstride_dest, binary_op_t binary_op, float fused_clamp_low, float fused_clamp_high)
{
    op_writer<tensor_binary_op_t>()(tensor_binary_op_t(datatype, rshape_src1, rstride_src1, rshape_src2, rstride_src2, rshape_dest, rstride_dest, binary_op, fused_clamp_low, fused_clamp_high), writer_);
}

void op_builder::tensor_call_(uint32_t function_id, uint16_t module_id, uint8_t num_src, uint8_t num_dst)
{
    op_writer<tensor_call_op_t>()(tensor_call_op_t(function_id, module_id, num_src, num_dst), writer_);
}

void op_builder::tensor_conv2d_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rshape_kernel, uint8_t rstride_kernel, uint8_t rstride_bias, uint8_t rstride_dest, uint16_t groups, uint16_t stride_h, uint16_t stride_w, uint16_t dilation_h, uint16_t dilation_w, float fused_clamp_low, float fused_clamp_high)
{
    op_writer<tensor_conv2d_op_t>()(tensor_conv2d_op_t(datatype, rshape_src, rstride_src, rshape_kernel, rstride_kernel, rstride_bias, rstride_dest, groups, stride_h, stride_w, dilation_h, dilation_w, fused_clamp_low, fused_clamp_high), writer_);
}

void op_builder::tensor_copy_(datatype_t datatype, uint8_t rshape, uint8_t rstride_src, uint8_t rstride_dest)
{
    op_writer<tensor_copy_op_t>()(tensor_copy_op_t(datatype, rshape, rstride_src, rstride_dest), writer_);
}

void op_builder::tensor_convert_(datatype_t in_datatype, datatype_t dst_datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest)
{
    op_writer<tensor_convert_op_t>()(tensor_convert_op_t(in_datatype, dst_datatype, rshape_src, rstride_src, rstride_dest), writer_);
}

void op_builder::tensor_cumsum_(datatype_t datatype, uint8_t rshape_src, int32_t axis, bool exclusive, bool reverse)
{
    op_writer<tensor_cumsum_op_t>()(tensor_cumsum_op_t(datatype, rshape_src, axis, exclusive, reverse), writer_);
}

void op_builder::tensor_dequantize_(datatype_t in_datatype, datatype_t dst_datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest)
{
    op_writer<tensor_dequantize_op_t>()(tensor_dequantize_op_t(in_datatype, dst_datatype, rshape_src, rstride_src, rstride_dest), writer_);
}

void op_builder::tensor_equal_(datatype_t datatype, uint8_t rshape_src1, uint8_t rstride_src1, uint8_t rshape_src2, uint8_t rstride_src2, uint8_t rstride_dest)
{
    op_writer<tensor_equal_op_t>()(tensor_equal_op_t(datatype, rshape_src1, rstride_src1, rshape_src2, rstride_src2, rstride_dest), writer_);
}

void op_builder::tensor_gather_(datatype_t datatype, uint8_t rshape_src, uint8_t rshape_dest, uint8_t rstride_src, uint8_t rstride_dest, uint8_t rshape_indices, uint8_t axis)
{
    op_writer<tensor_gather_op_t>()(tensor_gather_op_t(datatype, rshape_src, rshape_dest, rstride_src, rstride_dest, rshape_indices, axis), writer_);
}

void op_builder::tensor_gather_nd_(datatype_t datatype, uint8_t rshape_src, uint8_t rshape_dest, uint8_t rstride_src, uint8_t rstride_dest, uint8_t rshape_indices, uint8_t batch_dims)
{
    op_writer<tensor_gather_nd_op_t>()(tensor_gather_nd_op_t(datatype, rshape_src, rshape_dest, rstride_src, rstride_dest, rshape_indices, batch_dims), writer_);
}

void op_builder::tensor_hardmax_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, int32_t axis)
{
    op_writer<tensor_hardmax_op_t>()(tensor_hardmax_op_t(datatype, rshape_src, rstride_src, axis), writer_);
}

void op_builder::tensor_lut1d_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, uint16_t table_len)
{
    op_writer<tensor_lut1d_op_t>()(tensor_lut1d_op_t(datatype, rshape_src, rstride_src, rstride_dest, table_len), writer_);
}

void op_builder::tensor_matmul_(uint8_t rshape_src1, uint8_t rstride_src1, uint8_t rshape_src2, uint8_t rstride_src2, uint8_t rshape_dest, uint8_t rstride_dest, float fused_clamp_low, float fused_clamp_high)
{
    op_writer<tensor_matmul_op_t>()(tensor_matmul_op_t(rshape_src1, rstride_src1, rshape_src2, rstride_src2, rshape_dest, rstride_dest, fused_clamp_low, fused_clamp_high), writer_);
}

void op_builder::tensor_onehot_(datatype_t datatype, uint8_t rshape_indices, uint8_t rshape_dest, uint8_t rstride_dest, uint8_t axis, onehot_mode_t onehot_mode)
{
    op_writer<tensor_onehot_op_t>()(tensor_onehot_op_t(datatype, rshape_indices, rshape_dest, rstride_dest, axis, onehot_mode), writer_);
}

void op_builder::tensor_pad_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, uint8_t rpaddings, pad_mode_t pad_mode)
{
    op_writer<tensor_pad_op_t>()(tensor_pad_op_t(datatype, rshape_src, rstride_src, rstride_dest, rpaddings, pad_mode), writer_);
}

void op_builder::tensor_quantize_(datatype_t in_datatype, datatype_t dst_datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest)
{
    op_writer<tensor_quantize_op_t>()(tensor_quantize_op_t(in_datatype, dst_datatype, rshape_src, rstride_src, rstride_dest), writer_);
}

void op_builder::tensor_random_normal_(datatype_t datatype_dest, uint8_t rshape_dest, float mean, float std, float seed)
{
    op_writer<tensor_random_normal_op_t>()(tensor_random_normal_op_t(datatype_dest, rshape_dest, mean, std, seed), writer_);
}

void op_builder::tensor_random_uniform_(datatype_t datatype_dest, uint8_t rshape_dest, float low, float high, float seed)
{
    op_writer<tensor_random_uniform_op_t>()(tensor_random_uniform_op_t(datatype_dest, rshape_dest, low, high, seed), writer_);
}

void op_builder::tensor_reduce_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, reduce_op_t reduce_op, uint8_t rshape_axis, bool keep_dims)
{
    op_writer<tensor_reduce_op_t>()(tensor_reduce_op_t(datatype, rshape_src, rstride_src, rstride_dest, reduce_op, rshape_axis, keep_dims), writer_);
}

void op_builder::tensor_reduce_arg_(datatype_t datatype_src, uint8_t rshape_src, uint8_t rstride_src, datatype_t datatype_dest, uint8_t rstride_dest, reduce_arg_op_t reduce_arg_op, uint8_t rshape_axis, bool keep_dims, bool select_last_idx)
{
    op_writer<tensor_reduce_arg_op_t>()(tensor_reduce_arg_op_t(datatype_src, rshape_src, rstride_src, datatype_dest, rstride_dest, reduce_arg_op, rshape_axis, keep_dims, select_last_idx), writer_);
}

void op_builder::tensor_reduce_prod_(uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, uint8_t rshape_axes, bool keep_dims)
{
    op_writer<tensor_reduce_prod_op_t>()(tensor_reduce_prod_op_t(rshape_src, rstride_src, rstride_dest, rshape_axes, keep_dims), writer_);
}

void op_builder::tensor_reduce_window2d_(datatype_t datatype, reduce_op_t reduce_op, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, uint16_t filter_h, uint16_t filter_w, uint16_t stride_h, uint16_t stride_w, uint16_t dilation_h, uint16_t dilation_w, float fused_clamp_low, float fused_clamp_high)
{
    op_writer<tensor_reduce_window2d_op_t>()(tensor_reduce_window2d_op_t(datatype, reduce_op, rshape_src, rstride_src, rstride_dest, filter_h, filter_w, stride_h, stride_w, dilation_h, dilation_w, fused_clamp_low, fused_clamp_high), writer_);
}

void op_builder::tensor_resize_image_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, bool align_corners, bool half_pixel_centers, image_resize_mode_t image_resize_mode)
{
    op_writer<tensor_resize_image_op_t>()(tensor_resize_image_op_t(datatype, rshape_src, rstride_src, rstride_dest, align_corners, half_pixel_centers, image_resize_mode), writer_);
}

void op_builder::tensor_roi_align_(datatype_t datatype, uint8_t rshape_src, uint8_t rshape_dest, roi_align_mode_t mode, float spatial_scale, int64_t sampling_ratio)
{
    op_writer<tensor_roi_align_op_t>()(tensor_roi_align_op_t(datatype, rshape_src, rshape_dest, mode, spatial_scale, sampling_ratio), writer_);
}

void op_builder::tensor_sigmoid_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest)
{
    op_writer<tensor_sigmoid_op_t>()(tensor_sigmoid_op_t(datatype, rshape_src, rstride_src, rstride_dest), writer_);
}

void op_builder::tensor_slice_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, uint8_t rbegins, uint8_t rends, uint8_t rstrides)
{
    op_writer<tensor_slice_op_t>()(tensor_slice_op_t(datatype, rshape_src, rstride_src, rstride_dest, rbegins, rends, rstrides), writer_);
}

void op_builder::tensor_ternary_(datatype_t datatype, uint8_t rshape_src1, uint8_t rstride_src1, uint8_t rshape_src2, uint8_t rstride_src2, uint8_t rshape_src3, uint8_t rstride_src3, uint8_t rstride_dest)
{
    op_writer<tensor_ternary_op_t>()(tensor_ternary_op_t(datatype, rshape_src1, rstride_src1, rshape_src2, rstride_src2, rshape_src3, rstride_src3, rstride_dest), writer_);
}

void op_builder::tensor_topk_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rshape_dest1, uint8_t rstride_dest1, uint8_t rshape_dest2, uint8_t rstride_dest2, int64_t k, int32_t axis, bool largest, bool sorted)
{
    op_writer<tensor_topk_op_t>()(tensor_topk_op_t(datatype, rshape_src, rstride_src, rshape_dest1, rstride_dest1, rshape_dest2, rstride_dest2, k, axis, largest, sorted), writer_);
}

void op_builder::tensor_trilu_(datatype_t datatype, uint8_t rshape_src, bool upper, int64_t k)
{
    op_writer<tensor_trilu_op_t>()(tensor_trilu_op_t(datatype, rshape_src, upper, k), writer_);
}

void op_builder::tensor_unary_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, unary_op_t unary_op)
{
    op_writer<tensor_unary_op_t>()(tensor_unary_op_t(datatype, rshape_src, rstride_src, rstride_dest, unary_op), writer_);
}

void op_builder::tensor_transpose_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, uint8_t rshape_perm)
{
    op_writer<tensor_transpose_op_t>()(tensor_transpose_op_t(datatype, rshape_src, rstride_src, rstride_dest, rshape_perm), writer_);
}
