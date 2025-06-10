#include "sasppu_mpy_help.h"

/**
 * Copy a sprite block to the screen.
 * @param dst_x X coordinate to copy to
 * @param dst_y Y coordinate to copy to
 * @param width Width of the block to copy
 * @param height Height of the block to copy
 * @param src_x Source X coordinate in sprite memory
 * @param src_y Source Y coordinate in sprite memory
 * @param double_size (optional) If true, copy at double size
 * @return An integer indicating the result of the copy operation
 */
static mp_obj_t sasppu_copy_sprite(size_t n_args, const mp_obj_t *args)
{
    mp_int_t dst_x = mp_obj_get_int(args[0]);
    mp_int_t dst_y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_int_t src_x = mp_obj_get_int(args[4]);
    mp_int_t src_y = mp_obj_get_int(args[5]);
    bool double_size = false;
    if (n_args == 7)
    {
        double_size = mp_obj_is_true(args[6]);
    }
    SASPPUImageCode res = SASPPU_copy_sprite(dst_x, dst_y, width, height, src_x, src_y, double_size);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_copy_sprite_obj, 6, 7, sasppu_copy_sprite);

/**
 * Copy a sprite block with transparency to the screen.
 * @param dst_x X coordinate to copy to
 * @param dst_y Y coordinate to copy to
 * @param width Width of the block to copy
 * @param height Height of the block to copy
 * @param src_x Source X coordinate in sprite memory
 * @param src_y Source Y coordinate in sprite memory
 * @param double_size (optional) If true, copy at double size
 * @return An integer indicating the result of the transparent copy operation
 */
static mp_obj_t sasppu_copy_sprite_transparent(size_t n_args, const mp_obj_t *args)
{
    mp_int_t dst_x = mp_obj_get_int(args[0]);
    mp_int_t dst_y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_int_t src_x = mp_obj_get_int(args[4]);
    mp_int_t src_y = mp_obj_get_int(args[5]);
    bool double_size = false;
    if (n_args == 7)
    {
        double_size = mp_obj_is_true(args[6]);
    }
    SASPPUImageCode res = SASPPU_copy_sprite_transparent(dst_x, dst_y, width, height, src_x, src_y, double_size);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_copy_sprite_transparent_obj, 6, 7, sasppu_copy_sprite_transparent);

/**
 * Fill a rectangular sprite area with a solid color.
 * @param x X coordinate of the area
 * @param y Y coordinate of the area
 * @param width Width of the area to fill
 * @param height Height of the area to fill
 * @param colour Color value to fill with
 * @return An integer indicating the result of the fill operation
 */
static mp_obj_t sasppu_fill_sprite(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_int_t colour = mp_obj_get_int(args[4]);
    SASPPUImageCode res = SASPPU_fill_sprite(x, y, width, height, colour);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_fill_sprite_obj, 5, 5, sasppu_fill_sprite);

/**
 * Draw multiline text onto a sprite layer.
 * @param x X coordinate to start drawing
 * @param y Y coordinate to start drawing
 * @param colour Text color value
 * @param line_width Maximum line width in pixels
 * @param text The text string to draw
 * @param double_size (optional) If true, draw text at double size
 * @param newline_height (optional) Height of newlines in pixels
 * @return An integer indicating the result of the text draw operation
 */
static mp_obj_t sasppu_draw_text_sprite(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t colour = mp_obj_get_int(args[2]);
    mp_int_t line_width = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], text, text_len);
    mp_int_t newline_height = 10;
    bool double_size = false;
    if (n_args >= 6)
    {
        double_size = mp_obj_is_true(args[5]);
    }
    if (n_args == 7)
    {
        newline_height = mp_obj_get_int(args[6]);
    }
    SASPPUImageCode res = SASPPU_draw_text_sprite(x, y, colour, line_width, newline_height, double_size, (const char *)text);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_draw_text_sprite_obj, 5, 7, sasppu_draw_text_sprite);

