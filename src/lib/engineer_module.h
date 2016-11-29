#ifndef _ENGINEER_MODULE_H_
#define _ENGINEER_MODULE_H_

#include "../headers/Engineer.h"

#ifndef NAME
   #define NAME
#endif

#ifndef DATA
   #define DATA
#endif

#define COMPONENT NAME_Component
#define DATACACHE COMPONENT_Cache
#define OVERRIDE  _NAME_engineer_module
/*
#ifndef NAME
   #define COMPONENT void
   #define DATACACHE void
   #define OVERRIDE  _engineer_module
#else
   #define COMPONENT NAME_Component
   #define DATACACHE COMPONENT_Cache
   #define OVERRIDE  _NAME_engineer_module
#endif
*/
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

      /* Experimental new command macros
      #define VAR(TYPE, KEY) pd->cache->KEY = engineer_type_TYPE_soa_new();
      DATA
      #undef VAR
      */
   }
   DATACACHE;
#endif

#define add    OVERRIDE_add
#define awake  OVERRIDE_component_awake
#define start  OVERRIDE_component_start
#define update OVERRIDE_component_update

#include "engineer_module.eo.h"

#endif
