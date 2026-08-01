#include "py/binary.h"
#include "py/obj.h"
#include "py/objarray.h"
#include "py/objstr.h"
#include "py/runtime.h"
#include "sasppu/help.h"
#include "sasppu/sasppu.h"

#include "sasppu_background_map.h"
#include "sasppu_background_state.h"
#include "sasppu_buffer.h"
#include "sasppu_cmath_state.h"
#include "sasppu_graphics_plane.h"
#include "sasppu_hdma.h"
#include "sasppu_main_state.h"
#include "sasppu_mpy_help.h"
#include "sasppu_sprite.h"

#if !MICROPY_ENABLE_FINALISER
#error "SASPPU_MPY requires MICROPY_ENABLE_FINALISER"
#endif

void sasppu_module_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest) {
  if (dest[0] == MP_OBJ_NULL) {
    // Load attribute.
    switch (attr) {
    case MP_QSTR_forced_blank:
      dest[0] = SASPPU_forced_blank ? mp_const_true : mp_const_false;
      break;
    default:
      dest[1] = MP_OBJ_SENTINEL;
      break;
    }
  } else if (dest[1] != MP_OBJ_NULL) {
    // Store attribute.
    switch (attr) {
    case MP_QSTR_forced_blank: {
      SASPPU_forced_blank = mp_obj_is_true(dest[1]);
      dest[0] = MP_OBJ_NULL;
    }
    default:
      break;
    }
  }
}

