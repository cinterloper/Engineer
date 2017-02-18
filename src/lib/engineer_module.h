#ifndef _ENGINEER_MODULE_H_
#define _ENGINEER_MODULE_H_

#include "../headers/Engineer.h"

#ifndef PROJECT
   #define PROJECT
#endif

#ifndef MODULE
   #define MODULE
#endif

#ifndef STATE
   #define STATE
#endif

#ifndef EVENTS
   #define EVENTS
#endif

typedef struct
{
   const char *name;

   uint64_t parent;
   uint64_t nextsibling;
   uint64_t prevsibling;

   #define FIELD(key, type) \
      type key;
   STATE
   #undef FIELD
}
Engineer_Component;

typedef struct
{
   Eina_Inarray *name;

   Eina_Inarray *parent;
   Eina_Inarray *siblingnext;
   Eina_Inarray *siblingprev;

   #define FIELD(key, type) \
      type##SOA key;
   STATE
   #undef FIELD
}
Engineer_Component_History;

typedef struct
{
   Eina_Inarray *name;

   Eina_Inarray *parent;
   Eina_Inarray *siblingnext;
   Eina_Inarray *siblingprev;

   #define FIELD(key, type) \
      type##SOA key;
   STATE
   #undef FIELD
}
Engineer_Module_Frame;

typedef struct
{
   Eina_Inarray *buffer;

   Engineer_Module_Frame *past;
   Engineer_Module_Frame *present;
   Engineer_Module_Frame *future;

   Eina_Inarray *history;
   Eina_Inarray *id;
   Eina_Hash    *lookup;
}
Engineer_Module_Data;

void engineer_module_component_awake(Engineer_Component *data);
void engineer_module_component_start(Engineer_Component *data);
void engineer_module_component_update(Engineer_Component *data);

#define EVENT(key, size) \
   bool engineer_module_component_event_##key(Engineer_Component *data, void *note, uint64_t size);
EVENTS
#undef EVENT

#define awake(data)  engineer_module_component_awake(data)
#define start(data)  engineer_module_component_start(data)
#define update(data) engineer_module_component_update(data)

#define event(key, data, note, size) engineer_module_component_event_##key(data, note, size)

#include "engineer_module.eo.h"

#endif

