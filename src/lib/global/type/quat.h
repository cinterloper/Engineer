#ifndef _ENGINEER_TYPE_QUAT_H_
#define _ENGINEER_TYPE_QUAT_H_

#include "angl.h"
#include "sclr.h"

#define TYPE Quat

#define FIELDS    \
   FIELD(w, Angl) \
   FIELD(x, Sclr) \
   FIELD(y, Sclr) \
   FIELD(z, Sclr)

#include "type.h"

#endif

