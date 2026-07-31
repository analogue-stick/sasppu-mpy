// Include the header file to get access to the MicroPython API
#pragma once
#include "py/binary.h"
#include "py/obj.h"
#include "py/objarray.h"
#include "py/runtime.h"
#include "sasppu/help.h"
#include "sasppu/sasppu.h"

extern const mp_obj_type_t sasppu_type_sprite;

mp_obj_t sasppu_sprite_default(mp_obj_t self_in);
