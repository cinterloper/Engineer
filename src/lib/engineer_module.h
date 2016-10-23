#ifndef _ENGINEER_MODULE_H_
#define _ENGINEER_MODULE_H_

#include "../Engineer.h"

#ifndef NAME
   #define COMPONENT void
   #define DATACACHE void
   #define OVERRIDE  _engineer_module
#else
   #define COMPONENT NAME_Component
   #define DATACACHE COMPONENT_Cache
   #define OVERRIDE  _NAME_engineer_module
#endif

#if defined(NAME) && defined(DATA)

   typedef struct
   {
      Engineer_Scene_Component *component;

      #define VAR(TYPE, KEY) TYPE *KEY;
      DATA
      #undef VAR
   }
   COMPONENT;

   typedef struct
   {
      Eina_Inarray *component;

      #define VAR(TYPE, KEY) Eina_Inarray *KEY;
      DATA
      #undef VAR
   }
   DATACACHE;

#endif

#define add    EINA_UNUSED OVERRIDE_add
#define awake  EINA_UNUSED OVERRIDE_component_awake
#define start  EINA_UNUSED OVERRIDE_component_start
#define update EINA_UNUSED OVERRIDE_component_update

#include "engineer_module.eo.h"

#endif
