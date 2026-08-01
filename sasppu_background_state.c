// Include the header file to get access to the MicroPython API
#include "sasppu_background_state.h"
#include <string.h>

mp_obj_t sasppu_background_state_default(mp_obj_t self_in) {
  BackgroundState *self = MP_OBJ_TO_PTR(self_in);
  memset(&self->scroll_x, 0, sizeof(BackgroundState) - sizeof(mp_obj_base_t));
  self->scroll_x = 0;
  self->scroll_y = 0;
  self->windows = 0xFF;
  self->flags = 0;
  return mp_const_none;
}

static mp_obj_t sasppu_background_state_make_new(const mp_obj_type_t *type,
                                                 size_t n_args, size_t n_kw,
                                                 const mp_obj_t *args_in) {
  BackgroundState *o = mp_obj_malloc(BackgroundState, type);

  sasppu_background_state_default(MP_OBJ_FROM_PTR(o));

  return MP_OBJ_FROM_PTR(o);
}

static mp_obj_t sasppu_background_state_binary_op(mp_binary_op_t op,
                                                  mp_obj_t lhs_in,
                                                  mp_obj_t rhs_in) {
  BackgroundState *self = MP_OBJ_TO_PTR(lhs_in);
  BackgroundState *other = MP_OBJ_TO_PTR(rhs_in);
  switch (op) {
  case MP_BINARY_OP_EQUAL: {
    return memcmp(&self->scroll_x, &other->scroll_x,
                  sizeof(BackgroundState) - sizeof(mp_obj_base_t))
               ? mp_const_true
               : mp_const_false;
  }
  default:
    // op not supported
    return MP_OBJ_NULL;
  }
}

static void sasppu_background_state_attr(mp_obj_t self_in, qstr attr,
                                         mp_obj_t *dest) {
  BackgroundState *self = MP_OBJ_TO_PTR(self_in);
  if (dest[0] == MP_OBJ_NULL) {
    // Load attribute.
    switch (attr) {
    case MP_QSTR_scroll_x:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->scroll_x);
      break;
    case MP_QSTR_scroll_y:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->scroll_y);
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
    case MP_QSTR_scroll_x:
      if ((val < -0x8000) || (val > 0x7FFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Position value out of bounds"));
      } else {
        self->scroll_x = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_scroll_y:
      if ((val < -0x8000) || (val > 0x7FFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Position value out of bounds"));
      } else {
        self->scroll_y = val;
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
        self->windows |= (val << 4);
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

static const mp_rom_map_elem_t sasppu_background_state_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_C_MATH), MP_ROM_INT(BG_C_MATH)},
};
static MP_DEFINE_CONST_DICT(sasppu_background_state_locals_dict,
                            sasppu_background_state_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(sasppu_type_background_state, MP_QSTR_BackgroundState,
                         MP_TYPE_FLAG_NONE, make_new,
                         sasppu_background_state_make_new, locals_dict,
                         &sasppu_background_state_locals_dict, binary_op,
                         sasppu_background_state_binary_op, attr,
                         sasppu_background_state_attr);
