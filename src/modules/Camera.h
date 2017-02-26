#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../headers/Engineer.h"

#define STATE \
   FIELD(transformid, Sclr) \
   FIELD(target1,     Sclr) \
   FIELD(target2,     Sclr) \
   FIELD(uv,          Vec2)

//#define EVENTS

#include "engineer_module.h"

#endif

