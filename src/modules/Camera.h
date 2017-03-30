#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Engineer.h"
#include "engineer_viewport.h"

#define STATE \
   FIELD(viewport,    Sclr) \
   FIELD(transformid, Sclr) \
   FIELD(target1,     Sclr) \
   FIELD(target2,     Sclr) \
   FIELD(uv,          Vec2)

#define EVENTS \
   EVENT(viewport_attach, 1)

#include "Engineer_Module.h"

#endif