/**
 * Draw text onto a sprite layer and return next cursor position.
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
static mp_obj_t sasppu_draw_text_next_sprite(size_t n_args, const mp_obj_t *args)
{
    size_t x = mp_obj_get_int(args[0]);
    size_t y = mp_obj_get_int(args[1]);
    mp_int_t colour = mp_obj_get_int(args[2]);
    mp_int_t line_start = mp_obj_get_int(args[3]);
    mp_int_t line_width = mp_obj_get_int(args[4]);
    mp_check_self(mp_obj_is_str_or_bytes(args[5]));
    GET_STR_DATA_LEN(args[5], text, text_len);
    mp_int_t newline_height = 10;
    bool double_size = false;
    if (n_args >= 7)
    {
        double_size = mp_obj_is_true(args[6]);
    }
    if (n_args == 8)
    {
        newline_height = mp_obj_get_int(args[7]);
    }
    SASPPUImageCode res = SASPPU_draw_text_next_sprite(&x, &y, colour, line_start, line_width, newline_height, double_size, (const char **)&text);
    mp_obj_t tuple_args[3] = {MP_OBJ_NEW_SMALL_INT(res), MP_OBJ_NEW_SMALL_INT(x), MP_OBJ_NEW_SMALL_INT(y)};
    return mp_obj_new_tuple(3, tuple_args);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_draw_text_next_sprite_obj, 6, 8, sasppu_draw_text_next_sprite);

/**
 * Blit a sprite to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the sprite
 * @param height Height of the sprite
 * @param data The sprite data as a bytes or bytearray object
 * @param double_size (optional) If true, the sprite will be drawn at double size
 * @return An integer indicating the result of the blit operation
 */
static mp_obj_t sasppu_blit_sprite(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], data, data_len);
    if (data_len < (width * height * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for size"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 6)
    {
        double_size = mp_obj_is_true(args[5]);
    }
    SASPPUImageCode res = SASPPU_blit_sprite(x, y, width, height, double_size, (const uint16_t *)data);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_blit_sprite_obj, 5, 6, sasppu_blit_sprite);

/**
 * Blit a sprite with transparency to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the sprite
 * @param height Height of the sprite
 * @param data The sprite data as a bytes or bytearray object
 * @param double_size (optional) If true, the sprite will be drawn at double size
 * @return An integer indicating the result of the transparent blit operation
 */
static mp_obj_t sasppu_blit_sprite_transparent(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], data, data_len);
    if (data_len < (width * height * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for size"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 6)
    {
        double_size = mp_obj_is_true(args[5]);
    }
    SASPPUImageCode res = SASPPU_blit_sprite_transparent(x, y, width, height, double_size, (const uint16_t *)data);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_blit_sprite_transparent_obj, 5, 6, sasppu_blit_sprite_transparent);

/**
 * Blit a paletted sprite to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the sprite
 * @param height Height of the sprite
 * @param palette Palette data as bytes or bytearray
 * @param bitdepth Bit depth (0-3) for palette indices
 * @param data The sprite index data as bytes or bytearray
 * @param double_size (optional) If true, draw at double size
 * @return An integer indicating the result of the paletted blit
 */
static mp_obj_t sasppu_paletted_sprite(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], palette, palette_len);
    mp_int_t bitdepth = mp_obj_get_int(args[5]);
    if ((bitdepth < 0) || (bitdepth > 3))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid bitdepth"));
        return mp_const_none;
    }
    size_t bpp = 1 << bitdepth;
    size_t total_palette = 1 << bpp;
    if (palette_len < (total_palette * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Palette not large enough for bitdepth"));
        return mp_const_none;
    }
    mp_check_self(mp_obj_is_str_or_bytes(args[6]));
    GET_STR_DATA_LEN(args[6], data, data_len);
    if (data_len < ((width * height * bpp + 7) / 8))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for bitdepth"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 8)
    {
        double_size = mp_obj_is_true(args[7]);
    }
    SASPPUImageCode res = SASPPU_paletted_sprite(x, y, width, height, double_size, data, (const uint16_t *)palette, bitdepth);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_paletted_sprite_obj, 7, 8, sasppu_paletted_sprite);

/**
 * Blit a paletted sprite with transparency to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the sprite
 * @param height Height of the sprite
 * @param palette Palette data as bytes or bytearray
 * @param bitdepth Bit depth (0-3) for palette indices
 * @param data The sprite index data as bytes or bytearray
 * @param double_size (optional) If true, draw at double size
 * @return An integer indicating the result of the transparent paletted blit
 */
