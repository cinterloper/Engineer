#define EFL_BETA_API_SUPPORT
#include <Eo.h>
#include "engineer_director.eo.h"

//  Project .db files will be stored in /var/db/projectname or STEAMAPPDIR/projectname/var/db

typedef struct
{
   char       *project; // The name of the project that this server/cluster is running.
   Eina_Array *nodes;   // A list of network address strings for each registered node.
}
Engineer_Director_Data;

/*** Constructor ***/

EOLIAN static Efl_Object *
_engineer_director_constructor(Eo *obj, Engineer_Director_Data *pd,
        char *project)
{
   // Set up the master node for our database cluster.
   // See if there is a pre-existing project table for this project.
   // If so, load project data from the database.
   // If not, create new project data tables.
}

/*** Callbacks ***/

EOLIAN static void
_engineer_director_node_registration_cb(Eo *obj, Engineer_Director_Data *pd)
{
}

EOLIAN static void
_engineer_director_node_deregistration_cb(Eo *obj, Engineer_Director_Data *pd)
{
}

/*** Project Methods ***/

EOLIAN static void
_engineer_director_project_set(Eo *obj, Engineer_Director_Data *pd,
        char *target)
{
   pd->project = target;
}

EOLIAN static char *
_engineer_director_project_get(Eo *obj, Engineer_Director_Data *pd)
{
   return pd->project;
}

EOLIAN static void
_engineer_director_project_init()
{
}

EOLIAN static void
_engineer_director_project_save()
{
}

/*** Scene Methods***/

EOLIAN static void
_engineer_director_scene_load(Eo *obj, Engineer_Director_Data *pd,
        char *node, char *scene)
{

}

#include "engineer_director.eo.c"
