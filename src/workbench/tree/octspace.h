#ifndef _ENGINEER_OCTSPACE_H_
#define _ENGINEER_OCTSPACE_H_

#include "../../headers/Engineer.h"

typedef struct
{
   uint32_t      version;

   Eo           *scene;
   Eina_Inarray *level[64];

   uint32_t lock:24
   uint32_t childmask:8;

   uint64_t population;
}
Engineer_Octspace;

typedef struct
{
   uint64_t index;

   //uint32_t parent;

   uint64_t empty:20;
   uint64_t childmask:8;

   uint64_t topdepth:6,  bottomdepth:6;
   uint64_t updepth:6,   downdepth:6;
   uint64_t leftdepth:6, rightdepth:6;

   uint32_t top,  bottom;
   uint32_t up,   down;
   uint32_t left, right;

   uint64_t transformid;
}
Engineer_Octspace_Node_01to21;

typedef struct
{
   Vec2 index;

   //uint32_t parent;

   uint64_t empty:20;
   uint64_t childmask:8;

   uint64_t topdepth:6,  bottomdepth:6;
   uint64_t updepth:6,   downdepth:6;
   uint64_t leftdepth:6, rightdepth:6;

   uint32_t top,  bottom;
   uint32_t up,   down;
   uint32_t left, right;

   uint64_t transformid;
}
Engineer_Octspace_Node_22to42;

typedef struct
{
   Vec3 index;

   //uint32_t parent;

   uint64_t empty:20;
   uint64_t childmask:8;

   uint64_t topdepth:6,  bottomdepth:6;
   uint64_t updepth:6,   downdepth:6;
   uint64_t leftdepth:6, rightdepth:6;

   uint32_t top,  bottom;
   uint32_t up,   down;
   uint32_t left, right;

   uint64_t transformid;
}
Engineer_Octspace_Node_43to63;

Engineer_Octspace *
engineer_octspace_factory();

void
engineer_octspace_disposal(Engineer_Octspace *octspace);

void
engineer_octspace_insert(Engineer_Octspace *octspace, uint64_t transformid);

void
engineer_octspace_remove(Engineer_Octspace *octspace);

void
engineer_octspace_sprout(Engineer_Octspace *octspace);

void
engineer_octspace_prune(Engineer_Octspace *octspace);

uint32_t
engineer_octspace_search(Engineer_Octspace *octspace, uint32_t depth, Vec3 index);

#endif