static mp_obj_t sasppu_paletted_sprite_transparent(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], palette, palette_len);
    mp_int_t bitdepth = mp_obj_get_int(args[5]);
    if ((bitdepth < 0) || (bitdepth > 3))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid bitdepth"));
        return mp_const_none;
    }
    size_t bpp = 1 << bitdepth;
    size_t total_palette = 1 << bpp;
    if (palette_len < (total_palette * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Palette not large enough for bitdepth"));
        return mp_const_none;
    }
    mp_check_self(mp_obj_is_str_or_bytes(args[6]));
    GET_STR_DATA_LEN(args[6], data, data_len);
    if (data_len < ((width * height * bpp + 7) / 8))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for bitdepth"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 8)
    {
        double_size = mp_obj_is_true(args[7]);
    }
    SASPPUImageCode res = SASPPU_paletted_sprite_transparent(x, y, width, height, double_size, data, (const uint16_t *)palette, bitdepth);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_paletted_sprite_transparent_obj, 7, 8, sasppu_paletted_sprite_transparent);

/**
 * Blit a compressed sprite to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the sprite
 * @param height Height of the sprite
 * @param palette Palette data as bytes or bytearray
 * @param bitdepth Bit depth (0-3) for palette indices
 * @param data The compressed sprite data as bytes or bytearray
 * @param double_size (optional) If true, draw at double size
 * @return An integer indicating the result of the compressed blit
 */
static mp_obj_t sasppu_compressed_sprite(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], palette, palette_len);
    mp_int_t bitdepth = mp_obj_get_int(args[5]);
    if ((bitdepth < 0) || (bitdepth > 3))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid bitdepth"));
        return mp_const_none;
    }
    size_t bpp = 1 << bitdepth;
    size_t total_palette = 1 << bpp;
    if (palette_len < (total_palette * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Palette not large enough for bitdepth"));
        return mp_const_none;
    }
    mp_check_self(mp_obj_is_str_or_bytes(args[6]));
    GET_STR_DATA_LEN(args[6], data, data_len);
    if (data_len < ((width * height * bpp + 7) / 8))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for bitdepth"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 8)
    {
        double_size = mp_obj_is_true(args[7]);
    }
    SASPPUImageCode res = SASPPU_compressed_sprite(x, y, width, height, double_size, data, (const uint16_t *)palette, bitdepth);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_compressed_sprite_obj, 7, 8, sasppu_compressed_sprite);

/**
 * Blit a compressed sprite with transparency to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the sprite
 * @param height Height of the sprite
 * @param palette Palette data as bytes or bytearray
 * @param bitdepth Bit depth (0-3) for palette indices
 * @param data The compressed sprite data as bytes or bytearray
 * @param double_size (optional) If true, draw at double size
 * @return An integer indicating the result of the transparent compressed blit
 */
static mp_obj_t sasppu_compressed_sprite_transparent(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], palette, palette_len);
    mp_int_t bitdepth = mp_obj_get_int(args[5]);
    if ((bitdepth < 0) || (bitdepth > 3))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid bitdepth"));
        return mp_const_none;
    }
    size_t bpp = 1 << bitdepth;
    size_t total_palette = 1 << bpp;
    if (palette_len < (total_palette * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Palette not large enough for bitdepth"));
        return mp_const_none;
    }
    mp_check_self(mp_obj_is_str_or_bytes(args[6]));
    GET_STR_DATA_LEN(args[6], data, data_len);
    if (data_len < ((width * height * bpp + 7) / 8))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for bitdepth"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 8)
    {
        double_size = mp_obj_is_true(args[7]);
    }
    SASPPUImageCode res = SASPPU_compressed_sprite_transparent(x, y, width, height, double_size, data, (const uint16_t *)palette, bitdepth);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_compressed_sprite_transparent_obj, 7, 8, sasppu_compressed_sprite_transparent);

