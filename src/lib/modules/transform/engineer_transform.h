#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#define SYMBOL transform

#define FIELDS \
   FIELD(position, Vec3) \
   FIELD(velocity, Vec3) \
   FIELD(impulse,  Vec3) \
   FIELD(netforce, Vec3) 

#define RESPONSES \
   REPSONSE(accelerate, sizeof(Vec3))

#include "../engineer_module_subclass_autogen.h"

#endif
