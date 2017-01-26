#include "engineer_transform.h"

// This method is needed for Eina_Module, make sure efl_add() points to the right CLASS macro.
EOLIAN static Efl_Object *
factory(Eo *obj)
{ return efl_add(ENGINEER_TRANSFORM_CLASS, obj); }

EOLIAN static void
awake(const HANDLE *next, Sclr *dt EINA_UNUSED)
{
   *next->acceleration->x = 0;
   *next->acceleration->y = 0;
   *next->acceleration->z = 0;

   *next->velocity->x = 0;
   *next->velocity->y = 0;
   *next->velocity->z = 0;

   *next->position->x = 0;
   *next->position->y = 0;
   *next->position->z = 0;
}

EOLIAN static void
start(const HANDLE *next EINA_UNUSED, Sclr *dt EINA_UNUSED)
{
}

EOLIAN static void
update(const HANDLE *last, const HANDLE *next, Sclr *dt)
{
   // We use Velocity Verlet Integration to calculate the next position and velocity.
   // Note that by the time update begins, the value of next->acceleration should be properly set,
   //    either to zero, by the scene iterator, or by the accelerate callback.
   Sclr dtsqr = MULT(dt, dt);
   Sclr offset;

   offset = (*last->acceleration->x + *next->acceleration->x) >> 1;
   *next->velocity->x += MULT(&offset, dt);
   offset = (*last->acceleration->y + *next->acceleration->y) >> 1;
   *next->velocity->y += MULT(&offset, dt);
   offset = (*last->acceleration->z + *next->acceleration->z) >> 1;
   *next->velocity->z += MULT(&offset, dt);

   offset = MULT(last->acceleration->x, &dtsqr);
   *next->position->x = *last->position->x + MULT(last->velocity->x, dt) + (offset >> 1);
   offset = MULT(last->acceleration->y, &dtsqr);
   *next->position->y = *last->position->y + MULT(last->velocity->y, dt) + (offset >> 1);
   offset = MULT(last->acceleration->z, &dtsqr);
   *next->position->z = *last->position->z + MULT(last->velocity->z, dt) + (offset >> 1);
}

// When invoking this, pass the object pointer of the invoking module object instance.
EOLIAN static void
_engineer_transform_accelerate(Eo *obj, uint componentid, const Vec3 *input)
{
   HANDLE *next = engineer_module_handle_alloc(obj);
   engineer_module_component_lookup(obj, 0, componentid, next);

   *next->acceleration->x += *input->x;
   *next->acceleration->y += *input->y;
   *next->acceleration->z += *input->z;

   engineer_module_handle_free(obj, next);
}

#include "engineer_transform.eo.c"
