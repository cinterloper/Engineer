#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../headers/Engineer.h"

#define STATE \
   FIELD(position, Vec3) \
   FIELD(velocity, Vec3) \
   FIELD(impulse,  Vec3) \
   FIELD(netforce, Vec3)

#define EVENTS \
   EVENT(accelerate)

#include "engineer_module.h"

#endif
