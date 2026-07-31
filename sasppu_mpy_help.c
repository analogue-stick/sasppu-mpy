#include "sasppu_mpy_help.h"
#include "sasppu_graphics_plane.h"

/**
 * Copy a block from somewhere on the plane to somewhere else on the plane.
 * @param graphics_plane Graphics plane to edit
 * @param dst_x X coordinate to copy to
 * @param dst_y Y coordinate to copy to
 * @param width Width of the block to copy
 * @param height Height of the block to copy
 * @param src_x Source X coordinate in plane memory
 * @param src_y Source Y coordinate in plane memory
 * @param double_size (optional) If true, copy at double size
 * @param transparent (optional) If true, transparent pixels will not be written
 * @return An integer indicating the result of the copy operation
 */
static mp_obj_t sasppu_copy(size_t n_args, const mp_obj_t *args) {
  if (!mp_obj_is_type(args[0], &sasppu_type_graphics_plane)) {
    mp_raise_TypeError(MP_ERROR_TEXT("not a graphics plane"));
    return mp_const_none;
  }
  GraphicsPlane *graphics_plane = MP_OBJ_TO_PTR(args[0]);
  mp_int_t dst_x = mp_obj_get_int(args[1]);
  mp_int_t dst_y = mp_obj_get_int(args[2]);
  mp_int_t width = mp_obj_get_int(args[3]);
  mp_int_t height = mp_obj_get_int(args[4]);
  mp_int_t src_x = mp_obj_get_int(args[5]);
  mp_int_t src_y = mp_obj_get_int(args[6]);
  bool double_size = false;
  if (n_args == 8) {
    double_size = mp_obj_is_true(args[7]);
  }
  bool transparent = false;
  if (n_args == 9) {
    transparent = mp_obj_is_true(args[8]);
  }
  SASPPUImageCode res = SASPPU_copy(graphics_plane, dst_x, dst_y, width, height,
                                    src_x, src_y, double_size, transparent);
  return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_copy_obj, 8, 9, sasppu_copy);

/**
 * Fill a rectangular area of a plane with a solid color.
 * @param graphics_plane Graphics plane to edit
 * @param x X coordinate of the area
 * @param y Y coordinate of the area
 * @param width Width of the area to fill
 * @param height Height of the area to fill
 * @param colour Color value to fill with
 * @return An integer indicating the result of the fill operation
 */
static mp_obj_t sasppu_fill(size_t n_args, const mp_obj_t *args) {
  if (!mp_obj_is_type(args[0], &sasppu_type_graphics_plane)) {
    mp_raise_TypeError(MP_ERROR_TEXT("not a graphics plane"));
    return mp_const_none;
  }
  GraphicsPlane *graphics_plane = MP_OBJ_TO_PTR(args[0]);
  mp_int_t x = mp_obj_get_int(args[1]);
  mp_int_t y = mp_obj_get_int(args[2]);
  mp_int_t width = mp_obj_get_int(args[3]);
  mp_int_t height = mp_obj_get_int(args[4]);
  mp_int_t colour = mp_obj_get_int(args[5]);
  SASPPUImageCode res =
      SASPPU_fill(graphics_plane, x, y, width, height, colour);
  return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_fill_obj, 6, 6, sasppu_fill);

/**
 * Draw multiline text on a plane.
 * @param graphics_plane Graphics plane to edit
 * @param x X coordinate to start drawing
 * @param y Y coordinate to start drawing
 * @param colour Text color value
 * @param line_width Maximum line width in pixels
 * @param text The text string to draw
 * @param double_size (optional) If true, draw text at double size
 * @param newline_height (optional) Height of newlines in pixels
 * @return An integer indicating the result of the text draw operation
 */
