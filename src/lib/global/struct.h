#ifndef _ENGINEER_GLOBAL_STRUCTURES_H_
#define _ENGINEER_GLOBAL_STRUCTURES_H_

#include <Ecore_Getopt.h>
#include <Elementary.h>
#include "type/sclr.h"

typedef const char* ClassLabel;
typedef const char* StateLabel;
typedef const char* EventLabel;

typedef struct
{
   ClassID   id;
   void     *eina;

   uint64_t size;

   // Module Management Methods.
   Eo *
   (*module_new)(Eo *scene);
   Eina_Bool
   (*module_update)(Eo *module);

   // Component Metadata getters/setters.
   Index
   (*component_lookup)(Eo *module, ComponentID componentid);
   void
   (*component_parent_set)(Eo *module, ComponentID target, EntityID newparent);
   EntityID
   (*component_parent_get)(Eo *module, ComponentID target);
   void
   (*component_siblingnext_set)(Eo *module, ComponentID target, ComponentID newsibling);
   ComponentID
   (*component_siblingnext_get)(Eo *module, ComponentID target);
   void
   (*component_siblingprev_set)(Eo *module, ComponentID target, ComponentID newsibling);
   ComponentID
   (*component_siblingprev_get)(Eo *module, ComponentID target);

   // Component Services.
   Eina_Bool
   (*component_factory)(Eo *module,
      ComponentID target, EntityID parent, void *input);

   // Component Methods.
   Eina_Bool
   (*component_create)(Eo *module,
      EntityID sender, void *class, ComponentID componentid, EntityID parent, void *payload);
   void
   (*component_attach)(Eo *module,
      ComponentID target, EntityID newparent);
   void *
   (*component_state_get)(Eo *module, ComponentID target, StateLabel key);
}
Engineer_Component_Class;

#endif

