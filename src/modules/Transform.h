#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../headers/Engineer.h"

#define STATE \
   FIELD(position,    Vec3) \
   FIELD(orientation, Quat) \
   FIELD(telelock,    Sclr)

#define EVENTS \
   EVENT(move) \
   EVENT(teleport) \
   EVENT(rotate) \
   EVENT(reorient) \

#include "engineer_module.h"

#endif
