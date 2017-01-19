#ifndef _ENGINEER_TRANSFORM_H_
#define _ENGINEER_TRANSFORM_H_

// "NAME" *MUST* be the same as your Efl_Object Class name in the lowercase/underscore format.
#define NAME engineer_transform
#define DATA \
   VAR(Vec3, position) \
   VAR(Vec3, velocity) \
   VAR(Vec3, acceleration)

#include "../engineer_module.h"
#include "engineer_transform.eo.h"

typedef struct {}
Engineer_Transform_Data;

#endif
