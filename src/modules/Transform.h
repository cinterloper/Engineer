#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Engineer.h"

#define STATE \
   FIELD(position,    Vec3) \
   FIELD(poslock,     Sclr) \
   FIELD(orientation, Quat) \
   FIELD(orilock,     Sclr) \
   FIELD(bounds,      Vec3)

#define EVENTS \
   EVENT(move,     1) \
   EVENT(teleport, 1) \
   EVENT(rotate,   1) \
   EVENT(reorient, 1) \

#include "Engineer_Module.h"

#endif
