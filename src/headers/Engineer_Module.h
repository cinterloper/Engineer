#ifndef ENGINEER_MODULE_H_
#define ENGINEER_MODULE_H_

#include "engineer_module.h"

// static_array<ubyte, 128>

/*** Component Core Scripting Stubs ***/

#define awake(data) \
   engineer_module_component_awake(Eo *module EINA_UNUSED,  \
      ComponentID this EINA_UNUSED, uint64_t index EINA_UNUSED, data)

#define start(data) \
   engineer_module_component_start(Eo *module EINA_UNUSED,  \
      ComponentID this EINA_UNUSED, uint64_t index EINA_UNUSED, data)

#define update(data) \
   engineer_module_component_update(Eo *module EINA_UNUSED, \
      ComponentID this EINA_UNUSED, uint64_t index EINA_UNUSED, data)

#define event(key, data, payload) \
   engineer_module_component_event_##key(data, payload)

/** Component Method Macros ***/

// Creates a new Entity, attaches it to a specified parent Entity and returns it's EntityID.
// Effect Speed: Next Frame
#define entity_create(parent) \
   engineer_scene_entity_create(efl_parent_get(module), parent, index)

// Searches for a Component of the specified class and returns it's ComponentID.
// Effect Speed: Immedate/expensive
#define entity_search(target, class) \
   engineer_scene_entity_component_search(efl_parent_get(module), target, class)

// Sends a notice of Event $TYPE with an attached payload.
// Effect Speed: Next Frame
#define entity_notify(target, event, payload) \
   engineer_scene_notify_event(efl_parent_get(module), \
      this, target, event, payload, engineer_module_event_sizeof(module, event))

// Creates a new Component, attaches it to a specified parent Entity, and returns it's ComponentID.
// Effect Speed: Next Frame
#define component_create(class, parent, payload) \
   engineer_scene_component_create(efl_parent_get(module), this, class, parent, payload)

// Takes a ComponentID and a key string and returns the value in the specified state field.
// Effect Speed: Immediate/inexpensive
#define component_query(target, key) \
   engineer_scene_component_state_get(efl_parent_get(module), target, key)

// Gets the present parent of the given ComponentID.
// Effect Speed: Immediate/inexpensive
#define component_parent_get(target) \
   engineer_scene_component_parent_get(efl_parent_get(module), target, 1)


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
