/* This file is generated by tools/stackvm_gen/IsaGen at 2023/6/20 14:21:49
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
#include "../datatypes.h"
#include <vector>

BEGIN_NS_NNCASE_RT_MODULE(stackvm)

// Enums

enum class opcode_t : uint8_t {
    NOP = 0,
    LDNULL = 1,
    LDC_I4 = 2,
    LDC_I4_0 = 3,
    LDC_I4_1 = 4,
    LDC_R4 = 5,
    LDIND_I1 = 6,
    LDIND_I2 = 7,
    LDIND_I4 = 8,
    LDIND_I = 9,
    LDIND_U1 = 10,
    LDIND_U2 = 11,
    LDIND_U4 = 12,
    LDIND_U = 13,
    LDIND_BR2 = 14,
    LDIND_R4 = 15,
    STIND_I1 = 16,
    STIND_I2 = 17,
    STIND_I4 = 18,
    STIND_I = 19,
    STIND_BR2 = 20,
    STIND_R4 = 21,
    LEA_GP = 22,
    LDELEM_I1 = 23,
    LDELEM_I2 = 24,
    LDELEM_I4 = 25,
    LDELEM_I = 26,
    LDELEM_U1 = 27,
    LDELEM_U2 = 28,
    LDELEM_U4 = 29,
    LDELEM_U = 30,
    LDELEM_BR2 = 31,
    LDELEM_R4 = 32,
    STELEM_I1 = 33,
    STELEM_I2 = 34,
    STELEM_I4 = 35,
    STELEM_I = 36,
    STELEM_BR2 = 37,
    STELEM_R4 = 38,
    LDARG = 39,
    LDARG_0 = 40,
    LDARG_1 = 41,
    LDARG_2 = 42,
    LDARG_3 = 43,
    LDARG_4 = 44,
    LDARG_5 = 45,
    DUP = 46,
    POP = 47,
    LDLOCAL = 48,
    STLOCAL = 49,
    LDTUPLE_ELEM = 50,
    LDTUPLE = 51,
    LDDATATYPE = 52,
    LDTENSOR = 53,
    LDSCALAR = 54,
    NEG = 55,
    ADD = 56,
    SUB = 57,
    MUL = 58,
    DIV = 59,
    DIV_U = 60,
    REM = 61,
    REM_U = 62,
    AND = 63,
    OR = 64,
    XOR = 65,
    NOT = 66,
    SHL = 67,
    SHR = 68,
    SHR_U = 69,
    CLT = 70,
    CLT_U = 71,
    CLE = 72,
    CLE_U = 73,
    CEQ = 74,
    CGE = 75,
    CGE_U = 76,
    CGT = 77,
    CGT_U = 78,
    CNE = 79,
    CONV_I1 = 80,
    CONV_I2 = 81,
    CONV_I4 = 82,
    CONV_I = 83,
    CONV_U1 = 84,
    CONV_U2 = 85,
    CONV_U4 = 86,
    CONV_U = 87,
    CONV_BR2 = 88,
    CONV_R4 = 89,
    BR = 90,
    BR_TRUE = 91,
    BR_FALSE = 92,
    RET = 93,
    CALL = 94,
    ECALL = 95,
    EXTCALL = 96,
    CUSCALL = 97,
    THROW = 98,
    BREAK = 99,
    TENSOR = 100,
};

enum class tensor_function_t : uint16_t {
    batch_normalization = 0,
    batch_to_space = 1,
    celu = 7,
    conv2d = 13,
    conv2d_transpose = 14,
    elu = 17,
    erf = 18,
    gelu = 27,
    hardmax = 29,
    hard_sigmoid = 30,
    hard_swish = 31,
    instance_normalization = 33,
    l2_normalization = 34,
    layer_norm = 35,
    leaky_relu = 36,
    log_softmax = 37,
    lp_normalization = 38,
    lrn = 39,
    one_hot = 44,
    pad = 45,
    prelu = 46,
    reduce_window2d = 55,
    relu = 56,
    relu6 = 57,
    selu = 64,
    sigmoid = 66,
    softmax = 69,
    softplus = 70,
    softsign = 71,
    space_to_batch = 72,
    swish = 76,
    binary = 2,
    clamp = 8,
    compare = 9,
    condition = 11,
    cum_sum = 15,
    dequantize = 16,
    fake_dequantize = 20,
    fake_quantize = 21,
    mat_mul = 41,
    quantize = 48,
    quant_param_of = 49,
    range_of = 51,
    reduce = 53,
    reduce_arg = 54,
    require = 58,
    select = 63,
    unary = 80,
    bitcast = 3,
    broadcast = 4,
    bucket_pad = 5,
    cast = 6,
    concat = 10,
    constant_of_shape = 12,
    expand = 19,
    fix_shape = 22,
    flatten = 23,
    gather = 24,
    gather_elements = 25,
    gather_nd = 26,
    get_item = 28,
    index_of = 32,
    lstm = 40,
    prod = 47,
    range = 50,
    rank = 52,
    reshape = 59,
    reverse_sequence = 61,
    scatter_nd = 62,
    shape_of = 65,
    size_of = 67,
    slice = 68,
    split = 73,
    squeeze = 74,
    stack = 75,
    tile = 77,
    top_k = 78,
    transpose = 79,
    unsqueeze = 83,
    where = 84,
    normal = 42,
    normal_like = 43,
    uniform = 81,
    uniform_like = 82,
    resize_image = 60,
};

enum class binary_op_t : uint8_t {
    add = 0,
    sub = 1,
    mul = 2,
    div = 3,
    mod = 4,
    min = 5,
    max = 6,
    pow = 7,
    bitwise_and = 8,
    bitwise_or = 9,
    bitwise_xor = 10,
    logical_and = 11,
    logical_or = 12,
    logical_xor = 13,
    left_shift = 14,
    right_shift = 15,
};

enum class cast_mode_t : int32_t {
    kdefault = 0,
    exact = 1,
    check_overflow = 2,
    reinterpret = 3,
};

enum class compare_op_t : uint8_t {
    equal = 0,
    not_equal = 1,
    lower_than = 2,
    lower_or_equal = 3,
    greater_than = 4,
    greater_or_equal = 5,
};

enum class pad_mode_t : uint8_t {
    constant = 0,
    reflect = 1,
    symmetric = 2,
    edge = 3,
};

enum class lstmdirection_t : int32_t {
    forward = 0,
    reverse = 1,
    bidirectional = 2,
};

enum class lstmlayout_t : int32_t {
    zero = 0,
    one = 1,
};

enum class one_hot_mode_t : uint8_t {
    normal = 0,
    process_neg = 1,
};

enum class quant_mode_t : int32_t {
    unsigned_mode = 0,
    signed_symmetric_mode = 1,
    signed_asymmetric_mode = 2,
};

enum class reduce_op_t : uint8_t {
    mean = 0,
    min = 1,
    max = 2,
    sum = 3,
    prod = 4,
};

enum class reduce_arg_op_t : uint8_t {
    arg_min = 0,
    arg_max = 1,
};

enum class image_resize_mode_t : uint8_t {
    bilinear = 0,
    nearest_neighbor = 1,
};

enum class image_resize_transformation_mode_t : int32_t {
    half_pixel = 0,
    pytorch_half_pixel = 1,
    align_corners = 2,
    asymmetric = 3,
    tfcrop_and_resize = 4,
};

enum class image_resize_nearest_mode_t : int32_t {
    round_prefer_floor = 0,
    round_prefer_ceil = 1,
    floor = 2,
    ceil = 3,
};

enum class unary_op_t : uint8_t {
    abs = 0,
    acos = 1,
    acosh = 2,
    asin = 3,
    asinh = 4,
    ceil = 5,
    cos = 6,
    cosh = 7,
    exp = 8,
    floor = 9,
    log = 10,
    neg = 11,
    round = 12,
    rsqrt = 13,
    sin = 14,
    sinh = 15,
    sign = 16,
    sqrt = 17,
    square = 18,
    tanh = 19,
    bitwise_not = 20,
    logical_not = 21,
};

// Instructions

struct nop_op_t {};

struct br_op_t {
    int32_t target;
};

struct br_true_op_t {
    int32_t target;
};

struct br_false_op_t {
    int32_t target;
};

struct ret_op_t {};

struct call_op_t {
    uint16_t args;
    int32_t target;
};

struct ecall_op_t {
    uint16_t args;
};

struct extcall_op_t {
    uint16_t args;
    bool is_prim_func;
};

struct cuscall_op_t {
    std::string registered_name;
    gsl::span<const gsl::byte> fields_span;
    uint16_t args;
};

struct throw_op_t {};

struct break_op_t {};

struct ldc_i4_op_t {
    int32_t imm;
};

struct ldnull_op_t {};

struct ldc_i4_0_op_t {};

struct ldc_i4_1_op_t {};

struct ldc_r4_op_t {
    float imm;
};

struct ldind_i1_op_t {};

struct ldind_i2_op_t {};

struct ldind_i4_op_t {};

struct ldind_i_op_t {};

struct ldind_u1_op_t {};

struct ldind_u2_op_t {};

struct ldind_u4_op_t {};

struct ldind_u_op_t {};

struct ldind_br2_op_t {};

struct ldind_r4_op_t {};

struct stind_i1_op_t {};

struct stind_i2_op_t {};

struct stind_i4_op_t {};

struct stind_i_op_t {};

struct stind_br2_op_t {};

struct stind_r4_op_t {};

struct lea_gp_op_t {
    uint8_t gpid;
    int32_t offset;
};

struct ldelem_i1_op_t {};

struct ldelem_i2_op_t {};

struct ldelem_i4_op_t {};

struct ldelem_i_op_t {};

struct ldelem_u1_op_t {};

struct ldelem_u2_op_t {};

struct ldelem_u4_op_t {};

struct ldelem_u_op_t {};

struct ldelem_br2_op_t {};

struct ldelem_r4_op_t {};

struct stelem_i1_op_t {};

struct stelem_i2_op_t {};

struct stelem_i4_op_t {};

struct stelem_i_op_t {};

struct stelem_br2_op_t {};

struct stelem_r4_op_t {};

struct ldarg_op_t {
    uint16_t index;
};

struct ldarg_0_op_t {};

struct ldarg_1_op_t {};

struct ldarg_2_op_t {};

struct ldarg_3_op_t {};

struct ldarg_4_op_t {};

struct ldarg_5_op_t {};

struct ldtuple_elem_op_t {};

struct ldtuple_op_t {};

struct lddatatype_op_t {};

struct ldtensor_op_t {};

struct ldlocal_op_t {
    uint16_t index;
};

struct stlocal_op_t {
    uint16_t index;
};

struct ldscalar_op_t {};

struct dup_op_t {};

struct pop_op_t {};

struct neg_op_t {};

struct add_op_t {};

struct sub_op_t {};

struct mul_op_t {};

struct div_op_t {};

struct div_u_op_t {};

struct rem_op_t {};

struct rem_u_op_t {};

struct and_op_t {};

struct or_op_t {};

struct xor_op_t {};

struct not_op_t {};

struct shl_op_t {};

struct shr_op_t {};

struct shr_u_op_t {};

struct clt_op_t {};

struct clt_u_op_t {};

struct cle_op_t {};

struct cle_u_op_t {};

struct ceq_op_t {};

struct cge_op_t {};

struct cge_u_op_t {};

struct cgt_op_t {};

struct cgt_u_op_t {};

struct cne_op_t {};

struct conv_i1_op_t {};

struct conv_i2_op_t {};

struct conv_i4_op_t {};

struct conv_i_op_t {};

struct conv_u1_op_t {};

struct conv_u2_op_t {};

struct conv_u4_op_t {};

struct conv_u_op_t {};

struct conv_br2_op_t {};

struct conv_r4_op_t {};

// Tensor instructions

struct tensor_batch_normalization_op_t {};

struct tensor_batch_to_space_op_t {};

struct tensor_binary_op_t {
    binary_op_t binary_op;
};

struct tensor_bitcast_op_t {
    prim_type_t type;
    prim_type_t new_type;
};

struct tensor_broadcast_op_t {};

struct tensor_bucket_pad_op_t {};

struct tensor_cast_op_t {
    typecode_t new_type;
    cast_mode_t cast_mode;
};

struct tensor_celu_op_t {};

struct tensor_clamp_op_t {};

struct tensor_compare_op_t {
    compare_op_t compare_op;
};

struct tensor_concat_op_t {};

struct tensor_condition_op_t {
    bool can_fold_const_call;
};

struct tensor_constant_of_shape_op_t {};

struct tensor_conv2d_op_t {
    pad_mode_t pad_mode;
};

struct tensor_conv2d_transpose_op_t {
    pad_mode_t pad_mode;
};

struct tensor_cum_sum_op_t {};

struct tensor_dequantize_op_t {
    typecode_t target_type;
};

struct tensor_elu_op_t {};

struct tensor_erf_op_t {};

struct tensor_expand_op_t {};

struct tensor_fake_dequantize_op_t {
    typecode_t target_type;
};

struct tensor_fake_quantize_op_t {
    typecode_t target_type;
};

struct tensor_fix_shape_op_t {};

struct tensor_flatten_op_t {};

struct tensor_gather_op_t {};

struct tensor_gather_elements_op_t {};

struct tensor_gather_nd_op_t {};

struct tensor_gelu_op_t {};

struct tensor_get_item_op_t {};

struct tensor_hard_sigmoid_op_t {};

struct tensor_hard_swish_op_t {};

struct tensor_hardmax_op_t {};

struct tensor_index_of_op_t {};

struct tensor_instance_normalization_op_t {};

struct tensor_l2_normalization_op_t {};

struct tensor_layer_norm_op_t {
    int32_t axis;
    float epsilon;
};

struct tensor_leaky_relu_op_t {};

struct tensor_log_softmax_op_t {};

struct tensor_lp_normalization_op_t {};

struct tensor_lrn_op_t {};

struct tensor_lstm_op_t {
    lstmdirection_t direction;
    lstmlayout_t layout;
    std::vector<std::string> activations;
};

struct tensor_mat_mul_op_t {};

struct tensor_normal_op_t {
    typecode_t type;
};

struct tensor_normal_like_op_t {
    typecode_t type;
};

struct tensor_one_hot_op_t {
    one_hot_mode_t one_hot_mode;
};

struct tensor_pad_op_t {
    pad_mode_t pad_mode;
};

struct tensor_prelu_op_t {};

struct tensor_prod_op_t {};

struct tensor_quant_param_of_op_t {
    quant_mode_t quant_mode;
};

struct tensor_quantize_op_t {
    typecode_t target_type;
};

struct tensor_range_op_t {};

struct tensor_range_of_op_t {
    bool is_range_of_weight;
};

struct tensor_rank_op_t {};

struct tensor_reduce_op_t {
    reduce_op_t reduce_op;
};

struct tensor_reduce_arg_op_t {
    reduce_arg_op_t reduce_arg_op;
    typecode_t dest_type;
};

struct tensor_reduce_window2d_op_t {
    reduce_op_t reduce_op;
};

struct tensor_relu_op_t {};

struct tensor_relu6_op_t {};

struct tensor_require_op_t {
    std::string message;
    bool can_fold_const_call;
};

struct tensor_reshape_op_t {};

struct tensor_resize_image_op_t {
    image_resize_mode_t resize_mode;
    image_resize_transformation_mode_t transformation_mode;
    image_resize_nearest_mode_t nearest_mode;
    bool is_tfresize;
};

struct tensor_reverse_sequence_op_t {};

struct tensor_scatter_nd_op_t {};

struct tensor_select_op_t {};

struct tensor_selu_op_t {};

struct tensor_shape_of_op_t {};

struct tensor_sigmoid_op_t {};

struct tensor_size_of_op_t {};

struct tensor_slice_op_t {};

struct tensor_softmax_op_t {};

struct tensor_softplus_op_t {};

struct tensor_softsign_op_t {};

struct tensor_space_to_batch_op_t {};

struct tensor_split_op_t {};

struct tensor_squeeze_op_t {};

struct tensor_stack_op_t {};

struct tensor_swish_op_t {};

struct tensor_tile_op_t {};

struct tensor_top_k_op_t {};

struct tensor_transpose_op_t {};

struct tensor_unary_op_t {
    unary_op_t unary_op;
};

struct tensor_uniform_op_t {
    typecode_t type;
};

struct tensor_uniform_like_op_t {
    typecode_t type;
};

struct tensor_unsqueeze_op_t {};

struct tensor_where_op_t {
    bool is_tf_where;
};

inline std::string to_string(tensor_function_t tensor_funct) {
    switch (tensor_funct) {
    case tensor_function_t::batch_normalization:
        return "batch_normalization";
    case tensor_function_t::batch_to_space:
        return "batch_to_space";
    case tensor_function_t::celu:
        return "celu";
    case tensor_function_t::conv2d:
        return "conv2d";
    case tensor_function_t::conv2d_transpose:
        return "conv2d_transpose";
    case tensor_function_t::elu:
        return "elu";
    case tensor_function_t::erf:
        return "erf";
    case tensor_function_t::gelu:
        return "gelu";
    case tensor_function_t::hardmax:
        return "hardmax";
    case tensor_function_t::hard_sigmoid:
        return "hard_sigmoid";
    case tensor_function_t::hard_swish:
        return "hard_swish";
    case tensor_function_t::instance_normalization:
        return "instance_normalization";
    case tensor_function_t::l2_normalization:
        return "l2_normalization";
    case tensor_function_t::layer_norm:
        return "layer_norm";
    case tensor_function_t::leaky_relu:
        return "leaky_relu";
    case tensor_function_t::log_softmax:
        return "log_softmax";
    case tensor_function_t::lp_normalization:
        return "lp_normalization";
    case tensor_function_t::lrn:
        return "lrn";
    case tensor_function_t::one_hot:
        return "one_hot";
    case tensor_function_t::pad:
        return "pad";
    case tensor_function_t::prelu:
        return "prelu";
    case tensor_function_t::reduce_window2d:
        return "reduce_window2d";
    case tensor_function_t::relu:
        return "relu";
    case tensor_function_t::relu6:
        return "relu6";
    case tensor_function_t::selu:
        return "selu";
    case tensor_function_t::sigmoid:
        return "sigmoid";
    case tensor_function_t::softmax:
        return "softmax";
    case tensor_function_t::softplus:
        return "softplus";
    case tensor_function_t::softsign:
        return "softsign";
    case tensor_function_t::space_to_batch:
        return "space_to_batch";
    case tensor_function_t::swish:
        return "swish";
    case tensor_function_t::binary:
        return "binary";
    case tensor_function_t::clamp:
        return "clamp";
    case tensor_function_t::compare:
        return "compare";
    case tensor_function_t::condition:
        return "condition";
    case tensor_function_t::cum_sum:
        return "cum_sum";
    case tensor_function_t::dequantize:
        return "dequantize";
    case tensor_function_t::fake_dequantize:
        return "fake_dequantize";
    case tensor_function_t::fake_quantize:
        return "fake_quantize";
    case tensor_function_t::mat_mul:
        return "mat_mul";
    case tensor_function_t::quantize:
        return "quantize";
    case tensor_function_t::quant_param_of:
        return "quant_param_of";
    case tensor_function_t::range_of:
        return "range_of";
    case tensor_function_t::reduce:
        return "reduce";
    case tensor_function_t::reduce_arg:
        return "reduce_arg";
    case tensor_function_t::require:
        return "require";
    case tensor_function_t::select:
        return "select";
    case tensor_function_t::unary:
        return "unary";
    case tensor_function_t::bitcast:
        return "bitcast";
    case tensor_function_t::broadcast:
        return "broadcast";
    case tensor_function_t::bucket_pad:
        return "bucket_pad";
    case tensor_function_t::cast:
        return "cast";
    case tensor_function_t::concat:
        return "concat";
    case tensor_function_t::constant_of_shape:
        return "constant_of_shape";
    case tensor_function_t::expand:
        return "expand";
    case tensor_function_t::fix_shape:
        return "fix_shape";
    case tensor_function_t::flatten:
        return "flatten";
    case tensor_function_t::gather:
        return "gather";
    case tensor_function_t::gather_elements:
        return "gather_elements";
    case tensor_function_t::gather_nd:
        return "gather_nd";
    case tensor_function_t::get_item:
        return "get_item";
    case tensor_function_t::index_of:
        return "index_of";
    case tensor_function_t::lstm:
        return "lstm";
    case tensor_function_t::prod:
        return "prod";
    case tensor_function_t::range:
        return "range";
    case tensor_function_t::rank:
        return "rank";
    case tensor_function_t::reshape:
        return "reshape";
    case tensor_function_t::reverse_sequence:
        return "reverse_sequence";
    case tensor_function_t::scatter_nd:
        return "scatter_nd";
    case tensor_function_t::shape_of:
        return "shape_of";
    case tensor_function_t::size_of:
        return "size_of";
    case tensor_function_t::slice:
        return "slice";
    case tensor_function_t::split:
        return "split";
    case tensor_function_t::squeeze:
        return "squeeze";
    case tensor_function_t::stack:
        return "stack";
    case tensor_function_t::tile:
        return "tile";
    case tensor_function_t::top_k:
        return "top_k";
    case tensor_function_t::transpose:
        return "transpose";
    case tensor_function_t::unsqueeze:
        return "unsqueeze";
    case tensor_function_t::where:
        return "where";
    case tensor_function_t::normal:
        return "normal";
    case tensor_function_t::normal_like:
        return "normal_like";
    case tensor_function_t::uniform:
        return "uniform";
    case tensor_function_t::uniform_like:
        return "uniform_like";
    case tensor_function_t::resize_image:
        return "resize_image";
    }
    return "unknown tensor_function_t";
}

inline std::string to_string(opcode_t code) {
    switch (code) {
    case opcode_t::NOP:
        return "NOP";
    case opcode_t::LDNULL:
        return "LDNULL";
    case opcode_t::LDC_I4:
        return "LDC_I4";
    case opcode_t::LDC_I4_0:
        return "LDC_I4_0";
    case opcode_t::LDC_I4_1:
        return "LDC_I4_1";
    case opcode_t::LDC_R4:
        return "LDC_R4";
    case opcode_t::LDIND_I1:
        return "LDIND_I1";
    case opcode_t::LDIND_I2:
        return "LDIND_I2";
    case opcode_t::LDIND_I4:
        return "LDIND_I4";
    case opcode_t::LDIND_I:
        return "LDIND_I";
    case opcode_t::LDIND_U1:
        return "LDIND_U1";
    case opcode_t::LDIND_U2:
        return "LDIND_U2";
    case opcode_t::LDIND_U4:
        return "LDIND_U4";
    case opcode_t::LDIND_U:
        return "LDIND_U";
    case opcode_t::LDIND_BR2:
        return "LDIND_BR2";
    case opcode_t::LDIND_R4:
        return "LDIND_R4";
    case opcode_t::STIND_I1:
        return "STIND_I1";
    case opcode_t::STIND_I2:
        return "STIND_I2";
    case opcode_t::STIND_I4:
        return "STIND_I4";
    case opcode_t::STIND_I:
        return "STIND_I";
    case opcode_t::STIND_BR2:
        return "STIND_BR2";
    case opcode_t::STIND_R4:
        return "STIND_R4";
    case opcode_t::LEA_GP:
        return "LEA_GP";
    case opcode_t::LDELEM_I1:
        return "LDELEM_I1";
    case opcode_t::LDELEM_I2:
        return "LDELEM_I2";
    case opcode_t::LDELEM_I4:
        return "LDELEM_I4";
    case opcode_t::LDELEM_I:
        return "LDELEM_I";
    case opcode_t::LDELEM_U1:
        return "LDELEM_U1";
    case opcode_t::LDELEM_U2:
        return "LDELEM_U2";
    case opcode_t::LDELEM_U4:
        return "LDELEM_U4";
    case opcode_t::LDELEM_U:
        return "LDELEM_U";
    case opcode_t::LDELEM_BR2:
        return "LDELEM_BR2";
    case opcode_t::LDELEM_R4:
        return "LDELEM_R4";
    case opcode_t::STELEM_I1:
        return "STELEM_I1";
    case opcode_t::STELEM_I2:
        return "STELEM_I2";
    case opcode_t::STELEM_I4:
        return "STELEM_I4";
    case opcode_t::STELEM_I:
        return "STELEM_I";
    case opcode_t::STELEM_BR2:
        return "STELEM_BR2";
    case opcode_t::STELEM_R4:
        return "STELEM_R4";
    case opcode_t::LDARG:
        return "LDARG";
    case opcode_t::LDARG_0:
        return "LDARG_0";
    case opcode_t::LDARG_1:
        return "LDARG_1";
    case opcode_t::LDARG_2:
        return "LDARG_2";
    case opcode_t::LDARG_3:
        return "LDARG_3";
    case opcode_t::LDARG_4:
        return "LDARG_4";
    case opcode_t::LDARG_5:
        return "LDARG_5";
    case opcode_t::DUP:
        return "DUP";
    case opcode_t::POP:
        return "POP";
    case opcode_t::LDLOCAL:
        return "LDLOCAL";
    case opcode_t::STLOCAL:
        return "STLOCAL";
    case opcode_t::LDTUPLE_ELEM:
        return "LDTUPLE_ELEM";
    case opcode_t::LDTUPLE:
        return "LDTUPLE";
    case opcode_t::LDDATATYPE:
        return "LDDATATYPE";
    case opcode_t::LDTENSOR:
        return "LDTENSOR";
    case opcode_t::LDSCALAR:
        return "LDSCALAR";
    case opcode_t::NEG:
        return "NEG";
    case opcode_t::ADD:
        return "ADD";
    case opcode_t::SUB:
        return "SUB";
    case opcode_t::MUL:
        return "MUL";
    case opcode_t::DIV:
        return "DIV";
    case opcode_t::DIV_U:
        return "DIV_U";
    case opcode_t::REM:
        return "REM";
    case opcode_t::REM_U:
        return "REM_U";
    case opcode_t::AND:
        return "AND";
    case opcode_t::OR:
        return "OR";
    case opcode_t::XOR:
        return "XOR";
    case opcode_t::NOT:
        return "NOT";
    case opcode_t::SHL:
        return "SHL";
    case opcode_t::SHR:
        return "SHR";
    case opcode_t::SHR_U:
        return "SHR_U";
    case opcode_t::CLT:
        return "CLT";
    case opcode_t::CLT_U:
        return "CLT_U";
    case opcode_t::CLE:
        return "CLE";
    case opcode_t::CLE_U:
        return "CLE_U";
    case opcode_t::CEQ:
        return "CEQ";
    case opcode_t::CGE:
        return "CGE";
    case opcode_t::CGE_U:
        return "CGE_U";
    case opcode_t::CGT:
        return "CGT";
    case opcode_t::CGT_U:
        return "CGT_U";
    case opcode_t::CNE:
        return "CNE";
    case opcode_t::CONV_I1:
        return "CONV_I1";
    case opcode_t::CONV_I2:
        return "CONV_I2";
    case opcode_t::CONV_I4:
        return "CONV_I4";
    case opcode_t::CONV_I:
        return "CONV_I";
    case opcode_t::CONV_U1:
        return "CONV_U1";
    case opcode_t::CONV_U2:
        return "CONV_U2";
    case opcode_t::CONV_U4:
        return "CONV_U4";
    case opcode_t::CONV_U:
        return "CONV_U";
    case opcode_t::CONV_BR2:
        return "CONV_BR2";
    case opcode_t::CONV_R4:
        return "CONV_R4";
    case opcode_t::BR:
        return "BR";
    case opcode_t::BR_TRUE:
        return "BR_TRUE";
    case opcode_t::BR_FALSE:
        return "BR_FALSE";
    case opcode_t::RET:
        return "RET";
    case opcode_t::CALL:
        return "CALL";
    case opcode_t::ECALL:
        return "ECALL";
    case opcode_t::EXTCALL:
        return "EXTCALL";
    case opcode_t::CUSCALL:
        return "CUSCALL";
    case opcode_t::THROW:
        return "THROW";
    case opcode_t::BREAK:
        return "BREAK";
    case opcode_t::TENSOR:
        return "TENSOR";
    }
    return "unknown opcode_t";
}
END_NS_NNCASE_RT_MODULE
