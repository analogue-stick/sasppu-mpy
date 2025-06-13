#include "sasppu_hdma.h"
#include "sasppu_sprite.h"
#include "sasppu_main_state.h"
#include "sasppu_cmath_state.h"
#include "sasppu_background.h"
#include "subscr_load_adapter.h"

static mp_obj_t hdma_subscr(mp_obj_t self_in, mp_obj_t index_in, mp_obj_t value)
{
    sasppu_hdma_t *self = MP_OBJ_TO_PTR(self_in);
    mp_int_t index = mp_obj_get_int(index_in);
    if ((index < 0) || (index >= HDMA_LEN))
    {
        mp_raise_msg(&mp_type_IndexError, MP_ERROR_TEXT("Index out of HDMA bounds"));
        return mp_const_none;
    }

    HDMAEntry *entry = &SASPPU_hdma_tables[self->table][index];

    if (value == MP_OBJ_NULL)
    {
        entry->command = HDMA_NOOP;
        return mp_const_none;
    }
    else if (value == MP_OBJ_SENTINEL)
    {
        mp_obj_t tuple_args[2] = {MP_OBJ_NEW_SMALL_INT(entry->command), MP_OBJ_NEW_SMALL_INT(entry->value)};
        return mp_obj_new_tuple(2, tuple_args);
    }
    else
    {
        if (!mp_obj_is_type(value, &mp_type_tuple)) {
            mp_raise_msg(&mp_type_TypeError, MP_ERROR_TEXT("HDMA value must be tuple of two integers"));
            return mp_const_none;
        }
        mp_obj_tuple_t *pair = MP_OBJ_TO_PTR(value);
        if (pair->len != 2) {
            mp_raise_msg(&mp_type_TypeError, MP_ERROR_TEXT("HDMA value must be tuple of two integers"));
            return mp_const_none;
        }
        mp_int_t command = mp_obj_get_int(pair->items[0]);
        if ((command < 0) || (command >= HDMA_LAST))
        {
            mp_raise_msg(&mp_type_IndexError, MP_ERROR_TEXT("HDMA command out of bounds"));
            return mp_const_none;
        }
        uint16_t value = (uint16_t)(mp_obj_get_int(pair->items[1]));
        entry->command = (uint16_t)(command);
        entry->value = value;
        return mp_const_none;
    }

    return MP_OBJ_NULL;
}

static mp_obj_t hdma_unary_op(mp_unary_op_t op, mp_obj_t self_in)
{
    switch (op)
    {
    case MP_UNARY_OP_LEN:
    {
        return MP_OBJ_NEW_SMALL_INT(HDMA_LEN);
    }
    default:
        return MP_OBJ_NULL; // op not supported
    }
}

MP_DEFINE_CONST_OBJ_TYPE(
    sasppu_type_hdma,
    MP_QSTR_HDMA,
    MP_TYPE_FLAG_ITER_IS_GETITER,
    unary_op, hdma_unary_op,
    subscr, hdma_subscr,
    iter, subscr_getiter);