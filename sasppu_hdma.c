#include "sasppu_hdma.h"
#include "sasppu_sprite.h"
#include "sasppu_main_state.h"
#include "sasppu_cmath_state.h"
#include "sasppu_background.h"
#include "subscr_load_adapter.h"

const size_t HDMA_LEN = 240;

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
        switch (entry->command) {
            default:
            case HDMA_NOOP: {
                return mp_const_none;
            }
            case HDMA_DISABLE: {
                return mp_const_false;
            }
            case HDMA_WRITE_MAIN_STATE: {
                sasppu_main_state_t *ms = mp_obj_malloc(sasppu_main_state_t, &sasppu_type_main_state);
                ms->dat = entry->data.main;
                return MP_OBJ_FROM_PTR(ms);
            }
            case HDMA_WRITE_CMATH_STATE: {
                sasppu_cmath_state_t *cs = mp_obj_malloc(sasppu_cmath_state_t, &sasppu_type_cmath_state);
                cs->dat = entry->data.cmath;
                return MP_OBJ_FROM_PTR(cs);
            }
            case HDMA_WRITE_OAM: {
                sasppu_sprite_t *spr = mp_obj_malloc(sasppu_sprite_t, &sasppu_type_sprite);
                spr->dat = entry->data.oam;
                mp_obj_t tuple_args[2] = {MP_OBJ_NEW_SMALL_INT(entry->oam_index), MP_OBJ_TO_PTR(spr)};
                return mp_obj_new_tuple(2, tuple_args);
            }
            case HDMA_WRITE_BG0_STATE: {
                sasppu_background_t *bg = mp_obj_malloc(sasppu_background_t, &sasppu_type_background);
                bg->dat = entry->data.background;
                mp_obj_t tuple_args[2] = {MP_OBJ_NEW_SMALL_INT(0), MP_OBJ_TO_PTR(bg)};
                return mp_obj_new_tuple(2, tuple_args);
            }
            case HDMA_WRITE_BG1_STATE: {
                sasppu_background_t *bg = mp_obj_malloc(sasppu_background_t, &sasppu_type_background);
                bg->dat = entry->data.background;
                mp_obj_t tuple_args[2] = {MP_OBJ_NEW_SMALL_INT(1), MP_OBJ_TO_PTR(bg)};
                return mp_obj_new_tuple(2, tuple_args);
            }
        }
    }
    else
    {
        if (value == mp_const_none)
        {
            entry->command = HDMA_NOOP;
        }
        else if (value == mp_const_false)
        {
            entry->command = HDMA_DISABLE;
        }
        else if (mp_obj_is_type(value, &sasppu_type_main_state))
        {
            entry->command = HDMA_WRITE_MAIN_STATE;
            sasppu_main_state_t *ms = MP_OBJ_FROM_PTR(value);
            entry->data.main = ms->dat;
        }
        else if (mp_obj_is_type(value, &sasppu_type_cmath_state))
        {
            entry->command = HDMA_WRITE_CMATH_STATE;
            sasppu_cmath_state_t *cs = MP_OBJ_FROM_PTR(value);
            entry->data.cmath = cs->dat;
        }
        else if (mp_obj_is_type(value, &mp_type_tuple))
        {
            size_t len;
            mp_obj_t *items;
            mp_obj_tuple_get(value, &len, &items);
            if ((len == 2) && mp_obj_is_int(items[0]))
            {
                ssize_t bind_index = mp_obj_get_int(items[0]);
                if (mp_obj_is_type(items[1], &sasppu_type_background))
                {
                    if (bind_index == 0)
                    {
                        entry->command = HDMA_WRITE_BG0_STATE;
                    }
                    else if (bind_index == 1)
                    {
                        entry->command = HDMA_WRITE_BG1_STATE;
                    }
                    else
                    {
                        mp_raise_msg(&mp_type_IndexError, MP_ERROR_TEXT("Background index out of bounds"));
                        return mp_const_none;
                    }

                    sasppu_background_t *bg = MP_OBJ_FROM_PTR(items[1]);
                    entry->data.background = bg->dat;
                }
                else if (mp_obj_is_type(items[1], &sasppu_type_sprite))
                {
                    if ((bind_index < 0) || (bind_index > SPRITE_COUNT))
                    {
                        mp_raise_msg(&mp_type_IndexError, MP_ERROR_TEXT("Sprite index out of bounds"));
                        return mp_const_none;
                    }

                    entry->command = HDMA_WRITE_OAM;
                    sasppu_sprite_t *spr = MP_OBJ_FROM_PTR(items[1]);
                    entry->data.oam = spr->dat;
                    entry->oam_index = bind_index;
                }
            }
        }
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