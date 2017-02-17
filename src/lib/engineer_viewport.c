#include "engineer_viewport.h"

// eolian_gen `pkg-config --variable=eolian_flags ecore eo evas efl` -I .
//    -I "/home/brokenshakles/.efler/efl/src/lib/" -g h engineer_viewport.eo

EOLIAN Eo *
engineer_viewport_add(Eo *obj)
{
   return efl_add(ENGINEER_VIEWPORT_CLASS, obj);
}

EOLIAN static Efl_Object *
_engineer_viewport_efl_object_constructor(Eo *obj, Engineer_Viewport_Data *pd EINA_UNUSED)
{
   return efl_constructor(efl_super(obj, ENGINEER_VIEWPORT_CLASS));
}

Efl_Object *
_engineer_viewport_efl_object_finalize(Eo *obj, Engineer_Viewport_Data *pd EINA_UNUSED)
{
   return obj;
}

EOLIAN static void
_engineer_viewport_efl_object_destructor(Eo *obj EINA_UNUSED, Engineer_Viewport_Data *pd EINA_UNUSED)
{
}

EOLIAN static void
_engineer_viewport_alpha_set(Eo *obj EINA_UNUSED, Engineer_Viewport_Data *pd,
        char alpha)
{
   pd->alpha = alpha;
}

EOLIAN static char
_engineer_viewport_alpha_get(Eo *obj EINA_UNUSED, Engineer_Viewport_Data *pd)
{
   return pd->alpha;
}

EOLIAN static void
_engineer_viewport_camera_set(Eo *obj EINA_UNUSED, Engineer_Viewport_Data *pd,
        unsigned int camera)
{
   pd->camera = camera;
}

EOLIAN static uint
_engineer_viewport_camera_get(Eo *obj EINA_UNUSED, Engineer_Viewport_Data *pd)
{
   return pd->camera;
}

