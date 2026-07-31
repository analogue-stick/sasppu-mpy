#pragma once
#include "py/binary.h"
#include "py/obj.h"
#include "py/objarray.h"
#include "py/objstr.h"
#include "py/runtime.h"
#include "sasppu/help.h"
#include "sasppu/sasppu.h"

extern const mp_obj_fun_builtin_var_t sasppu_copy_obj;
extern const mp_obj_fun_builtin_var_t sasppu_blit_obj;
extern const mp_obj_fun_builtin_var_t sasppu_paletted_obj;
extern const mp_obj_fun_builtin_var_t sasppu_compressed_obj;
extern const mp_obj_fun_builtin_var_t sasppu_draw_text_obj;
extern const mp_obj_fun_builtin_var_t sasppu_draw_text_next_obj;
extern const mp_obj_fun_builtin_var_t sasppu_fill_obj;

extern const mp_obj_fun_builtin_var_t sasppu_get_text_size_obj;

extern const mp_obj_fun_builtin_var_t sasppu_macro_mul_rgb555_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_cmath_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_rgb555_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_rgb555_cmath_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_rgb888_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_rgb888_cmath_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_grey555_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_grey555_cmath_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_mul_channel_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_r_channel_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_g_channel_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_b_channel_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_cmath_channel_obj;
extern const mp_obj_fun_builtin_fixed_t sasppu_macro_mul_col_obj;
