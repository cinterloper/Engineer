#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../headers/Engineer.h"

#define STATE \
   FIELD(position,    Vec3) \
   FIELD(poslock,     Sclr) \
   FIELD(orientation, Quat) \
   FIELD(orilock,     Sclr) \
   FIELD(bounds,      Vec3)

#define EVENTS \
   EVENT(move) \
   EVENT(teleport) \
   EVENT(rotate) \
   EVENT(reorient) \

#include "engineer_module.h"

#endif
