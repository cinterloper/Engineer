#ifndef _ENGINEER_VIEWPORT_H_
#define _ENGINEER_VIEWPORT_H_

#include "../headers/Engineer.h"

#include "engineer_viewport.eo.h"

typedef struct
{
   uint alpha;
   uint camera;
}
Engineer_Viewport_Data;

EOLIAN Eo *
engineer_viewport_add(Eo *obj);

#endif

