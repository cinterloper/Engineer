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

typedef struct
{
   const char *name;

   uint64_t parent;
   uint64_t nextsibling;
   uint64_t prevsibling;
}
Engineer_Component;

typedef struct
{
   Eina_Inarray *name;

   Eina_Inarray *parent;
   Eina_Inarray *siblingnext;
   Eina_Inarray *siblingprev;

}
Engineer_Component_History;

typedef struct
{
   Eina_Inarray *name;

   Eina_Inarray *parent;
   Eina_Inarray *siblingnext;
   Eina_Inarray *siblingprev;
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

#endif

