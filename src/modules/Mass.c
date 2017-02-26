#include "Mass.h"

void awake(Engineer_Component *data EINA_UNUSED)
{
   /*
   data->position.x = 0;
   data->position.y = 0;
   data->position.z = 0;

   data->velocity.x = 0;
   data->velocity.y = 0;
   data->velocity.z = 0;

   data->impulse.x = 0;
   data->impulse.y = 0;
   data->impulse.z = 0;
   */
}

void start(Engineer_Component *data EINA_UNUSED)
{
}

void update(Engineer_Component *data EINA_UNUSED)
{
   // We use Velocity Verlet Integration to calculate the next position and velocity.
   //    Then we record our acceleration/impulse input to our timeline.
   Sclr offset EINA_UNUSED;
   double dt = 1/32;
   double dtsqr EINA_UNUSED = dt * dt;
   /*
   offset            = MULT(data->impulse.x,  dtsqr);
   data->position.x += MULT(data->velocity.x, dt) + (offset / 2);
   offset            = MULT(data->impulse.y,  dtsqr);
   data->position.y += MULT(data->velocity.y, dt) + (offset / 2);
   offset            = MULT(data->impulse.z,  dtsqr);
   data->position.z += MULT(data->velocity.z, dt) + (offset / 2);

   offset            = (data->impulse.x + data->netforce.x) / 2;
   data->velocity.x += MULT(offset, dt);
   offset            = (data->impulse.y + data->netforce.y) / 2;
   data->velocity.y += MULT(offset, dt);
   offset            = (data->impulse.z + data->netforce.z) / 2;
   data->velocity.z += MULT(offset, dt);

   data->impulse.x = data->netforce.x;
   data->impulse.y = data->netforce.y;
   data->impulse.z = data->netforce.z;
   */
}

bool event(accelerate, Engineer_Component *data EINA_UNUSED, void *payload, uint64_t size EINA_UNUSED)
{
   Vec3 force EINA_UNUSED = *(Vec3*)payload;
   /*
   data->netforce.x += force->x;
   data->netforce.y += force->y;
   data->netforce.z += force->z;
   */
  return EINA_TRUE;
}
