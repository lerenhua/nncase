/* This file is generated by tools/stackvm_gen/IsaGen at 2021/2/4 22:42:55 +08:00.
 *
 * Copyright 2020 Canaan Inc.
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

void op_builder::tensor_batch_to_space_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, uint8_t rshape_block, uint8_t rpaddings)
{
    op_writer<tensor_batch_to_space_op_t>()(tensor_batch_to_space_op_t(datatype, rshape_src, rstride_src, rstride_dest, rshape_block, rpaddings), writer_);
}

void op_builder::tensor_conv2d_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rshape_kernel, uint8_t rstride_kernel, uint8_t rstride_bias, uint8_t rstride_dest, uint16_t groups, uint16_t stride_h, uint16_t stride_w, uint16_t dilation_h, uint16_t dilation_w, float fused_clamp_low, float fused_clamp_high)
{
    op_writer<tensor_conv2d_op_t>()(tensor_conv2d_op_t(datatype, rshape_src, rstride_src, rshape_kernel, rstride_kernel, rstride_bias, rstride_dest, groups, stride_h, stride_w, dilation_h, dilation_w, fused_clamp_low, fused_clamp_high), writer_);
}

void op_builder::tensor_reduce_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, reduce_op_t reduce_op, uint8_t rshape_axis, bool keep_dims)
{
    op_writer<tensor_reduce_op_t>()(tensor_reduce_op_t(datatype, rshape_src, rstride_src, rstride_dest, reduce_op, rshape_axis, keep_dims), writer_);
}

void op_builder::tensor_binary_(datatype_t datatype, uint8_t rshape_src1, uint8_t rstride_src1, uint8_t rshape_src2, uint8_t rstride_src2, uint8_t rstride_dest, binary_op_t binary_op, float fused_clamp_low, float fused_clamp_high)
{
    op_writer<tensor_binary_op_t>()(tensor_binary_op_t(datatype, rshape_src1, rstride_src1, rshape_src2, rstride_src2, rstride_dest, binary_op, fused_clamp_low, fused_clamp_high), writer_);
}

void op_builder::tensor_unary_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, unary_op_t unary_op)
{
    op_writer<tensor_unary_op_t>()(tensor_unary_op_t(datatype, rshape_src, rstride_src, rstride_dest, unary_op), writer_);
}

void op_builder::tensor_transpose_(datatype_t datatype, uint8_t rshape_src, uint8_t rstride_src, uint8_t rstride_dest, uint8_t rshape_perm)
{
    op_writer<tensor_transpose_op_t>()(tensor_transpose_op_t(datatype, rshape_src, rstride_src, rstride_dest, rshape_perm), writer_);
}

