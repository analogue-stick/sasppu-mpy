#include "sasppu_cmath_state.h"
#include <string.h>

mp_obj_t sasppu_cmath_state_default(mp_obj_t self_in) {
  CMathState *self = MP_OBJ_TO_PTR(self_in);
  memset(&self->screen_fade, 0, sizeof(CMathState) - sizeof(mp_obj_base_t));
  self->screen_fade = 255;
  self->flags = 0;
  return mp_const_none;
}

static mp_obj_t sasppu_cmath_state_make_new(const mp_obj_type_t *type,
                                            size_t n_args, size_t n_kw,
                                            const mp_obj_t *args_in) {
  CMathState *o = mp_obj_malloc(CMathState, type);

  sasppu_cmath_state_default(MP_OBJ_FROM_PTR(o));
  

  return MP_OBJ_FROM_PTR(o);
}

static mp_obj_t sasppu_cmath_state_binary_op(mp_binary_op_t op, mp_obj_t lhs_in,
                                             mp_obj_t rhs_in) {
  CMathState *self = MP_OBJ_TO_PTR(lhs_in);
  CMathState *other = MP_OBJ_TO_PTR(rhs_in);
  switch (op) {
  case MP_BINARY_OP_EQUAL: {
    return memcmp(&self->screen_fade, &other->screen_fade,
                  sizeof(CMathState) - sizeof(mp_obj_base_t))
               ? mp_const_true
               : mp_const_false;
  }
  default:
    // op not supported
    return MP_OBJ_NULL;
  }
}

static void sasppu_cmath_state_attr(mp_obj_t self_in, qstr attr,
                                    mp_obj_t *dest) {
  CMathState *self = MP_OBJ_TO_PTR(self_in);
  if (dest[0] == MP_OBJ_NULL) {
    // Load attribute.
    switch (attr) {
    case MP_QSTR_screen_fade:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->screen_fade);
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
    case MP_QSTR_screen_fade:
      if ((val < 0) || (val > 0xFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Screen fade out of bounds"));
      } else {
        self->screen_fade = val;
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

static const mp_rom_map_elem_t sasppu_cmath_state_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_HALF_MAIN_SCREEN), MP_ROM_INT(CMATH_HALF_MAIN_SCREEN)},
    {MP_ROM_QSTR(MP_QSTR_DOUBLE_MAIN_SCREEN),
     MP_ROM_INT(CMATH_DOUBLE_MAIN_SCREEN)},
    {MP_ROM_QSTR(MP_QSTR_HALF_SUB_SCREEN), MP_ROM_INT(CMATH_HALF_SUB_SCREEN)},
    {MP_ROM_QSTR(MP_QSTR_DOUBLE_SUB_SCREEN),
     MP_ROM_INT(CMATH_DOUBLE_SUB_SCREEN)},
    {MP_ROM_QSTR(MP_QSTR_ADD_SUB_SCREEN), MP_ROM_INT(CMATH_ADD_SUB_SCREEN)},
    {MP_ROM_QSTR(MP_QSTR_SUB_SUB_SCREEN), MP_ROM_INT(CMATH_SUB_SUB_SCREEN)},
    {MP_ROM_QSTR(MP_QSTR_FADE_ENABLE), MP_ROM_INT(CMATH_FADE_ENABLE)},
    {MP_ROM_QSTR(MP_QSTR_CMATH_ENABLE), MP_ROM_INT(CMATH_CMATH_ENABLE)},
};
static MP_DEFINE_CONST_DICT(sasppu_cmath_state_locals_dict,
                            sasppu_cmath_state_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(sasppu_type_cmath_state, MP_QSTR_CMathState,
                         MP_TYPE_FLAG_NONE, make_new,
                         sasppu_cmath_state_make_new, locals_dict,
                         &sasppu_cmath_state_locals_dict, binary_op,
                         sasppu_cmath_state_binary_op, attr,
                         sasppu_cmath_state_attr);
