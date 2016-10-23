#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include "engineer_node.eo.h"

// eolian_gen `pkg-config --variable=eolian_flags evas eo efl` --gi -o engineer_module.c engineer_module.eo

typedef struct
{
   char        *director;  // The network address of the director node.
   Eina_Array  *services;  // A list of pointers to active Service objects.

   Eina_Bool    living;
}
Engineer_Node_Data;

/*** Constructors ***/

EOLIAN static Efl_Object *
_engineer_node_constructor(Eo *obj, Engineer_Node_Data *pd)
{
   pd-> living = EINA_TRUE;
}

/*** Callbacks ***/

/*** Node Methods ***/

// Register this node with target director node at the network location listed in the string.
// Note that this function is also used to set up director nodes, just pass the loopback address.
EOLIAN static void
_engineer_node_register(Eo *obj, Engineer_Node_Data *pd,
        char *target)
{
   // Check to see if we are trying to register the loopback, if so, create a director service.
   if (target = "127.0.0.1")
   {
      eo_add(ENGINEER_DIRECTOR_CLASS, obj);
   }
   pd->director = target;
}

EOLIAN static void
_engineer_node_deregister(Eo *obj, Engineer_Node_Data *pd)
{
}

EOLIAN static void
_engineer_node_kill(Eo *obj, Engineer_Node_Data *pd)
{
   pd->living = EINA_FALSE;
}

/*** Director Methods ***/

EOLIAN static void
_engineer_node_director_create(Eo *obj, Engineer_Node_Data *pd)
{
}

/*** Scene Methods ***/

EOLIAN static void
_engineer_node_scene_create(char *name)
{
  // Scene's will have a default modulepath for the core modules, and will automaticall load them.
}

EOLIAN static void
_engineer_node_scene_destroy()
{
}

EOLIAN static void
_engineer_node_scene_save()
{
}

EOLIAN static void
_engineer_node_scene_load()
{
}


#include "engineer_node.eo.c"
