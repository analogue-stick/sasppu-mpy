#include "sasppu_sprite.h"
#include <string.h>

mp_obj_t sasppu_sprite_default(mp_obj_t self_in) {
  Sprite *self = MP_OBJ_TO_PTR(self_in);
  memset(&self->x, 0, sizeof(Sprite) - sizeof(mp_obj_base_t));
  self->x = 0;
  self->y = 0;
  self->width = 8;
  self->height = 8;
  self->graphics_x = 0;
  self->graphics_y = 0;
  self->flags = 0;
  self->windows = 0xFF;
  return mp_const_none;
}

static mp_obj_t sasppu_sprite_make_new(const mp_obj_type_t *type, size_t n_args,
                                       size_t n_kw, const mp_obj_t *args_in) {
  Sprite *o = mp_obj_malloc(Sprite, type);

  sasppu_sprite_default(MP_OBJ_FROM_PTR(o));

  return MP_OBJ_FROM_PTR(o);
}

static mp_obj_t sasppu_sprite_binary_op(mp_binary_op_t op, mp_obj_t lhs_in,
                                        mp_obj_t rhs_in) {
  Sprite *self = MP_OBJ_TO_PTR(lhs_in);
  Sprite *other = MP_OBJ_TO_PTR(rhs_in);
  switch (op) {
  case MP_BINARY_OP_EQUAL: {
    return memcmp(&self->x, &other->x, sizeof(Sprite) - sizeof(mp_obj_base_t))
               ? mp_const_true
               : mp_const_false;
  }
  default:
    // op not supported
    return MP_OBJ_NULL;
  }
}

static void sasppu_sprite_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest) {
  Sprite *self = MP_OBJ_TO_PTR(self_in);
  if (dest[0] == MP_OBJ_NULL) {
    // Load attribute.
    switch (attr) {
    case MP_QSTR_x:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->x);
      break;
    case MP_QSTR_y:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->y);
      break;
    case MP_QSTR_width:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->width);
      break;
    case MP_QSTR_height:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->height);
      break;
    case MP_QSTR_graphics_x:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->graphics_x);
      break;
    case MP_QSTR_graphics_y:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->graphics_y);
      break;
    case MP_QSTR_windows:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->windows);
      break;
    case MP_QSTR_window_1:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->windows & 0x0F);
      break;
    case MP_QSTR_window_2:
      dest[0] = MP_OBJ_NEW_SMALL_INT((self->windows >> 4) & 0x0F);
      break;
    case MP_QSTR_flags:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->flags);
      break;
    default:
      dest[1] = MP_OBJ_SENTINEL;
      break;
    }
  } else if (dest[1] != MP_OBJ_NULL) {
    // Store attribute.
    mp_int_t val = mp_obj_get_int(dest[1]);
    switch (attr) {
    case MP_QSTR_x:
      if ((val < -0x8000) || (val > 0x7FFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Position value out of bounds"));
      } else {
        self->x = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_y:
      if ((val < -0x8000) || (val > 0x7FFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Position value out of bounds"));
      } else {
        self->y = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_width:
      if ((val < 0) || (val > 0xFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Dimension out of bounds"));
      } else if ((val & 0x7) > 0) {
        mp_raise_ValueError(MP_ERROR_TEXT("Width must be multiple of 8"));
      } else {
        self->width = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_height:
      if ((val < 0) || (val > 0xFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Dimension out of bounds"));
      } else {
        self->height = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_graphics_x:
      if ((val < 0) || (val > 0xFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Graphics position out of bounds"));
      } else if ((val & 0x7) > 0) {
        mp_raise_ValueError(
            MP_ERROR_TEXT("Graphics x position must be multiple of 8"));
      } else {
        self->graphics_x = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_graphics_y:
      if ((val < 0) || (val > 0xFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Graphics position out of bounds"));
      } else {
        self->graphics_y = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_windows:
      if ((val < 0) || (val > 0xFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Windows out of bounds"));
      } else {
        self->windows = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_window_1:
      if ((val < 0) || (val > 0xF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Window out of bounds"));
      } else {
        self->windows &= 0xF0;
        self->windows |= val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_window_2:
      if ((val < 0) || (val > 0xF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Window out of bounds"));
      } else {
        self->windows &= 0x0F;
        self->windows |= val << 4;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_flags:
      if ((val < 0) || (val > 0xFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Flags out of bounds"));
      } else {
        self->flags = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    default:
      break;
    }
  }
}

static const mp_rom_map_elem_t sasppu_sprite_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_USER_TYPE), MP_ROM_INT(SPR_USER_TYPE)},
    {MP_ROM_QSTR(MP_QSTR_ENABLED), MP_ROM_INT(SPR_ENABLED)},
    {MP_ROM_QSTR(MP_QSTR_FLIP_X), MP_ROM_INT(SPR_FLIP_X)},
    {MP_ROM_QSTR(MP_QSTR_FLIP_Y), MP_ROM_INT(SPR_FLIP_Y)},
    {MP_ROM_QSTR(MP_QSTR_C_MATH), MP_ROM_INT(SPR_C_MATH)},
    {MP_ROM_QSTR(MP_QSTR_DOUBLE), MP_ROM_INT(SPR_DOUBLE)},
};
static MP_DEFINE_CONST_DICT(sasppu_sprite_locals_dict,
                            sasppu_sprite_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(sasppu_type_sprite, MP_QSTR_Sprite, MP_TYPE_FLAG_NONE,
                         make_new, sasppu_sprite_make_new, locals_dict,
                         &sasppu_sprite_locals_dict, binary_op,
                         sasppu_sprite_binary_op, attr, sasppu_sprite_attr);
