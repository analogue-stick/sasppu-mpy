#include "sasppu_buffer.h"
#include <string.h>

mp_obj_t sasppu_buffer_entry_default(mp_obj_t self_in) {
  BufferEntry *self = MP_OBJ_TO_PTR(self_in);
  memset(&self->command, 0, sizeof(BufferEntry) - sizeof(mp_obj_base_t));
  self->command = 0;
  self->data = (void *)(0);
  return mp_const_none;
}

static mp_obj_t sasppu_buffer_entry_make_new(const mp_obj_type_t *type,
                                             size_t n_args, size_t n_kw,
                                             const mp_obj_t *args_in) {
  BufferEntry *o = mp_obj_malloc(BufferEntry, type);

  sasppu_buffer_entry_default(MP_OBJ_FROM_PTR(o));

  if (n_args == 1 || n_args > 2) {
    mp_raise_TypeError(MP_ERROR_TEXT("buffer entry needs command and object"));
    return mp_const_none;
  }

  mp_int_t command = mp_obj_get_int(args_in[0]);
  if ((command < 0) || (command >= CMD_LAST)) {
    mp_raise_ValueError(MP_ERROR_TEXT("Invalid buffer command"));
  } else {
    o->command = command;
  }
  o->data = MP_OBJ_TO_PTR(args_in[1]);

  return MP_OBJ_FROM_PTR(o);
}

static mp_obj_t sasppu_buffer_entry_binary_op(mp_binary_op_t op,
                                              mp_obj_t lhs_in,
                                              mp_obj_t rhs_in) {
  BufferEntry *self = MP_OBJ_TO_PTR(lhs_in);
  BufferEntry *other = MP_OBJ_TO_PTR(rhs_in);
  switch (op) {
  case MP_BINARY_OP_EQUAL: {
    return memcmp(&self->command, &other->command,
                  sizeof(BufferEntry) - sizeof(mp_obj_base_t))
               ? mp_const_true
               : mp_const_false;
  }
  default:
    // op not supported
    return MP_OBJ_NULL;
  }
}

static void sasppu_buffer_entry_attr(mp_obj_t self_in, qstr attr,
                                     mp_obj_t *dest) {
  BufferEntry *self = MP_OBJ_TO_PTR(self_in);
  if (dest[0] == MP_OBJ_NULL) {
    // Load attribute.
    switch (attr) {
    case MP_QSTR_command:
      dest[0] = MP_OBJ_NEW_SMALL_INT(self->command);
      break;
    case MP_QSTR_data:
      dest[0] = MP_OBJ_FROM_PTR(self->data);
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
      if ((val < 0) || (val >= CMD_LAST)) {
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid buffer command"));
      } else {
        self->command = val;
        dest[0] = MP_OBJ_NULL;
      }
      break;
    case MP_QSTR_data:
      self->data = MP_OBJ_TO_PTR(val);
      dest[0] = MP_OBJ_NULL;
      break;
    default:
      break;
    }
  }
}

static const mp_rom_map_elem_t sasppu_buffer_entry_locals_dict_table[] = {
    {MP_ROM_QSTR(MP_QSTR_CMD_NOOP), MP_ROM_INT(CMD_NOOP)},
    {MP_ROM_QSTR(MP_QSTR_CMD_BIND_MAIN_STATE), MP_ROM_INT(CMD_BIND_MAIN_STATE)},
    {MP_ROM_QSTR(MP_QSTR_CMD_BIND_C_MATH_STATE),
     MP_ROM_INT(CMD_BIND_C_MATH_STATE)},
    {MP_ROM_QSTR(MP_QSTR_CMD_BIND_BACKGROUND_PLANE),
     MP_ROM_INT(CMD_BIND_BACKGROUND_PLANE)},
    {MP_ROM_QSTR(MP_QSTR_CMD_BIND_SPRITE_PLANE),
     MP_ROM_INT(CMD_BIND_SPRITE_PLANE)},
    {MP_ROM_QSTR(MP_QSTR_CMD_BIND_BACKGROUND_MAP),
     MP_ROM_INT(CMD_BIND_BACKGROUND_MAP)},
    {MP_ROM_QSTR(MP_QSTR_CMD_BIND_BACKGROUND_STATE),
     MP_ROM_INT(CMD_BIND_BACKGROUND_STATE)},
    {MP_ROM_QSTR(MP_QSTR_CMD_BIND_SPRITE_STATE),
     MP_ROM_INT(CMD_BIND_SPRITE_STATE)},
    {MP_ROM_QSTR(MP_QSTR_CMD_APPLY_HDMA), MP_ROM_INT(CMD_APPLY_HDMA)},
    {MP_ROM_QSTR(MP_QSTR_CMD_BEGIN_FRAME), MP_ROM_INT(CMD_BEGIN_FRAME)},
    {MP_ROM_QSTR(MP_QSTR_CMD_UPDATE_WINDOWS), MP_ROM_INT(CMD_UPDATE_WINDOWS)},
    {MP_ROM_QSTR(MP_QSTR_CMD_DRAW_BACKGROUND), MP_ROM_INT(CMD_DRAW_BACKGROUND)},
    {MP_ROM_QSTR(MP_QSTR_CMD_DRAW_SPRITES), MP_ROM_INT(CMD_DRAW_SPRITES)},
    {MP_ROM_QSTR(MP_QSTR_CMD_END_FRAME), MP_ROM_INT(CMD_END_FRAME)}};
static MP_DEFINE_CONST_DICT(sasppu_buffer_entry_locals_dict,
                            sasppu_buffer_entry_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(sasppu_type_buffer_entry, MP_QSTR_BufferEntry,
                         MP_TYPE_FLAG_NONE, make_new,
                         sasppu_buffer_entry_make_new, locals_dict,
                         &sasppu_buffer_entry_locals_dict, binary_op,
                         sasppu_buffer_entry_binary_op, attr,
                         sasppu_buffer_entry_attr);
