#include "sasppu_map.h"
#include "subscr_load_adapter.h"

static mp_obj_t sasppu_graphics_plane_subscr(mp_obj_t self_in,
                                             mp_obj_t index_in,
                                             mp_obj_t value) {
  GraphicsPlane *self = MP_OBJ_TO_PTR(self_in);
  mp_int_t index = mp_obj_get_int(index_in);
  if ((index < 0) || (index >= (self->height * self->width))) {
    mp_raise_msg(&mp_type_IndexError,
                 MP_ERROR_TEXT("Index out of plane bounds"));
    return mp_const_none;
  }

  uint16_t *dat_cast = (uint16_t *)(self->dat);

  if (value == MP_OBJ_NULL) {
    dat_cast[index] = 0;
    return mp_const_none;
  } else if (value == MP_OBJ_SENTINEL) {
    return MP_OBJ_NEW_SMALL_INT(dat_cast[index]);
  } else {
    mp_int_t tile = mp_obj_get_int(value);
    if ((tile < 0) || (tile > 0xFFFF)) {
      mp_raise_ValueError(MP_ERROR_TEXT("Invalid plane tile"));
      return mp_const_none;
    }
    dat_cast[index] = tile;
    return mp_const_none;
  }

  return MP_OBJ_NULL;
}

static mp_obj_t graphics_plane_unary_op(mp_unary_op_t op, mp_obj_t self_in) {
  GraphicsPlane *self = MP_OBJ_TO_PTR(self_in);
  switch (op) {
  case MP_UNARY_OP_LEN: {
    return MP_OBJ_NEW_SMALL_INT(self->height * self->width);
  }
  default:
    return MP_OBJ_NULL; // op not supported
  }
}

MP_DEFINE_CONST_OBJ_TYPE(sasppu_type_graphics_plane, MP_QSTR_GraphicsPlane,
                         MP_TYPE_FLAG_ITER_IS_GETITER, unary_op,
                         graphics_plane_unary_op, subscr, graphics_plane_subscr,
                         iter, subscr_getiter);
