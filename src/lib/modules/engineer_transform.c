#include "engineer_transform.h"

typedef struct {}
Engineer_Transform_Data;

// This method is needed for module Eo adding, make sure efl_add() points to the right CLASS macro.
EOLIAN static Efl_Object *
add(Eo *obj)
{ return efl_add(ENGINEER_TRANSFORM_CLASS, obj); }

EOLIAN static void
awake(const COMPONENT *com, const ulong dt)
{
}

EOLIAN static void
start(const COMPONENT *com, const ulong dt)
{
}

EOLIAN static void
update(const COMPONENT *com, const ulong dt)
{
   *com->velocity->x += MULT(com->acceleration->x, &dt);
   *com->velocity->y += MULT(com->acceleration->y, &dt);
   *com->velocity->z += MULT(com->acceleration->z, &dt);

   *com->position->x += MULT(com->velocity->x, &dt);
   *com->position->y += MULT(com->velocity->y, &dt);
   *com->position->z += MULT(com->velocity->z, &dt);
}

#include "engineer_transform.eo.c"
