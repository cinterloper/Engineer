#include "Camera.h"

void awake(Engineer_Component *data)
{
   // Get the address of our Transform.
   EntityID    parent    = component_parent_get(this);
   ComponentID transform = entity_search(parent, "Transform");

   printf("Camera Awake Checkpoint. TransformID: %ld\n", transform);

   if(transform != (long)ULONG_NULL)
   {
      data->transformid = transform;
   }

   if(data->viewport != 0)
   {
      // Register this camera with the viewport.
      engineer_viewport_camera_set((Eo*)data->viewport, this);
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
      // We need to get our collider objects module Eo pointer.
      Eo *scene = efl_parent_get(module);
      engineer_viewport_object_flush((Eo*)data->viewport);
      printf("Camera Update Transform ID Check: %ld\n", data->transformid);
      engineer_scene_broadphase_frustum_sweep(scene, (Eo*)data->viewport, data->transformid);
      engineer_viewport_render((Eo*)data->viewport);
   }
}

bool event(viewport_attach, Engineer_Component *data, void *payload)
{
   if(payload != NULL)
   {
      data->viewport = *(uint64_t*)payload;
      //engineer_viewport_camera_set((Eo*)data->viewport, this);
   }
   return EINA_TRUE;
}