static mp_obj_t sasppu_draw_text(size_t n_args, const mp_obj_t *args) {
  if (!mp_obj_is_type(args[0], &sasppu_type_graphics_plane)) {
    mp_raise_TypeError(MP_ERROR_TEXT("not a graphics plane"));
    return mp_const_none;
  }
  GraphicsPlane *graphics_plane = MP_OBJ_TO_PTR(args[0]);
  mp_int_t x = mp_obj_get_int(args[1]);
  mp_int_t y = mp_obj_get_int(args[2]);
  mp_int_t colour = mp_obj_get_int(args[3]);
  mp_int_t line_width = mp_obj_get_int(args[4]);
  mp_check_self(mp_obj_is_str_or_bytes(args[5]));
  GET_STR_DATA_LEN(args[5], text, text_len);
  mp_int_t newline_height = 10;
  bool double_size = false;
  if (n_args >= 7) {
    double_size = mp_obj_is_true(args[6]);
  }
  if (n_args == 8) {
    newline_height = mp_obj_get_int(args[7]);
  }
  SASPPUImageCode res =
      SASPPU_draw_text(graphics_plane, x, y, colour, line_width, newline_height,
                       double_size, (const char *)text);
  return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_draw_text_obj, 6, 8,
                                    sasppu_draw_text);

/**
 * Draw text onto a plane and return next cursor position.
 * @param graphics_plane Graphics plane to edit
 * @param x Starting X coordinate (updated in place)
 * @param y Starting Y coordinate (updated in place)
 * @param colour Text color value
 * @param line_start Starting offset within the text
 * @param line_width Maximum line width in pixels
 * @param text The text string to draw
 * @param double_size (optional) If true, draw text at double size
 * @param newline_height (optional) Height of newlines in pixels
 * @return Tuple (result_code, new_x, new_y)
 */
static mp_obj_t sasppu_draw_text_next(size_t n_args, const mp_obj_t *args) {
  if (!mp_obj_is_type(args[0], &sasppu_type_graphics_plane)) {
    mp_raise_TypeError(MP_ERROR_TEXT("not a graphics plane"));
    return mp_const_none;
  }
  GraphicsPlane *graphics_plane = MP_OBJ_TO_PTR(args[0]);
  size_t x = mp_obj_get_int(args[1]);
  size_t y = mp_obj_get_int(args[2]);
  mp_int_t colour = mp_obj_get_int(args[3]);
  mp_int_t line_start = mp_obj_get_int(args[4]);
  mp_int_t line_width = mp_obj_get_int(args[5]);
  mp_check_self(mp_obj_is_str_or_bytes(args[6]));
  GET_STR_DATA_LEN(args[6], text, text_len);
  mp_int_t newline_height = 10;
  bool double_size = false;
  if (n_args >= 8) {
    double_size = mp_obj_is_true(args[7]);
  }
  if (n_args == 9) {
    newline_height = mp_obj_get_int(args[8]);
  }
  SASPPUImageCode res =
      SASPPU_draw_text_next(&x, &y, colour, line_start, line_width,
                            newline_height, double_size, (const char **)&text);
  mp_obj_t tuple_args[3] = {MP_OBJ_NEW_SMALL_INT(res), MP_OBJ_NEW_SMALL_INT(x),
                            MP_OBJ_NEW_SMALL_INT(y)};
  return mp_obj_new_tuple(3, tuple_args);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_draw_text_next_sprite_obj, 7, 9,
                                    sasppu_draw_text_next_sprite);

/**
 * Blit a graphic to a plane.
 * @param graphics_plane Graphics plane to edit
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the graphic
 * @param height Height of the graphic
 * @param data The graphic data as a bytes or bytearray object
 * @param double_size (optional) If true, the graphic will be drawn at double
 * size
 * @param transparent (optional) If true, transparent pixels will not be written
 * @return An integer indicating the result of the blit operation
 */
static mp_obj_t sasppu_blit(size_t n_args, const mp_obj_t *args) {
  if (!mp_obj_is_type(args[0], &sasppu_type_graphics_plane)) {
    mp_raise_TypeError(MP_ERROR_TEXT("not a graphics plane"));
    return mp_const_none;
  }
  GraphicsPlane *graphics_plane = MP_OBJ_TO_PTR(args[0]);
  mp_int_t x = mp_obj_get_int(args[1]);
  mp_int_t y = mp_obj_get_int(args[2]);
  mp_int_t width = mp_obj_get_int(args[3]);
  mp_int_t height = mp_obj_get_int(args[4]);
  mp_check_self(mp_obj_is_str_or_bytes(args[5]));
  GET_STR_DATA_LEN(args[5], data, data_len);
  if (data_len < (width * height * 2)) {
    mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for size"));
    return mp_const_none;
  }
  bool double_size = false;
  if (n_args == 7) {
    double_size = mp_obj_is_true(args[6]);
  }
  bool transparent = false;
  if (n_args == 8) {
    transparent = mp_obj_is_true(args[7]);
  }
  SASPPUImageCode res =
      SASPPU_blit(graphics_plane, x, y, width, height, double_size, transparent,
                  (const uint16_t *)data);
  return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_blit_obj, 6, 8, sasppu_blit);

