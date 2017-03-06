#ifndef _ENGINEER_SCENE_H_
#define _ENGINEER_SCENE_H_

#include "../headers/Engineer.h"

typedef struct
{
   Eina_Inarray *name;

   Eina_Inarray *parent;
   Eina_Inarray *siblingnext;
   Eina_Inarray *siblingprev;
   Eina_Inarray *firstentity;
   Eina_Inarray *firstcomponent;

   Eina_Inarray *inbox;
   Eina_Inarray *outbox;
}
Engineer_Entity_History;

typedef struct
{
   double timestamp;

   // Active Entity Data Cache.
   Eina_Inarray *name;

   Eina_Inarray *parent;
   Eina_Inarray *siblingnext;
   Eina_Inarray *siblingprev;
   Eina_Inarray *firstentity;
   Eina_Inarray *firstcomponent;

   Eina_Inarray *inbox;  // Inbox for Entity Scope Notices, for each Current Entity.
   Eina_Inarray *outbox; // Outbox for Scene Scope Notices, for each Current Entity.
}
Engineer_Scene_Frame;

typedef struct
{
   const char   *name;            // The name of this scene.
   uint64_t      size;            // Diameter, in the quantum unit.
   uint32_t      shape;           // 0 for a cube, 1 for a sphere

   Ecore_Timer    *iterator;      // Triggers our frame update, the frequency can be changed.
   uint            clockrate;     // This value controls the FPS the scene is set to run at.
   Eina_Inarray   *timecard;      // Stores the completion time for the present and past frames.

   Eina_Hash    *lookup;          // Entity index lookup by ID.
   Eina_Inarray *id;              // EntityID reverse lookup table.
   Eina_Inarray *history;         // Stores all changes made to our Entity data frame-by-frame.
   Eina_Inarray *buffer;          // The buffer that the most recent 3 frames are stored in.

   Engineer_Scene_Frame *past;    // Used for interpolation. Is the frame before the present one.
   Engineer_Scene_Frame *present; // Points to the current frame data.
   Engineer_Scene_Frame *future;  // Points to the frame currently receiving the iterator update.

 //Engineer_Octspace *broadphase; // Our broadphase "Octspace" type octree, used by Transform.
   Eina_Hash         *modules;    // Module Data Eo lookup hash, using murmur3 hashes as keys.
}
Engineer_Scene_Data;

Eo *
engineer_scene_new(Eo *parent, const char *name);

Eina_Bool _engineer_scene_iterate_cb(void *obj);

#define NOTIFY(a, b, c) \
   engineer_scene_entity_notify(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED, a, b, c)

#include "engineer_scene.eo.h"

#endif
