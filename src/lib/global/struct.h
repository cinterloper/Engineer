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

   Eo *
   (*module_new)(Eo *scene);
   Eina_Bool
   (*module_update)(Eo *module);

   Eina_Bool
   (*component_factory)(Eo *module,
      ComponentID target, EntityID parent, void *input);

   Eina_Bool
   (*component_create)(Eo *module,
      EntityID sender, void *class, ComponentID componentid, EntityID parent, void *payload);

   void *component_destroy;
   void *component_archive;
   void *component_recall;
   void *component_sizeof;
   void *component_lookup;

   void
   (*component_attach)(Eo *module,
      ComponentID target, EntityID newparent);

   ComponentID
   (*component_siblingnext_get)(Eo *module,
      ComponentID target);
   void
   *component_state_get;
}
Engineer_Component_Class;

#endif