/**
 * Blit a paletted graphic to a plane.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the graphic
 * @param height Height of the graphic
 * @param palette Palette data as bytes or bytearray
 * @param bitdepth Bit depth (0-3) for palette indices
 * @param data The graphic index data as bytes or bytearray
 * @param double_size (optional) If true, draw at double size
 * @param transparent (optional) If true, transparent pixels will not be written
 * @return An integer indicating the result of the paletted blit
 */
static mp_obj_t sasppu_paletted(size_t n_args, const mp_obj_t *args) {
  if (!mp_obj_is_type(args[0], &sasppu_type_graphics_plane)) {
    mp_raise_TypeError(MP_ERROR_TEXT("not a graphics plane"));
    return mp_const_none;
  }
  GraphicsPlane *graphics_plane = MP_OBJ_TO_PTR(args[0]);
  mp_int_t x = mp_obj_get_int(args[1]);
  mp_int_t y = mp_obj_get_int(args[2]);
  mp_int_t width = mp_obj_get_int(args[3]);
  mp_int_t height = mp_obj_get_int(args[4]);
  mp_check_self(mp_obj_is_str_or_bytes(args[5]));
  GET_STR_DATA_LEN(args[5], palette, palette_len);
  mp_int_t bitdepth = mp_obj_get_int(args[6]);
  if ((bitdepth < 0) || (bitdepth > 3)) {
    mp_raise_ValueError(MP_ERROR_TEXT("Invalid bitdepth"));
    return mp_const_none;
  }
  size_t bpp = 1 << bitdepth;
  size_t total_palette = 1 << bpp;
  if (palette_len < (total_palette * 2)) {
    mp_raise_ValueError(MP_ERROR_TEXT("Palette not large enough for bitdepth"));
    return mp_const_none;
  }
  mp_check_self(mp_obj_is_str_or_bytes(args[7]));
  GET_STR_DATA_LEN(args[7], data, data_len);
  if (data_len < ((width * height * bpp + 7) / 8)) {
    mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for bitdepth"));
    return mp_const_none;
  }
  bool double_size = false;
  if (n_args == 9) {
    double_size = mp_obj_is_true(args[8]);
  }
  bool transparent = false;
  if (n_args == 10) {
    transparent = mp_obj_is_true(args[9]);
  }
  SASPPUImageCode res = SASPPU_paletted_sprite(
      graphics_plane, x, y, width, height, double_size, transparent, data,
      (const uint16_t *)palette, bitdepth);
  return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_paletted_obj, 8, 10,
                                    sasppu_paletted);

/**
 * Blit a compressed graphic to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the graphic
 * @param height Height of the graphic
 * @param palette Palette data as bytes or bytearray
 * @param bitdepth Bit depth (0-3) for palette indices
 * @param data The compressed graphic data as bytes or bytearray
 * @param double_size (optional) If true, draw at double size
 * @param transparent (optional) If true, transparent pixels will not be written
 * @return An integer indicating the result of the compressed blit
 */
