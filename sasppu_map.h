#pragma once
#include "py/runtime.h"
#include <stdlib.h>
#include "py/binary.h"
#include "py/obj.h"
#include "py/objarray.h"
#include "sasppu/sasppu.h"
#include "sasppu/help.h"

typedef struct
{
    mp_obj_base_t base;
    int bg;
} sasppu_map_t;

extern const mp_obj_type_t sasppu_type_map;