/**
 * Copy a background block to the screen.
 * @param dst_x X coordinate to copy to
 * @param dst_y Y coordinate to copy to
 * @param width Width of the block to copy
 * @param height Height of the block to copy
 * @param src_x Source X coordinate in background map
 * @param src_y Source Y coordinate in background map
 * @param double_size (optional) If true, copy at double size
 * @return An integer indicating the result of the copy operation
 */
static mp_obj_t sasppu_copy_background(size_t n_args, const mp_obj_t *args)
{
    mp_int_t dst_x = mp_obj_get_int(args[0]);
    mp_int_t dst_y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_int_t src_x = mp_obj_get_int(args[4]);
    mp_int_t src_y = mp_obj_get_int(args[5]);
    bool double_size = false;
    if (n_args == 7)
    {
        double_size = mp_obj_is_true(args[6]);
    }
    SASPPUImageCode res = SASPPU_copy_background(dst_x, dst_y, width, height, src_x, src_y, double_size);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_copy_background_obj, 6, 7, sasppu_copy_background);

/**
 * Copy a background block with transparency to the screen.
 * @param dst_x X coordinate to copy to
 * @param dst_y Y coordinate to copy to
 * @param width Width of the block to copy
 * @param height Height of the block to copy
 * @param src_x Source X coordinate in background map
 * @param src_y Source Y coordinate in background map
 * @param double_size (optional) If true, copy at double size
 * @return An integer indicating the result of the transparent copy operation
 */
static mp_obj_t sasppu_copy_background_transparent(size_t n_args, const mp_obj_t *args)
{
    mp_int_t dst_x = mp_obj_get_int(args[0]);
    mp_int_t dst_y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_int_t src_x = mp_obj_get_int(args[4]);
    mp_int_t src_y = mp_obj_get_int(args[5]);
    bool double_size = false;
    if (n_args == 7)
    {
        double_size = mp_obj_is_true(args[6]);
    }
    SASPPUImageCode res = SASPPU_copy_background_transparent(dst_x, dst_y, width, height, src_x, src_y, double_size);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_copy_background_transparent_obj, 6, 7, sasppu_copy_background_transparent);

/**
 * Fill a rectangular background area with a solid color.
 * @param x X coordinate of the area
 * @param y Y coordinate of the area
 * @param width Width of the area to fill
 * @param height Height of the area to fill
 * @param colour Color value to fill with
 * @return An integer indicating the result of the fill operation
 */
static mp_obj_t sasppu_fill_background(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_int_t colour = mp_obj_get_int(args[4]);
    SASPPUImageCode res = SASPPU_fill_background(x, y, width, height, colour);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_fill_background_obj, 5, 5, sasppu_fill_background);

/**
 * Draw multiline text onto a background layer.
 * @param x X coordinate to start drawing
 * @param y Y coordinate to start drawing
 * @param colour Text color value
 * @param line_width Maximum line width in pixels
 * @param text The text string to draw
 * @param double_size (optional) If true, draw text at double size
 * @param newline_height (optional) Height of newlines in pixels
 * @return An integer indicating the result of the text draw operation
 */
static mp_obj_t sasppu_draw_text_background(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t colour = mp_obj_get_int(args[2]);
    mp_int_t line_width = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], text, text_len);
    mp_int_t newline_height = 10;
    bool double_size = false;
    if (n_args >= 6)
    {
        double_size = mp_obj_is_true(args[5]);
    }
    if (n_args == 7)
    {
        newline_height = mp_obj_get_int(args[6]);
    }
    SASPPUImageCode res = SASPPU_draw_text_background(x, y, colour, line_width, newline_height, double_size, (const char *)text);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_draw_text_background_obj, 5, 7, sasppu_draw_text_background);