static mp_obj_t sasppu_compressed(size_t n_args, const mp_obj_t *args) {
  if (!mp_obj_is_type(args[0], &sasppu_type_graphics_plane)) {
    mp_raise_TypeError(MP_ERROR_TEXT("not a graphics plane"));
    return mp_const_none;
  }
  GraphicsPlane *graphics_plane = MP_OBJ_TO_PTR(args[0]);
  mp_int_t x = mp_obj_get_int(args[1]);
  mp_int_t y = mp_obj_get_int(args[2]);
  mp_int_t width = mp_obj_get_int(args[3]);
  mp_int_t height = mp_obj_get_int(args[4]);
  mp_check_self(mp_obj_is_str_or_bytes(args[5]));
  GET_STR_DATA_LEN(args[5], palette, palette_len);
  mp_int_t bitdepth = mp_obj_get_int(args[6]);
  if ((bitdepth < 0) || (bitdepth > 3)) {
    mp_raise_ValueError(MP_ERROR_TEXT("Invalid bitdepth"));
    return mp_const_none;
  }
  size_t bpp = 1 << bitdepth;
  size_t total_palette = 1 << bpp;
  if (palette_len < (total_palette * 2)) {
    mp_raise_ValueError(MP_ERROR_TEXT("Palette not large enough for bitdepth"));
    return mp_const_none;
  }
  mp_check_self(mp_obj_is_str_or_bytes(args[7]));
  GET_STR_DATA_LEN(args[7], data, data_len);
  if (data_len < ((width * height * bpp + 7) / 8)) {
    mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for bitdepth"));
    return mp_const_none;
  }
  bool double_size = false;
  if (n_args == 9) {
    double_size = mp_obj_is_true(args[8]);
  }
  bool transparent = false;
  if (n_args == 10) {
    transparent = mp_obj_is_true(args[9]);
  }
  SASPPUImageCode res = SASPPU_compressed_sprite(
      graphics_plane, x, y, width, height, double_size, transparent, data,
      (const uint16_t *)palette, bitdepth);
  return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_compressed_obj, 8, 10,
                                    sasppu_compressed);

/**
 * Measure multiline text dimensions.
 * @param line_width Maximum line width in pixels
 * @param text The text string to measure
 * @param double_size (optional) If true, measure at double size
 * @param newline_height (optional) Height of newlines in pixels
 * @return Tuple (width, height) of the rendered text
 */
static mp_obj_t sasppu_get_text_size(size_t n_args, const mp_obj_t *args) {
  mp_int_t line_width = mp_obj_get_int(args[0]);
  mp_check_self(mp_obj_is_str_or_bytes(args[1]));
  GET_STR_DATA_LEN(args[1], text, text_len);
  mp_int_t newline_height = 10;
  bool double_size = false;
  if (n_args >= 3) {
    double_size = mp_obj_is_true(args[2]);
  }
  if (n_args == 4) {
    newline_height = mp_obj_get_int(args[3]);
  }
  size_t width;
  size_t height;
  SASPPU_get_text_size(&width, &height, line_width, newline_height, double_size,
                       (const char *)text);
  mp_obj_t tuple_args[2] = {MP_OBJ_NEW_SMALL_INT(width),
                            MP_OBJ_NEW_SMALL_INT(height)};
  return mp_obj_new_tuple(2, tuple_args);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_get_text_size_obj, 2, 4,
                                    sasppu_get_text_size);

static mp_obj_t sasppu_macro_cmath(mp_obj_t col) {
  mp_int_t val = mp_obj_get_int(col);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_CMATH(val));
}

MP_DEFINE_CONST_FUN_OBJ_1(sasppu_macro_cmath_obj, sasppu_macro_cmath);

static mp_obj_t sasppu_macro_rgb555(mp_obj_t r, mp_obj_t g, mp_obj_t b) {
  mp_int_t valr = mp_obj_get_int(r);
  mp_int_t valg = mp_obj_get_int(g);
  mp_int_t valb = mp_obj_get_int(b);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_RGB555(valr, valg, valb));
}

MP_DEFINE_CONST_FUN_OBJ_3(sasppu_macro_rgb555_obj, sasppu_macro_rgb555);

static mp_obj_t sasppu_macro_rgb555_cmath(mp_obj_t r, mp_obj_t g, mp_obj_t b) {
  mp_int_t valr = mp_obj_get_int(r);
  mp_int_t valg = mp_obj_get_int(g);
  mp_int_t valb = mp_obj_get_int(b);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_RGB555_CMATH(valr, valg, valb));
}

MP_DEFINE_CONST_FUN_OBJ_3(sasppu_macro_rgb555_cmath_obj,
                          sasppu_macro_rgb555_cmath);

static mp_obj_t sasppu_macro_rgb888(mp_obj_t r, mp_obj_t g, mp_obj_t b) {
  mp_int_t valr = mp_obj_get_int(r);
  mp_int_t valg = mp_obj_get_int(g);
  mp_int_t valb = mp_obj_get_int(b);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_RGB888(valr, valg, valb));
}

