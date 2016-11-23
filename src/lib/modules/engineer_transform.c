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
   *com->velocityx += *com->accelerationx * dt;
   *com->velocityy += *com->accelerationy * dt;
   *com->velocityz += *com->accelerationz * dt;

   *com->positionx += *com->velocityx * dt;
   *com->positiony += *com->velocityy * dt;
   *com->positionz += *com->velocityz * dt;
}

#include "engineer_transform.eo.c"