/**
 * Draw text onto a background layer and return next cursor position.
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
static mp_obj_t sasppu_draw_text_next_background(size_t n_args, const mp_obj_t *args)
{
    size_t x = mp_obj_get_int(args[0]);
    size_t y = mp_obj_get_int(args[1]);
    mp_int_t colour = mp_obj_get_int(args[2]);
    mp_int_t line_start = mp_obj_get_int(args[3]);
    mp_int_t line_width = mp_obj_get_int(args[4]);
    mp_check_self(mp_obj_is_str_or_bytes(args[5]));
    GET_STR_DATA_LEN(args[5], text, text_len);
    mp_int_t newline_height = 10;
    bool double_size = false;
    if (n_args >= 7)
    {
        double_size = mp_obj_is_true(args[6]);
    }
    if (n_args == 8)
    {
        newline_height = mp_obj_get_int(args[7]);
    }
    SASPPUImageCode res = SASPPU_draw_text_next_background(&x, &y, colour, line_start, line_width, newline_height, double_size, (const char **)&text);
    mp_obj_t tuple_args[3] = {MP_OBJ_NEW_SMALL_INT(res), MP_OBJ_NEW_SMALL_INT(x), MP_OBJ_NEW_SMALL_INT(y)};
    return mp_obj_new_tuple(3, tuple_args);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_draw_text_next_background_obj, 6, 8, sasppu_draw_text_next_background);

/**
 * Blit a background image to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the image
 * @param height Height of the image
 * @param data The background data as a bytes or bytearray object
 * @param double_size (optional) If true, the image will be drawn at double size
 * @return An integer indicating the result of the blit operation
 */
static mp_obj_t sasppu_blit_background(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], data, data_len);
    if (data_len < (width * height * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for size"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 6)
    {
        double_size = mp_obj_is_true(args[5]);
    }
    SASPPUImageCode res = SASPPU_blit_background(x, y, width, height, double_size, (const uint16_t *)data);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_blit_background_obj, 5, 6, sasppu_blit_background);

/**
 * Blit a background image with transparency to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the image
 * @param height Height of the image
 * @param data The background data as a bytes or bytearray object
 * @param double_size (optional) If true, the image will be drawn at double size
 * @return An integer indicating the result of the transparent blit operation
 */
static mp_obj_t sasppu_blit_background_transparent(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], data, data_len);
    if (data_len < (width * height * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for size"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 6)
    {
        double_size = mp_obj_is_true(args[5]);
    }
    SASPPUImageCode res = SASPPU_blit_background_transparent(x, y, width, height, double_size, (const uint16_t *)data);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_blit_background_transparent_obj, 5, 6, sasppu_blit_background_transparent);

/**
 * Blit a paletted background to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the background
 * @param height Height of the background
 * @param palette Palette data as bytes or bytearray
 * @param bitdepth Bit depth (0-3) for palette indices
 * @param data The background index data as bytes or bytearray
 * @param double_size (optional) If true, draw at double size
 * @return An integer indicating the result of the paletted blit
 */
static mp_obj_t sasppu_paletted_background(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], palette, palette_len);
    mp_int_t bitdepth = mp_obj_get_int(args[5]);
    if ((bitdepth < 0) || (bitdepth > 3))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid bitdepth"));
        return mp_const_none;
    }
    size_t bpp = 1 << bitdepth;
    size_t total_palette = 1 << bpp;
    if (palette_len < (total_palette * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Palette not large enough for bitdepth"));
        return mp_const_none;
    }
    mp_check_self(mp_obj_is_str_or_bytes(args[6]));
    GET_STR_DATA_LEN(args[6], data, data_len);
    if (data_len < ((width * height * bpp + 7) / 8))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for bitdepth"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 8)
    {
        double_size = mp_obj_is_true(args[7]);
    }
    SASPPUImageCode res = SASPPU_paletted_background(x, y, width, height, double_size, data, (const uint16_t *)palette, bitdepth);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_paletted_background_obj, 7, 8, sasppu_paletted_background);

/**
 * Blit a paletted background with transparency to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the background
 * @param height Height of the background
 * @param palette Palette data as bytes or bytearray
 * @param bitdepth Bit depth (0-3) for palette indices
 * @param data The background index data as bytes or bytearray
 * @param double_size (optional) If true, draw at double size
 * @return An integer indicating the result of the transparent paletted blit
 */
