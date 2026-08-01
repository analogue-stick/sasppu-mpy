#include "sasppu_hdma.h"
#include <string.h>

mp_obj_t sasppu_hdma_entry_default(mp_obj_t self_in) {
  HDMAEntry *self = MP_OBJ_TO_PTR(self_in);
  memset(&self->command, 0, sizeof(HDMAEntry) - sizeof(mp_obj_base_t));
  self->command = 0;
  self->value = 0;
  return mp_const_none;
}

static mp_obj_t sasppu_hdma_entry_make_new(const mp_obj_type_t *type,
                                           size_t n_args, size_t n_kw,
                                           const mp_obj_t *args_in) {
  HDMAEntry *o = mp_obj_malloc(HDMAEntry, type);

  sasppu_hdma_entry_default(MP_OBJ_FROM_PTR(o));

  if (n_args == 1 || n_args > 2) {
    mp_raise_TypeError(MP_ERROR_TEXT("hdma entry needs command and value"));
    return mp_const_none;
  }

  mp_int_t command = mp_obj_get_int(args_in[0]);
  if ((command < 0) || (command >= HDMA_LAST)) {
    mp_raise_ValueError(MP_ERROR_TEXT("Invalid HDMA command"));
  } else {
    o->command = command;
  }
  mp_int_t val = mp_obj_get_int(args_in[1]);
  if ((val < -0x8000) || (val > 0x7FFF)) {
    mp_raise_ValueError(MP_ERROR_TEXT("Command value out of bounds"));
  } else {
    if (val < 0) {
      val += 0x10000;
    }
    o->value = val;
  }

  return MP_OBJ_FROM_PTR(o);
}

static mp_obj_t sasppu_hdma_entry_binary_op(mp_binary_op_t op, mp_obj_t lhs_in,
                                            mp_obj_t rhs_in) {
  HDMAEntry *self = MP_OBJ_TO_PTR(lhs_in);
  HDMAEntry *other = MP_OBJ_TO_PTR(rhs_in);
  switch (op) {
  case MP_BINARY_OP_EQUAL: {
    return memcmp(&self->command, &other->command,
                  sizeof(HDMAEntry) - sizeof(mp_obj_base_t))
               ? mp_const_true
               : mp_const_false;
  }
  default:
    // op not supported
    return MP_OBJ_NULL;
  }
}

static void sasppu_hdma_entry_attr(mp_obj_t self_in, qstr attr,
                                   mp_obj_t *dest) {
  HDMAEntry *self = MP_OBJ_TO_PTR(self_in);
  if (dest[0] == MP_OBJ_NULL) {
    // Load attribute.
    switch (attr) {
    case MP_QSTR_command:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->command);
      break;
    case MP_QSTR_value:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->value);
      break;
    default:
      dest[1] = MP_OBJ_SENTINEL;
      break;
    }
  } else if (dest[1] != MP_OBJ_NULL) {
    // Store attribute.
    mp_int_t val = mp_obj_get_int(dest[1]);
    switch (attr) {
    case MP_QSTR_command:
      if ((val < 0) || (val >= HDMA_LAST)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid HDMA command"));
      } else {
        self->command = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_value:
      if ((val < -0x8000) || (val > 0x7FFF)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Command value out of bounds"));
      } else {
        if (val < 0) {
          val += 0x10000;
        }
        self->value = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    default:
      break;
    }
  }
}

static const mp_rom_map_elem_t sasppu_hdma_entry_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_HDMA_NOOP), MP_ROM_INT(HDMA_NOOP)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_MAIN_STATE_MAINSCREEN_COLOUR),
     MP_ROM_INT(HDMA_MAIN_STATE_MAINSCREEN_COLOUR)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_MAIN_STATE_SUBSCREEN_COLOUR),
     MP_ROM_INT(HDMA_MAIN_STATE_SUBSCREEN_COLOUR)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_MAIN_STATE_WINDOW1_LEFT),
     MP_ROM_INT(HDMA_MAIN_STATE_WINDOW1_LEFT)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_MAIN_STATE_WINDOW1_RIGHT),
     MP_ROM_INT(HDMA_MAIN_STATE_WINDOW1_RIGHT)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_MAIN_STATE_WINDOW2_LEFT),
     MP_ROM_INT(HDMA_MAIN_STATE_WINDOW2_LEFT)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_MAIN_STATE_WINDOW2_RIGHT),
     MP_ROM_INT(HDMA_MAIN_STATE_WINDOW2_RIGHT)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_MAIN_STATE_BGCOL_WINDOWS),
     MP_ROM_INT(HDMA_MAIN_STATE_BGCOL_WINDOWS)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_MAIN_STATE_FLAGS),
     MP_ROM_INT(HDMA_MAIN_STATE_FLAGS)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_CMATH_STATE_SCREEN_FADE),
     MP_ROM_INT(HDMA_CMATH_STATE_SCREEN_FADE)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_CMATH_STATE_FLAGS),
     MP_ROM_INT(HDMA_CMATH_STATE_FLAGS)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_BACKGROUND_X), MP_ROM_INT(HDMA_BACKGROUND_X)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_BACKGROUND_Y), MP_ROM_INT(HDMA_BACKGROUND_Y)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_BACKGROUND_WINDOWS),
     MP_ROM_INT(HDMA_BACKGROUND_WINDOWS)},
    {MP_ROM_QSTR(MP_QSTR_HDMA_BACKGROUND_FLAGS),
     MP_ROM_INT(HDMA_BACKGROUND_FLAGS)},
};
static MP_DEFINE_CONST_DICT(sasppu_hdma_entry_locals_dict,
                            sasppu_hdma_entry_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(sasppu_type_hdma_entry, MP_QSTR_HdmaEntry,
                         MP_TYPE_FLAG_NONE, make_new,
                         sasppu_hdma_entry_make_new, locals_dict,
                         &sasppu_hdma_entry_locals_dict, binary_op,
                         sasppu_hdma_entry_binary_op, attr,
                         sasppu_hdma_entry_attr);
