#include "Transform.h"

void awake(Engineer_Component *data)
{
   data->position.x = 0;
   data->position.y = 0;
   data->position.z = 0;
}

void start(Engineer_Component *data EINA_UNUSED)
{
}

void update(Engineer_Component *data EINA_UNUSED)
{
}

bool event(move, Engineer_Component *data, void *payload)
{
  Vec3 position;

  if (data->poslock == EINA_FALSE)
  {
     position = *(Vec3*)payload;

     data->position.x += position.x;
     data->position.y += position.y;
     data->position.z += position.z;

     return EINA_TRUE;
  }
  else
  {
     return EINA_FALSE;
  }
}

bool event(teleport, Engineer_Component *data, void *payload)
{
   Vec3 position;

   if (data->poslock == EINA_FALSE)
   {
      position = *(Vec3*)payload;

      data->position.x = position.x;
      data->position.y = position.y;
      data->position.z = position.z;

      data->poslock = EINA_TRUE;

      return EINA_TRUE;
   }
   else
   {
      return EINA_FALSE;
   }
}

bool event(rotate, Engineer_Component *data EINA_UNUSED, void *payload EINA_UNUSED)
{
   return EINA_FALSE;
}

bool event(reorient, Engineer_Component *data EINA_UNUSED, void *payload EINA_UNUSED)
{
   return EINA_FALSE;
}
