#ifndef _ENGINEER_MODULE_H_
#define _ENGINEER_MODULE_H_

#include "Engineer.h"
#define TARGET(target) target.h
   #include STRINGIFY(TARGET(COMPONENT))

#ifndef STATE
   #define STATE
#endif

#ifndef EVENTS
   #define EVENTS
#endif

typedef enum
{
   nullSTATE
   #define FIELD(key, type) ,key##STATE
   STATE
   #undef FIELD

}
Component_State;

typedef enum
{
   nullEVENT
   #define EVENT(key, size) ,key##EVENT
   EVENTS
   #undef EVENT
}
Component_Event;

typedef struct
{
   const char *name;

   uint64_t parent;
   uint64_t nextsibling;
   uint64_t prevsibling;

   #define FIELD(key, type) type key;
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

   #define FIELD(key, type) type##SOA key;
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

   #define FIELD(key, type) type##SOA key;
   STATE
   #undef FIELD
}
Engineer_Module_Frame;

typedef struct
{
   Eina_Hash    *fields;
   Eina_Hash    *events;

   Eina_Hash    *lookup;
   Eina_Inarray *id;
   Eina_Inarray *history;
   Eina_Inarray *buffer;

   Engineer_Module_Frame *past;
   Engineer_Module_Frame *present;
   Engineer_Module_Frame *future;
}
Engineer_Module_Data;

Eo*      engineer_module_new(Eo *parent);
uint64_t engineer_module_classid(void);

void engineer_module_component_awake(Eo *module,
   ComponentID this, uint64_t index, Engineer_Component *data);
void engineer_module_component_start(Eo *module,
   ComponentID this, uint64_t index, Engineer_Component *data);
void engineer_module_component_update(Eo *module,
   ComponentID this, uint64_t index, Engineer_Component *data);

#define EVENT(key, unused) \
   bool engineer_module_component_event_##key(Engineer_Component *data, void *note); //, uint64_t size)
EVENTS
#undef EVENT

#include "engineer_module.eo.h"

#endif