MP_DEFINE_CONST_FUN_OBJ_3(sasppu_macro_rgb888_obj, sasppu_macro_rgb888);

static mp_obj_t sasppu_macro_rgb888_cmath(mp_obj_t r, mp_obj_t g, mp_obj_t b) {
  mp_int_t valr = mp_obj_get_int(r);
  mp_int_t valg = mp_obj_get_int(g);
  mp_int_t valb = mp_obj_get_int(b);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_RGB888_CMATH(valr, valg, valb));
}

MP_DEFINE_CONST_FUN_OBJ_3(sasppu_macro_rgb888_cmath_obj,
                          sasppu_macro_rgb888_cmath);

static mp_obj_t sasppu_macro_grey555(mp_obj_t g) {
  mp_int_t val = mp_obj_get_int(g);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_GREY555(val));
}

MP_DEFINE_CONST_FUN_OBJ_1(sasppu_macro_grey555_obj, sasppu_macro_grey555);

static mp_obj_t sasppu_macro_grey555_cmath(mp_obj_t g) {
  mp_int_t val = mp_obj_get_int(g);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_GREY555_CMATH(val));
}

MP_DEFINE_CONST_FUN_OBJ_1(sasppu_macro_grey555_cmath_obj,
                          sasppu_macro_grey555_cmath);

static mp_obj_t sasppu_macro_mul_channel(mp_obj_t col, mp_obj_t mul) {
  mp_int_t colv = mp_obj_get_int(col);
  mp_int_t mulv = mp_obj_get_int(mul);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_MUL_CHANNEL(colv, mulv));
}

MP_DEFINE_CONST_FUN_OBJ_2(sasppu_macro_mul_channel_obj,
                          sasppu_macro_mul_channel);

static mp_obj_t sasppu_macro_mul_rgb555(size_t n_args, const mp_obj_t *args) {
  mp_int_t valr = mp_obj_get_int(args[0]);
  mp_int_t valg = mp_obj_get_int(args[1]);
  mp_int_t valb = mp_obj_get_int(args[2]);
  mp_int_t mulv = mp_obj_get_int(args[3]);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_MUL_RGB555(valr, valg, valb, mulv));
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_macro_mul_rgb555_obj, 4, 4,
                                    sasppu_macro_mul_rgb555);

static mp_obj_t sasppu_macro_r_channel(mp_obj_t col) {
  mp_int_t val = mp_obj_get_int(col);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_R_CHANNEL(val));
}

MP_DEFINE_CONST_FUN_OBJ_1(sasppu_macro_r_channel_obj, sasppu_macro_r_channel);

static mp_obj_t sasppu_macro_g_channel(mp_obj_t col) {
  mp_int_t val = mp_obj_get_int(col);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_G_CHANNEL(val));
}

MP_DEFINE_CONST_FUN_OBJ_1(sasppu_macro_g_channel_obj, sasppu_macro_g_channel);

static mp_obj_t sasppu_macro_b_channel(mp_obj_t col) {
  mp_int_t val = mp_obj_get_int(col);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_B_CHANNEL(val));
}

MP_DEFINE_CONST_FUN_OBJ_1(sasppu_macro_b_channel_obj, sasppu_macro_b_channel);

static mp_obj_t sasppu_macro_cmath_channel(mp_obj_t col) {
  mp_int_t val = mp_obj_get_int(col);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_CMATH_CHANNEL(val));
}

MP_DEFINE_CONST_FUN_OBJ_1(sasppu_macro_cmath_channel_obj,
                          sasppu_macro_cmath_channel);

static mp_obj_t sasppu_macro_mul_col(mp_obj_t col, mp_obj_t mul) {
  mp_int_t colv = mp_obj_get_int(col);
  mp_int_t mulv = mp_obj_get_int(mul);
  return MP_OBJ_NEW_SMALL_INT(SASPPU_MUL_COL(colv, mulv));
}

MP_DEFINE_CONST_FUN_OBJ_2(sasppu_macro_mul_col_obj, sasppu_macro_mul_col);
