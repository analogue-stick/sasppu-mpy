#pragma once
#include "py/binary.h"
#include "py/obj.h"
#include "py/objarray.h"
#include "py/runtime.h"
#include "sasppu/help.h"
#include "sasppu/sasppu.h"

extern const mp_obj_type_t sasppu_type_cmath_state;

mp_obj_t sasppu_cmath_state_default(mp_obj_t self_in);
