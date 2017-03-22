#ifndef _MASS_H_
#define _MASS_H_

#include "Engineer.h"

#define STATE \
   FIELD(bounding_box,     Sclr) \
   FIELD(mass,             Sclr) \
   FIELD(angular_mass,     Mtrx) \
   FIELD(momentum,         Vec3) \
   FIELD(angular_momentum, Vec3)

#define EVENTS \
   EVENT(force, 1) \
   EVENT(twist, 1)

#include "Engineer_Module.h"

#endif

