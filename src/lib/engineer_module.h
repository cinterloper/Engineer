#ifndef _ENGINEER_MODULE_H_
#define _ENGINEER_MODULE_H_

#include "../headers/Engineer.h"
#define TARGET(target) ../modules/target.h
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
   #define EVENT(key) ,key##EVENT
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
void engineer_module_component_awake(Eo *module, uint64_t index, Engineer_Component *data);
void engineer_module_component_start(Eo *module, uint64_t index, Engineer_Component *data);
void engineer_module_component_update(Eo *module, uint64_t index, Engineer_Component *data);

#define EVENT(key) \
   bool engineer_module_component_event_##key(Engineer_Component *data, void *note, uint64_t size);
EVENTS
#undef EVENT

#include "engineer_module.eo.h"

/*** Component stub macros ***/

#define awake(data) \
   engineer_module_component_awake(Eo *module EINA_UNUSED, uint64_t index EINA_UNUSED, data)

#define start(data) \
   engineer_module_component_start(Eo *module EINA_UNUSED, uint64_t index EINA_UNUSED, data)

#define update(data) \
   engineer_module_component_update(Eo *module EINA_UNUSED, uint64_t index EINA_UNUSED, data)

#define event(key, data, payload, size) \
   engineer_module_component_event_##key(data, payload, size)

/** Component method macros ***/

// Valid Keys: all single keys:F1-F12:arrowup:arrowdown:arrowleft:arrowright:num0-9,:
//    tab, capslock, lshift, rshift, lctrl, rctrl, alt, altgr, window, lshift, rshift
//#define keypressed(key)  engineer_module_keypressed_get(key)
//#define keyheld(key)
//#define keyreleased(key)

//#define mousedelta(key)
//#define mouseclicked(button)       engineer_module_mouseclicked_get(button)
//#define mousedoubleclicked(button)
//#define mousedragged(button)
//#define mousereleased(button)

#define entity_notify(target, event, payload, size) \
   engineer_scene_notify_event(target, index, event, payload, size)

#define entity_create(parent) \
   engineer_scene_notify_entity_create(module, parent, index)

#define componentcreate(class, parent, payload) \
   engineer_scene_component_create(efl_parent_get(module), eina_inarray_get(pd->id, index), class, parent, payload)

#define component_search(target, class) \
   engineer_scene_entity_component_search(efl_parent_get(module), target, class)

#define component_query(target, key) \
   engineer_scene_component_state_get(module, target, key)



#endif

