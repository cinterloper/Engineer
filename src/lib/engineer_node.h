#ifndef _ENGINEER_NODE_H_
#define _ENGINEER_NODE_H_

#include "../headers/Engineer.h"
#include "engineer_node.eo.h"

// EntityID's and ComponentID's are each 64 bits long, with the largest 24 bits of the number
//    specifying the cluster Ip address of the originating Node. This allows compatibility with
//    subsets of both private network ranges of IpV4 and IpV6 (10.xxx.xxx.xxx for the former).
// Entity and Component status vars stores the

typedef struct
{
   Eina_Stringshare *path;        // Where the Game folder is located relative to the root drive.
   Eina_Stringshare *game;        // The title of the game the cluster is hosting.

   int           ipaddress;       // The 24 bit cluster Ip subaddress of the host of this node.
   int           mode;            // Stores the mode of this Node, server, client or standalone.
   Eina_Hash    *peers;           // A list of connected server peer nodes.
   Eina_Hash    *scenes;          // Our active scene Efl_Objects, referenced by thier proper names.

   unsigned int  modulecount;     // Stores the present total amount of Modules in the Node.
   Eina_Inarray *modulequeue;     // Stores (presently) free'd Module ID's.
   Eina_Inarray *modulecache;     // Our active Engineer_Node_Module(s), referenced by their ID's.
   Eina_Hash    *modulelookup;    // Finds the module, referenced by it's name string.

   unsigned int  entitycount;     // Stores the total amount of Entities originated by the Node.
   Eina_Inarray *entityqueue;     // Stores (presently) available Entity ID's.
   Eina_Hash    *entitylocate;    // Stores where all Entities originated by this Node are currently stored.
   Eina_Hash    *entitystatus;    // Stores the status of currently loaded EntityID's.

   unsigned int  componentcount;  // Stores the total amount of Components originated by the Node.
   Eina_Inarray *componentqueue;  // Stores (presently) available Component ID's.
   Eina_Hash    *componentlocate; // Stores where all Components originated by this Node are currently stored.
   Eina_Hash    *componentstatus; // (Living/Locked/Dead/Free). Also stores refcount.

   DB_ENV       *database;        // The handle pointer for our game database file/environment.
   DB           *nodetable;
   DB           *scenetable;
   DB           *moduletable;     // This is a list of modules that have been registered to the game, referenced by thier ID.
}
Engineer_Node_Data;

Eo*
engineer_node_add(Eo *obj, const char *path, const char *title);

#endif
