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
   EVENT(move) \
   EVENT(teleport) \
   EVENT(rotate) \
   EVENT(reorient) \

#include "Engineer_Module.h"

#endif
