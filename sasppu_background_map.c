#include "sasppu_background_map.h"
#include "subscr_load_adapter.h"

static mp_obj_t sasppu_background_map_make_new(const mp_obj_type_t *type,
                                               size_t n_args, size_t n_kw,
                                               const mp_obj_t *args_in) {
  if (n_args != 2) {
    mp_raise_TypeError(MP_ERROR_TEXT("background map needs width and height"));
    return mp_const_none;
  }

  BackgroundMap *o = mp_obj_malloc(BackgroundMap, type);
  memset(&o->width, 0, sizeof(BackgroundMap) - sizeof(mp_obj_base_t));

  o->width = mp_obj_get_int(args_in[0]);
  o->height = mp_obj_get_int(args_in[1]);

  if (__builtin_popcount(o->width) != 1) {
    mp_raise_ValueError(
        MP_ERROR_TEXT("background map width must be power of 2"));
    return mp_const_none;
  }
  if (__builtin_popcount(o->height) != 1) {
    mp_raise_ValueError(
        MP_ERROR_TEXT("background map height must be power of 2"));
    return mp_const_none;
  }
  if (o->width < MAP_WIDTH_MIN) {
    mp_raise_ValueError(
        MP_ERROR_TEXT("background map width must at least MAP_WIDTH_MIN"));
    return mp_const_none;
  }
  if (o->width > MAP_WIDTH_MAX) {
    mp_raise_ValueError(
        MP_ERROR_TEXT("background map width must at most MAP_WIDTH_MAX"));
    return mp_const_none;
  }
  if (o->height < MAP_HEIGHT_MIN) {
    mp_raise_ValueError(
        MP_ERROR_TEXT("background map height must at least MAP_HEIGHT_MIN"));
    return mp_const_none;
  }
  if (o->height > MAP_HEIGHT_MAX) {
    mp_raise_ValueError(
        MP_ERROR_TEXT("background map height must at most MAP_HEIGHT_MAX"));
    return mp_const_none;
  }

  SASPPU_alloc_background_map(o);

  return MP_OBJ_FROM_PTR(o);
}

static mp_obj_t sasppu_background_map_deinit(mp_obj_t self_in) {
  BackgroundMap *self = MP_OBJ_TO_PTR(self_in);
  SASPPU_free_background_map(*self);
  return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(sasppu_background_map_deinit_obj,
                                 sasppu_background_map_deinit);

static mp_obj_t background_map_subscr(mp_obj_t self_in, mp_obj_t index_in,
                                      mp_obj_t value) {
  BackgroundMap *self = MP_OBJ_TO_PTR(self_in);
  mp_int_t index = mp_obj_get_int(index_in);
  if ((index < 0) || (index >= (self->height * self->width))) {
    mp_raise_msg(&mp_type_IndexError, MP_ERROR_TEXT("Index out of map bounds"));
    return mp_const_none;
  }

  if (value == MP_OBJ_NULL) {
    self->dat[index] = 0;
    return mp_const_none;
  } else if (value == MP_OBJ_SENTINEL) {
    return MP_OBJ_NEW_SMALL_INT(self->dat[index]);
  } else {
    mp_int_t tile = mp_obj_get_int(value);
    if ((tile < 0) || (tile > 0xFFFF)) {
      mp_raise_ValueError(MP_ERROR_TEXT("Invalid Background tile"));
      return mp_const_none;
    }
    self->dat[index] = tile;
    return mp_const_none;
  }

  return MP_OBJ_NULL;
}

static mp_obj_t background_map_unary_op(mp_unary_op_t op, mp_obj_t self_in) {
  BackgroundMap *self = MP_OBJ_TO_PTR(self_in);
  switch (op) {
  case MP_UNARY_OP_LEN: {
    return MP_OBJ_NEW_SMALL_INT(self->height * self->width);
  }
  default:
    return MP_OBJ_NULL; // op not supported
  }
}

static const mp_rom_map_elem_t sasppu_background_map_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR___del__),
     MP_ROM_PTR(&sasppu_background_map_deinit_obj)}};
static MP_DEFINE_CONST_DICT(sasppu_background_map_locals_dict,
                            sasppu_background_map_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(sasppu_type_background_map, MP_QSTR_BackgroundMap,
                         MP_TYPE_FLAG_ITER_IS_GETITER, make_new,
                         sasppu_background_map_make_new, locals_dict,
                         &sasppu_background_map_locals_dict, unary_op,
                         background_map_unary_op, subscr, background_map_subscr,
                         iter, subscr_getiter);
