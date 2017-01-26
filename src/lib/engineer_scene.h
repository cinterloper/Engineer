#ifndef _ENGINEER_SCENE_H_
#define _ENGINEER_SCENE_H_

#include "../headers/Engineer.h"

#include "engineer_scene.eo.h"

typedef struct
{
   uint  index;
   uint  timestamp;

   Eina_Inarray *entitycache;
   Eina_Hash    *entitylookup;

   Eina_Inarray *componentcache;
   Eina_Hash    *componentlookup;
}
Engineer_Scene_Frame;

typedef struct
{
   Eo *node;                      // Pointer to the Parent Node Eo.
   // void *nodepd;

   const char   *name;            // The name of this scene. MUST be unique, the code will check.
   uint          size;

   Efl_Loop_Timer *iterator;      // Triggers our frame update, the frequency can be changed.
   uint            clockrate;     // This value controls the FPS the scene is set to run at.

   Eina_Inarray   *timeline;      // This contains an inarray of our recent Enginer_Scene_Frame(s).
   uint            retention;     // This value controls how many recent Frames the Scene stores.
   uint            current;       // This is used to store the current Scene_Frame inarray index.

   Engineer_Scene_Frame *past;    // Used for interpolation. Is the frame before the present one.
   Engineer_Scene_Frame *present; // Points to the current frame data.
   Engineer_Scene_Frame *future;  // Points to the frame currently receiving the iterator update.

   Eina_Hash *datacache;          // Scene Module Data lookup hashtable, using ModuleID's as inputs.

   DB *scenetable;

   DB *entitymeta;
   DB *entitytable;

   DB *componentmeta;
   DB *componenttable;

   // To be moved to the Game Eo later.
   unsigned int  entitycount;     // Stores the present total amount of Entities in the Scene.
   Eina_Inarray *entityqueue;     // Stores (presently) free'd Entity ID's.

   unsigned int  componentcount;  // Stores the present total amount of Components in the Scene.
   Eina_Inarray *componentqueue;  // Stores (presently) free'd Component ID's.
}
Engineer_Scene_Data;

EOLIAN Eo *
engineer_scene_add(Eo *obj, const char *name);

static void
_engineer_scene_iterate_init_task(void *data, Ecore_Thread *thread);

static void
_engineer_scene_iterate_init_done(void *data, Ecore_Thread *thread);

static void
_engineer_scene_iterate_init_cancel(void *data, Ecore_Thread *thread);

EOLIAN static Eina_Bool
_engineer_scene_iterate_cb(void *data);

EOLIAN static Eina_Bool
_engineer_scene_iterate_module_cb(const Eina_Hash *hash, const void *key,
        void *data, void *fdata);

EOLIAN static Eina_Bool
_engineer_scene_iterate_entity_cb(const Eina_Hash *hash, const void *key,
        void *data, void *fdata);

EOLIAN static Eina_Bool
_engineer_scene_iterate_component_cb(const Eina_Hash *hash, const void *key,
        void *data, void *fdata);

#endif
