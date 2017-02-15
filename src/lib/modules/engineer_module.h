#ifndef _ENGINEER_MODULE_H_
#define _ENGINEER_MODULE_H_

#ifndef PROJECT
   #define PROJECT
#endif
#ifndef SYMBOL
   #define SYMBOL
#endif
#ifndef FIELDS
   #define FIELDS
#endif
#ifndef RESPONSES
   #define RESPONSES
#endif

#include "../../headers/Engineer.h"
#include "engineer_module.eo.h"

#define COMPONENT PROJECT_SYMBOL_Data
typedef struct
{
   const uint64_t  this;
   const char     *name;

   const uint64_t  parent;
   const uint64_t  nextsibling;
   const uint64_t  prevsibling;

   #define FIELD(KEY, TYPE) \
      TYPE KEY;
   FIELDS
   #undef FIELD
}
COMPONENT;

typedef struct
{

   uint64_t      id; // Much like war, this never changes.
   Eina_Inarray *name;

   Eina_Inarray *parent;
   Eina_Inarray *siblingnext;
   Eina_Inarray *siblingprev;

   #define FIELD(KEY, TYPE) \
      TYPE##SOA KEY;
   FIELDS
   #undef FIELD
}
Engineer_Component_History;

typedef struct
{
   uint64_t timestamp;

   // All of the following vars are Engineer_Component data Arrays.
   Eina_Inarray *id;     // This field is used to correlate array indices to Component ID's.
   Eina_Inarray *name;

   Eina_Inarray *parent;
   Eina_Inarray *siblingnext;
   Eina_Inarray *siblingprev;

   #define FIELD(KEY, TYPE) \
      TYPE##SOA KEY;
   FIELDS
   #undef FIELD
}
Engineer_Module_Frame;

typedef struct
{
   uint64_t               class;     // Stores Class ID for the Scene Eo accesors.

   Eina_Inarray          *buffer;    // Triple framebuffer that most recent 3 frames are stored in.

   Engineer_Module_Frame *past;      // Used for interpolation. Is the frame before the present one.
   Engineer_Module_Frame *present;   // Points to the current frame data.
   Engineer_Module_Frame *future;    // Points to the frame currently receiving the iterator update.

   Eina_Hash *history;               // Stores historical record of Component data.
   Eina_Hash *lookup;                // This is our lookup hash for correlating Component ID's to array indices.
}
Engineer_Module_Data;

extern void
engineer_module_update(COMPONENT *buffer);

#endif