static mp_obj_t sasppu_paletted_background_transparent(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], palette, palette_len);
    mp_int_t bitdepth = mp_obj_get_int(args[5]);
    if ((bitdepth < 0) || (bitdepth > 3))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid bitdepth"));
        return mp_const_none;
    }
    size_t bpp = 1 << bitdepth;
    size_t total_palette = 1 << bpp;
    if (palette_len < (total_palette * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Palette not large enough for bitdepth"));
        return mp_const_none;
    }
    mp_check_self(mp_obj_is_str_or_bytes(args[6]));
    GET_STR_DATA_LEN(args[6], data, data_len);
    if (data_len < ((width * height * bpp + 7) / 8))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for bitdepth"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 8)
    {
        double_size = mp_obj_is_true(args[7]);
    }
    SASPPUImageCode res = SASPPU_paletted_background_transparent(x, y, width, height, double_size, data, (const uint16_t *)palette, bitdepth);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_paletted_background_transparent_obj, 7, 8, sasppu_paletted_background_transparent);

/**
 * Blit a compressed background to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the background
 * @param height Height of the background
 * @param palette Palette data as bytes or bytearray
 * @param bitdepth Bit depth (0-3) for palette indices
 * @param data The compressed background data as bytes or bytearray
 * @param double_size (optional) If true, draw at double size
 * @return An integer indicating the result of the compressed blit
 */
static mp_obj_t sasppu_compressed_background(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], palette, palette_len);
    mp_int_t bitdepth = mp_obj_get_int(args[5]);
    if ((bitdepth < 0) || (bitdepth > 3))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid bitdepth"));
        return mp_const_none;
    }
    size_t bpp = 1 << bitdepth;
    size_t total_palette = 1 << bpp;
    if (palette_len < (total_palette * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Palette not large enough for bitdepth"));
        return mp_const_none;
    }
    mp_check_self(mp_obj_is_str_or_bytes(args[6]));
    GET_STR_DATA_LEN(args[6], data, data_len);
    if (data_len < ((width * height * bpp + 7) / 8))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for bitdepth"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 8)
    {
        double_size = mp_obj_is_true(args[7]);
    }
    SASPPUImageCode res = SASPPU_compressed_background(x, y, width, height, double_size, data, (const uint16_t *)palette, bitdepth);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_compressed_background_obj, 7, 8, sasppu_compressed_background);

/**
 * Blit a compressed background with transparency to the screen.
 * @param x X coordinate to blit to
 * @param y Y coordinate to blit to
 * @param width Width of the background
 * @param height Height of the background
 * @param palette Palette data as bytes or bytearray
 * @param bitdepth Bit depth (0-3) for palette indices
 * @param data The compressed background data as bytes or bytearray
 * @param double_size (optional) If true, draw at double size
 * @return An integer indicating the result of the transparent compressed blit
 */
static mp_obj_t sasppu_compressed_background_transparent(size_t n_args, const mp_obj_t *args)
{
    mp_int_t x = mp_obj_get_int(args[0]);
    mp_int_t y = mp_obj_get_int(args[1]);
    mp_int_t width = mp_obj_get_int(args[2]);
    mp_int_t height = mp_obj_get_int(args[3]);
    mp_check_self(mp_obj_is_str_or_bytes(args[4]));
    GET_STR_DATA_LEN(args[4], palette, palette_len);
    mp_int_t bitdepth = mp_obj_get_int(args[5]);
    if ((bitdepth < 0) || (bitdepth > 3))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid bitdepth"));
        return mp_const_none;
    }
    size_t bpp = 1 << bitdepth;
    size_t total_palette = 1 << bpp;
    if (palette_len < (total_palette * 2))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Palette not large enough for bitdepth"));
        return mp_const_none;
    }
    mp_check_self(mp_obj_is_str_or_bytes(args[6]));
    GET_STR_DATA_LEN(args[6], data, data_len);
    if (data_len < ((width * height * bpp + 7) / 8))
    {
        mp_raise_ValueError(MP_ERROR_TEXT("Data not large enough for bitdepth"));
        return mp_const_none;
    }
    bool double_size = false;
    if (n_args == 8)
    {
        double_size = mp_obj_is_true(args[7]);
    }
    SASPPUImageCode res = SASPPU_compressed_background_transparent(x, y, width, height, double_size, data, (const uint16_t *)palette, bitdepth);
    return MP_OBJ_NEW_SMALL_INT(res);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_compressed_background_transparent_obj, 7, 8, sasppu_compressed_background_transparent);

