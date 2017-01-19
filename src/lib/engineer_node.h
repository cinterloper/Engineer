#ifndef _ENGINEER_NODE_H_
#define _ENGINEER_NODE_H_

#include "../headers/Engineer.h"
#include "engineer_node.eo.h"

typedef struct
{
   char         *path;         // Where the Game folder is located relative to the root drive.  Usually /opt/.
   char         *title;

   unsigned int  modulecount;
   Eina_Inarray *modulequeue;

   Eina_Hash    *nodes;        // A list of connected client and server hosts, also called "nodes" Not used yet.
   Eina_Inarray *modules;      // This is a collection of Engineer_Game_Module structs, referenced by their ID's.
   Eina_Hash    *modulelookup; // Finds the module, referenced by it's name string.

   Eina_Hash    *scenes;       // A list of pointers to our active scene objects, referenced by thier proper names.

   DB_ENV       *database;     // The handle pointer for our game database file/environment.
   DB           *nodetable;
   DB           *scenetable;
   DB           *moduletable;  // This is a list of modules that have been registered to the game, referenced by thier ID.
}
Engineer_Node_Data;

#endif
