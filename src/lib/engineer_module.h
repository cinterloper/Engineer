#ifndef _ENGINEER_MODULE_H_
#define _ENGINEER_MODULE_H_

#include "../headers/Engineer.h"

#ifndef NAME
   #define NAME default
#endif

#ifndef DATA
   #define DATA
#endif

#define COMPONENT NAME_Component
#define COMPODATA COMPONENT_Cache
#define OVERRIDE  NAME_engineer_module

typedef struct
{
   Engineer_Scene_Component *component;

   #define VAR(TYPE, KEY) \
      TYPE *KEY;
   DATA
   #undef VAR
}
COMPONENT;

typedef struct
{
   Engineer_Scene_Component *component;

   #define VAR(TYPE, KEY) \
      TYPEData KEY;
   DATA
   #undef VAR
}
COMPODATA;

#define add          _OVERRIDE_add
#define awake(a, b)  _OVERRIDE_component_awake(Eo *obj EINA_UNUSED, a, b)
#define start(a, b)  _OVERRIDE_component_start(Eo *obj EINA_UNUSED, a, b)
#define update(a, b) _OVERRIDE_component_update(Eo *obj EINA_UNUSED, a, b)

#include "engineer_module.eo.h"

#endif
