#ifndef _MASS_H_
#define _MASS_H_

#include "../headers/Engineer.h"

#define STATE \
   FIELD(bounding_box,     Sclr) \
   FIELD(mass,             Sclr) \
   FIELD(angular_mass,     Mtrx) \
   FIELD(momentum,         Vec3) \
   FIELD(angular_momentum, Vec3)

#define EVENTS \
   EVENT(force) \
   EVENT(twist)

#include "engineer_module.h"

#endif