/**
 * Measure multiline text dimensions.
 * @param line_width Maximum line width in pixels
 * @param text The text string to measure
 * @param double_size (optional) If true, measure at double size
 * @param newline_height (optional) Height of newlines in pixels
 * @return Tuple (width, height) of the rendered text
 */
static mp_obj_t sasppu_get_text_size(size_t n_args, const mp_obj_t *args)
{
    mp_int_t line_width = mp_obj_get_int(args[0]);
    mp_check_self(mp_obj_is_str_or_bytes(args[1]));
    GET_STR_DATA_LEN(args[1], text, text_len);
    mp_int_t newline_height = 10;
    bool double_size = false;
    if (n_args >= 3)
    {
        double_size = mp_obj_is_true(args[2]);
    }
    if (n_args == 4)
    {
        newline_height = mp_obj_get_int(args[3]);
    }
    size_t width;
    size_t height;
    SASPPU_get_text_size(&width, &height, line_width, newline_height, double_size, (const char *)text);
    mp_obj_t tuple_args[2] = {MP_OBJ_NEW_SMALL_INT(width), MP_OBJ_NEW_SMALL_INT(height)};
    return mp_obj_new_tuple(2, tuple_args);
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_get_text_size_obj, 2, 4, sasppu_get_text_size);

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

MP_DEFINE_CONST_FUN_OBJ_3(sasppu_macro_rgb555_cmath_obj, sasppu_macro_rgb555_cmath);

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

MP_DEFINE_CONST_FUN_OBJ_3(sasppu_macro_rgb888_cmath_obj, sasppu_macro_rgb888_cmath);

static mp_obj_t sasppu_macro_grey555(mp_obj_t g) {
    mp_int_t val = mp_obj_get_int(g);
    return MP_OBJ_NEW_SMALL_INT(SASPPU_GREY555(val));
}

MP_DEFINE_CONST_FUN_OBJ_1(sasppu_macro_grey555_obj, sasppu_macro_grey555);

static mp_obj_t sasppu_macro_grey555_cmath(mp_obj_t g) {
    mp_int_t val = mp_obj_get_int(g);
    return MP_OBJ_NEW_SMALL_INT(SASPPU_GREY555_CMATH(val));
}

MP_DEFINE_CONST_FUN_OBJ_1(sasppu_macro_grey555_cmath_obj, sasppu_macro_grey555_cmath);

static mp_obj_t sasppu_macro_mul_channel(mp_obj_t col, mp_obj_t mul) {
    mp_int_t colv = mp_obj_get_int(col);
    mp_int_t mulv = mp_obj_get_int(mul);
    return MP_OBJ_NEW_SMALL_INT(SASPPU_MUL_CHANNEL(colv, mulv));
}

MP_DEFINE_CONST_FUN_OBJ_2(sasppu_macro_mul_channel_obj, sasppu_macro_mul_channel);

static mp_obj_t sasppu_macro_mul_rgb555(size_t n_args, const mp_obj_t *args) {
    mp_int_t valr = mp_obj_get_int(args[0]);
    mp_int_t valg = mp_obj_get_int(args[1]);
    mp_int_t valb = mp_obj_get_int(args[2]);
    mp_int_t mulv = mp_obj_get_int(args[3]);
    return MP_OBJ_NEW_SMALL_INT(SASPPU_MUL_RGB555(valr, valg, valb, mulv));
}

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(sasppu_macro_mul_rgb555_obj, 4, 4, sasppu_macro_mul_rgb555);

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

MP_DEFINE_CONST_FUN_OBJ_1(sasppu_macro_cmath_channel_obj, sasppu_macro_cmath_channel);

static mp_obj_t sasppu_macro_mul_col(mp_obj_t col, mp_obj_t mul) {
    mp_int_t colv = mp_obj_get_int(col);
    mp_int_t mulv = mp_obj_get_int(mul);
    return MP_OBJ_NEW_SMALL_INT(SASPPU_MUL_COL(colv, mulv));
}

MP_DEFINE_CONST_FUN_OBJ_2(sasppu_macro_mul_col_obj, sasppu_macro_mul_col);
