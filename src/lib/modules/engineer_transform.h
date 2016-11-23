#ifndef _ENGINEER_TRANSFORM_H_
#define _ENGINEER_TRANSFORM_H_

// "NAME" *MUST* be the same as your Efl_Object Class name in the lowercase/underscore format.
#define NAME engineer_transform
#define DATA \
   VAR(ulong, positionx) \
   VAR(ulong, positiony) \
   VAR(ulong, positionz) \
   VAR(ulong, velocityx) \
   VAR(ulong, velocityy) \
   VAR(ulong, velocityz) \
   VAR(ulong, accelerationx) \
   VAR(ulong, accelerationy) \
   VAR(ulong, accelerationz)

#include "../engineer_module.h"
#include "engineer_transform.eo.h"

#endif
