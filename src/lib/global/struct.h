#ifndef _ENGINEER_GLOBAL_STRUCTURES_H_
#define _ENGINEER_GLOBAL_STRUCTURES_H_

#include <Ecore_Getopt.h>
#include <Elementary.h>
#include "type/sclr.h"

// 585 = 512 + 64 + 8 + 1

typedef Eina_Bool   bool;

typedef const char* String;
typedef const char* ClassLabel;
typedef const char* StateLabel;
typedef const char* EventLabel;

typedef struct
{
   GLfloat location[3];
   GLuint type;
   GLfloat color[3];
   GLfloat size;
}
Collider_Data;

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

   // Cache Utility API
   uint64_t
   (*cache_sizeof)(Eo *module);

   // Component Services.
   Eina_Bool
   (*component_factory)(Eo *module, ComponentID target, EntityID parent, void *input);
   Index
   (*component_index_get)(Eo *module, ComponentID componentid);
   void
   (*component_parent_set)(Eo *module, ComponentID target, EntityID newparent);
   EntityID
   (*component_parent_get)(Eo *module, ComponentID target, uint64_t offset);
   void
   (*component_siblingnext_set)(Eo *module, ComponentID target, ComponentID newsibling);
   ComponentID
   (*component_siblingnext_get)(Eo *module, ComponentID target, uint64_t offset);
   void
   (*component_siblingprev_set)(Eo *module, ComponentID target, ComponentID newsibling);
   ComponentID
   (*component_siblingprev_get)(Eo *module, ComponentID target, uint64_t offset);
   void *
   (*component_state_get)(Eo *module, ComponentID target, StateLabel key);
}
Engineer_Component_Class;

#endif

