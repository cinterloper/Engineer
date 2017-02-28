#include "Camera.h"

void awake(Engineer_Component *data EINA_UNUSED)
{
   // Get the address of our Transform.
}

void start(Engineer_Component *data EINA_UNUSED)
{

}

void update(Engineer_Component *data EINA_UNUSED)
{
   //Vec3 position; // need to get position and orientation from our entity transform.
   //Vec3 orientation;
   //Vec2 resolution;
   // We also need to get the target resolution from our viewport object.
}

bool event(accelerate, Engineer_Component *data EINA_UNUSED, void *payload EINA_UNUSED, uint64_t size EINA_UNUSED)
{
  return EINA_TRUE;
}
