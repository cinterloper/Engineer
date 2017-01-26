#ifndef _ENGINEER_MODULE_H_
#define _ENGINEER_MODULE_H_

#include "../../headers/Engineer.h"

#ifndef NAME
   #define NAME default
#endif

#ifndef DATA
   #define DATA
#endif

#define BUFFER NAME_Component_Buffer
#define HANDLE NAME_Component_Handle
#define SYMBOL NAME_engineer_module

#define factory(a)      _SYMBOL_factory(a, Engineer_Module_Data *pd EINA_UNUSED)
#define awake(a, b)     _SYMBOL_awake(Eo *obj EINA_UNUSED, a, b)
#define start(a, b)     _SYMBOL_start(Eo *obj EINA_UNUSED, a, b)
#define update(a, b, c) _SYMBOL_update(Eo *obj EINA_UNUSED, a, b, c)

typedef struct
{
   Engineer_Scene_Component *component;

   #define VAR(TYPE, KEY) \
      TYPEBuffer KEY;
   DATA
   #undef VAR
}
BUFFER;

typedef struct
{
   Engineer_Scene_Component *component;

   #define VAR(TYPE, KEY) \
      TYPE *KEY;
   DATA
   #undef VAR
}
HANDLE;

typedef struct
{
   uint  index;

   uint  offsetactive;
   uint  offsetpassive;

   HANDLE    *cache;
   Eina_Hash *lookup;
}
Engineer_Module_Frame;

typedef struct
{
   Engineer_Scene_Data   *scene;    // Stores the pointer of the parent Scene private data.

   Eina_Inarray          *timeline;

   Engineer_Module_Frame *past;     // Used for interpolation. Is the frame before the present one.
   Engineer_Module_Frame *present;  // Points to the current frame data.
   Engineer_Module_Frame *future;   // Points to the frame currently receiving the iterator update.

   DB        *table;
}
Engineer_Module_Data;

#include "engineer_module.eo.h"

#endif
