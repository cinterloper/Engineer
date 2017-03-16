#ifndef ENGINEER_MODULE_H_
#define ENGINEER_MODULE_H_

#include "engineer_module.h"

/*** Component Core Scripting Stubs ***/

#define awake(data) \
   engineer_module_component_awake(Eo *module EINA_UNUSED, uint64_t index EINA_UNUSED, data)

#define start(data) \
   engineer_module_component_start(Eo *module EINA_UNUSED, uint64_t index EINA_UNUSED, data)

#define update(data) \
   engineer_module_component_update(Eo *module EINA_UNUSED, uint64_t index EINA_UNUSED, data)

#define event(key, data, payload, size) \
   engineer_module_component_event_##key(data, payload, size)

/** Component Method Macros ***/

// Creates a new Entity, attaches it to a specified parent Entity and returns it's EntityID.
// Effect Speed: Next Frame
#define entity_create(parent) \
   engineer_scene_entity_create(module, parent, index)

// Searches for a Component of the specified class and returns it's ComponentID.
// Effect Speed: Immedate/expensive
#define entity_search(target, class) \
   engineer_scene_entity_component_search(efl_parent_get(module), target, class)

// Sends a notice of Event $TYPE with an attached payload of a specified size.
// Effect Speed: Next Frame
#define entity_notify(target, event, payload, size) \
   engineer_scene_notify_event(target, index, event, payload, size)

// Creates a new Component, attaches it to a specified parent Entity, and returns it's ComponentID.
// Effect Speed: Next Frame
#define component_create(class, parent, payload) \
   engineer_scene_component_create(efl_parent_get(module), eina_inarray_get(pd->id, index), \
      class, parent, payload)

// Takes a ComponentID and a key string and returns the value in the specified state field.
// Effect Speed: Immediate/inexpensive
#define component_query(target, key) \
   engineer_scene_component_state_get(module, target, key)


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

#endif
