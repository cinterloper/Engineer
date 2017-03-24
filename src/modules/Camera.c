#include "Camera.h"

void awake(Engineer_Component *data)
{
   // Get the address of our Transform.
   EntityID    parent    = component_parent_get(this);
   ComponentID transform = entity_search(parent, "Transform");

   if(transform != (long)ULONG_NULL)
   {
      data->transformid = transform;
   }
}

void start(Engineer_Component *data EINA_UNUSED)
{

}

void update(Engineer_Component *data)
{
   // First check to see if we have an attached viewport to export to, if not, skip this update.
   if(data->viewport != 0)
   {
      // Get our camera scenespace position from our Entity Transform Position.
      Vec3 *position EINA_UNUSED = (Vec3*)component_query(data->transformid, "Position");

      // For each collider object in the scene, make a list containing them all.
      // be sure to convert from worldspace co-ords to cameraspace co-ords
   }
}

bool event(viewport_attach, Engineer_Component *data, void *payload)
{
   if(payload != NULL)
   {
      data->viewport = *(uint64_t*)payload;
   }
   return EINA_TRUE;
}