// Define all attributes of the module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
static const mp_rom_map_elem_t sasppu_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_sasppu)},

    {MP_ROM_QSTR(MP_QSTR_BackgroundMap),
     MP_ROM_PTR(&sasppu_type_background_map)},
    {MP_ROM_QSTR(MP_QSTR_BackgroundState),
     MP_ROM_PTR(&sasppu_type_background_state)},
    {MP_ROM_QSTR(MP_QSTR_BufferEntry), MP_ROM_PTR(&sasppu_type_buffer_entry)},
    {MP_ROM_QSTR(MP_QSTR_CMathState), MP_ROM_PTR(&sasppu_type_cmath_state)},
    {MP_ROM_QSTR(MP_QSTR_GraphicsPlane),
     MP_ROM_PTR(&sasppu_type_graphics_plane)},
    {MP_ROM_QSTR(MP_QSTR_HdmaEntry), MP_ROM_PTR(&sasppu_type_hdma_entry)},
    {MP_ROM_QSTR(MP_QSTR_MainState), MP_ROM_PTR(&sasppu_type_main_state)},
    {MP_ROM_QSTR(MP_QSTR_Sprite), MP_ROM_PTR(&sasppu_type_sprite)},

    {MP_ROM_QSTR(MP_QSTR_copy), MP_ROM_PTR(&sasppu_copy_obj)},
    {MP_ROM_QSTR(MP_QSTR_fill), MP_ROM_PTR(&sasppu_fill_obj)},
    {MP_ROM_QSTR(MP_QSTR_blit), MP_ROM_PTR(&sasppu_blit_obj)},
    {MP_ROM_QSTR(MP_QSTR_paletted), MP_ROM_PTR(&sasppu_paletted_obj)},
    {MP_ROM_QSTR(MP_QSTR_compressed), MP_ROM_PTR(&sasppu_compressed_obj)},
    {MP_ROM_QSTR(MP_QSTR_draw_text), MP_ROM_PTR(&sasppu_draw_text_obj)},
    {MP_ROM_QSTR(MP_QSTR_draw_text_next),
     MP_ROM_PTR(&sasppu_draw_text_next_obj)},

    {MP_ROM_QSTR(MP_QSTR_get_text_size), MP_ROM_PTR(&sasppu_get_text_size_obj)},

    {MP_ROM_QSTR(MP_QSTR_mul_rgb555), MP_ROM_PTR(&sasppu_macro_mul_rgb555_obj)},
    {MP_ROM_QSTR(MP_QSTR_cmath), MP_ROM_PTR(&sasppu_macro_cmath_obj)},
    {MP_ROM_QSTR(MP_QSTR_rgb555), MP_ROM_PTR(&sasppu_macro_rgb555_obj)},
    {MP_ROM_QSTR(MP_QSTR_rgb555_cmath),
     MP_ROM_PTR(&sasppu_macro_rgb555_cmath_obj)},
    {MP_ROM_QSTR(MP_QSTR_rgb888), MP_ROM_PTR(&sasppu_macro_rgb888_obj)},
    {MP_ROM_QSTR(MP_QSTR_rgb888_cmath),
     MP_ROM_PTR(&sasppu_macro_rgb888_cmath_obj)},
    {MP_ROM_QSTR(MP_QSTR_grey555), MP_ROM_PTR(&sasppu_macro_grey555_obj)},
    {MP_ROM_QSTR(MP_QSTR_grey555_cmath),
     MP_ROM_PTR(&sasppu_macro_grey555_cmath_obj)},
    {MP_ROM_QSTR(MP_QSTR_mul_channel),
     MP_ROM_PTR(&sasppu_macro_mul_channel_obj)},
    {MP_ROM_QSTR(MP_QSTR_r_channel), MP_ROM_PTR(&sasppu_macro_r_channel_obj)},
    {MP_ROM_QSTR(MP_QSTR_g_channel), MP_ROM_PTR(&sasppu_macro_g_channel_obj)},
    {MP_ROM_QSTR(MP_QSTR_b_channel), MP_ROM_PTR(&sasppu_macro_b_channel_obj)},
    {MP_ROM_QSTR(MP_QSTR_cmath_channel),
     MP_ROM_PTR(&sasppu_macro_cmath_channel_obj)},
    {MP_ROM_QSTR(MP_QSTR_mul_col), MP_ROM_PTR(&sasppu_macro_mul_col_obj)},

    {MP_ROM_QSTR(MP_QSTR_SPRITE_COUNT_POWER_MAX),
     MP_ROM_INT(SPRITE_COUNT_POWER_MAX)},
    {MP_ROM_QSTR(MP_QSTR_SPRITE_COUNT_POWER_MIN),
     MP_ROM_INT(SPRITE_COUNT_POWER_MIN)},
    {MP_ROM_QSTR(MP_QSTR_SPRITE_CACHE_POWER), MP_ROM_INT(SPRITE_CACHE_POWER)},
    {MP_ROM_QSTR(MP_QSTR_SPRITE_COUNT_MAX), MP_ROM_INT(SPRITE_COUNT_MAX)},
    {MP_ROM_QSTR(MP_QSTR_SPRITE_COUNT_MIN), MP_ROM_INT(SPRITE_COUNT_MIN)},
    {MP_ROM_QSTR(MP_QSTR_SPRITE_CACHE), MP_ROM_INT(SPRITE_CACHE)},

    {MP_ROM_QSTR(MP_QSTR_GRAPHICS_WIDTH_POWER_MAX),
     MP_ROM_INT(GRAPHICS_WIDTH_POWER_MAX)},
    {MP_ROM_QSTR(MP_QSTR_GRAPHICS_HEIGHT_POWER_MAX),
     MP_ROM_INT(GRAPHICS_HEIGHT_POWER_MAX)},
    {MP_ROM_QSTR(MP_QSTR_GRAPHICS_WIDTH_POWER_MIN),
     MP_ROM_INT(GRAPHICS_WIDTH_POWER_MIN)},
    {MP_ROM_QSTR(MP_QSTR_GRAPHICS_HEIGHT_POWER_MIN),
     MP_ROM_INT(GRAPHICS_HEIGHT_POWER_MIN)},
    {MP_ROM_QSTR(MP_QSTR_GRAPHICS_WIDTH_MAX), MP_ROM_INT(GRAPHICS_WIDTH_MAX)},
    {MP_ROM_QSTR(MP_QSTR_GRAPHICS_HEIGHT_MAX), MP_ROM_INT(GRAPHICS_HEIGHT_MAX)},
    {MP_ROM_QSTR(MP_QSTR_GRAPHICS_WIDTH_MIN), MP_ROM_INT(GRAPHICS_WIDTH_MIN)},
    {MP_ROM_QSTR(MP_QSTR_GRAPHICS_HEIGHT_MIN), MP_ROM_INT(GRAPHICS_HEIGHT_MIN)},

    {MP_ROM_QSTR(MP_QSTR_MAP_WIDTH_POWER_MAX), MP_ROM_INT(MAP_WIDTH_POWER_MAX)},
    {MP_ROM_QSTR(MP_QSTR_MAP_HEIGHT_POWER_MAX),
     MP_ROM_INT(MAP_HEIGHT_POWER_MAX)},
    {MP_ROM_QSTR(MP_QSTR_MAP_WIDTH_POWER_MIN), MP_ROM_INT(MAP_WIDTH_POWER_MIN)},
    {MP_ROM_QSTR(MP_QSTR_MAP_HEIGHT_POWER_MIN),
     MP_ROM_INT(MAP_HEIGHT_POWER_MIN)},
    {MP_ROM_QSTR(MP_QSTR_MAP_WIDTH_MAX), MP_ROM_INT(MAP_WIDTH_MAX)},
    {MP_ROM_QSTR(MP_QSTR_MAP_HEIGHT_MAX), MP_ROM_INT(MAP_HEIGHT_MAX)},
    {MP_ROM_QSTR(MP_QSTR_MAP_WIDTH_MIN), MP_ROM_INT(MAP_WIDTH_MIN)},
    {MP_ROM_QSTR(MP_QSTR_MAP_HEIGHT_MIN), MP_ROM_INT(MAP_HEIGHT_MIN)},

    {MP_ROM_QSTR(MP_QSTR_IC_SUCCESS), MP_ROM_INT(SASPPU_IC_Success)},
    {MP_ROM_QSTR(MP_QSTR_IC_TOO_WIDE), MP_ROM_INT(SASPPU_IC_TooWide)},
    {MP_ROM_QSTR(MP_QSTR_IC_TOO_TALL), MP_ROM_INT(SASPPU_IC_TooTall)},
    {MP_ROM_QSTR(MP_QSTR_IC_INVALID_BIT_DEPTH),
     MP_ROM_INT(SASPPU_IC_InvalidBitdepth)},

    {MP_ROM_QSTR(MP_QSTR_WINDOW_A), MP_ROM_INT(WINDOW_A)},
    {MP_ROM_QSTR(MP_QSTR_WINDOW_B), MP_ROM_INT(WINDOW_B)},
    {MP_ROM_QSTR(MP_QSTR_WINDOW_AB), MP_ROM_INT(WINDOW_AB)},
    {MP_ROM_QSTR(MP_QSTR_WINDOW_X), MP_ROM_INT(WINDOW_X)},
    {MP_ROM_QSTR(MP_QSTR_WINDOW_ALL), MP_ROM_INT(WINDOW_ALL)},

    {MP_ROM_QSTR(MP_QSTR_BPP1), MP_ROM_INT(0)},
    {MP_ROM_QSTR(MP_QSTR_BPP2), MP_ROM_INT(1)},
    {MP_ROM_QSTR(MP_QSTR_BPP4), MP_ROM_INT(2)},
    {MP_ROM_QSTR(MP_QSTR_BPP8), MP_ROM_INT(3)},

    {MP_ROM_QSTR(MP_QSTR_SCREEN_WIDTH), MP_ROM_INT(SCREEN_WIDTH)},
    {MP_ROM_QSTR(MP_QSTR_SCREEN_HEIGHT), MP_ROM_INT(SCREEN_HEIGHT)},

    {MP_ROM_QSTR(MP_QSTR_TRANSPARENT_BLACK),
     MP_ROM_INT(SASPPU_RGB555(0, 0, 0))},
    {MP_ROM_QSTR(MP_QSTR_OPAQUE_BLACK), MP_ROM_INT(SASPPU_RGB555(1, 0, 0))},
    {MP_ROM_QSTR(MP_QSTR_RED), MP_ROM_INT(SASPPU_RGB555(31, 0, 0))},
    {MP_ROM_QSTR(MP_QSTR_GREEN), MP_ROM_INT(SASPPU_RGB555(0, 31, 0))},
    {MP_ROM_QSTR(MP_QSTR_BLUE), MP_ROM_INT(SASPPU_RGB555(0, 0, 31))},
    {MP_ROM_QSTR(MP_QSTR_WHITE), MP_ROM_INT(SASPPU_RGB555(31, 31, 31))},
};
static MP_DEFINE_CONST_DICT(sasppu_globals, sasppu_globals_table);

// Define module object.
const mp_obj_module_t sasppu_module = {
    .base = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&sasppu_globals,
};

// Register the module to make it available in Python.
MP_REGISTER_MODULE(MP_QSTR_sasppu, sasppu_module);

MP_REGISTER_MODULE_DELEGATION(sasppu_module, sasppu_module_attr);
