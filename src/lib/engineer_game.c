#include "engineer_game.h"

typedef struct
{
   char         *path;        // Where the Game folder is located relative to the root drive.  Usually /opt/.
   char         *title;

   unsigned int  modulecount;
   Eina_Inarray *modulequeue;

   Eina_Hash    *nodes;       // A list of connected client and server hosts, also called "nodes" Not used yet.
   Eina_Hash    *scenes;      // A list of pointers to our active scene objects, referenced by thier proper names.
   Eina_Hash    *modules;     // This is a collection of Engineer_Game_Module structs, referenced by thier proper names.
   Eina_Hash    *modulelookup; // Finds the module name for a given module id.

   DB_ENV       *database;    // The handle pointer for our game database file/environment.
   DB           *nodetable;
   DB           *scenetable;
   DB           *moduletable; // This is a list of modules that have been registered to the game, referenced by thier ID.
}
Engineer_Game_Data;

EOLIAN static Efl_Object *
_engineer_game_efl_object_constructor(Eo *obj, Engineer_Game_Data *pd EINA_UNUSED)
{
   return obj;
}

EOLIAN static Efl_Object *
_engineer_game_efl_object_finalize(Eo *obj, Engineer_Game_Data *pd)
{
   // Set up our path elements.
   //if (pd->path == NULL) pd->path = ; // If no path is specified, use current dir.
   //if (pd->name == NULL) pd->name = "Untitled Game";

   // Set up our path var.
   char gamepath[PATH_MAX];
   snprintf(gamepath, sizeof(gamepath), "%s/%s/", pd->path, pd->title); // Usually /opt/$GAMENAME

   // Open the database environment.
   pd->database = NULL;
   db_env_create(&pd->database, 0);
   pd->database->open(
      pd->database,    // DB_ENV ptr.
      gamepath,        // Environment home directory.
      DB_CREATE,       // Open flags.
      0);

   // Load the file pointed to by the path var.
   engineer_game_file_load(obj);

   // Load any registered modules automatically.

   return obj;
}

EOLIAN static void
_engineer_game_efl_object_destructor(Eo *obj, Engineer_Game_Data *pd)
{
   if (pd->database != NULL) pd->database->close(pd->database, 0);

   efl_destructor(efl_super(obj, ENGINEER_GAME_CLASS));
}

EOLIAN static void
_engineer_game_file_load(Eo *obj, Engineer_Game_Data *pd)
{
   if (pd->nodes     != NULL || pd->scenes     != NULL || pd->modules     != NULL ||
       pd->nodetable != NULL || pd->scenetable != NULL || pd->moduletable != NULL)
      engineer_game_file_close(obj);

   //pd->nodes   = eina_hash_string_superfast_new(eng_free_cb);
   pd->scenes  = eina_hash_string_superfast_new(eng_free_cb);
   pd->modules = eina_hash_string_superfast_new(eng_free_cb);

   Eina_List *tables = NULL, *list, *next;
   struct { DB *handle; char *name; } *table, buffer;
   char tablefile[PATH_MAX];

   buffer.handle = pd->nodetable;
   buffer.name   = "Node";
   tables = eina_list_append(tables, &buffer);
   buffer.handle = pd->scenetable;
   buffer.name   = "Scene";
   tables = eina_list_append(tables, &buffer);
   buffer.handle = pd->moduletable;
   buffer.name   = "Module";
   tables = eina_list_append(tables, &buffer);

   EINA_LIST_FOREACH_SAFE(tables, list, next, table)
   {
      snprintf(tablefile, sizeof(tablefile), "data/game/%s.db", table->name);

      table->handle = NULL;
      db_create(&table->handle, NULL, 0);
      table->handle->open(
         table->handle,    // DB structure pointer.
         NULL,             // Transaction pointer.
         tablefile,        // On-disk file that holds the database.
         tablefile,        // Optional logical database name.
         DB_QUEUE,         // Database access method.
         DB_CREATE,        // Open flags.
         0);               // File mode (using defaults).
   }
}

EOLIAN static void
_engineer_game_file_save(Eo *obj EINA_UNUSED, Engineer_Game_Data *pd)
{
   //if (pd->nodetable != NULL) pd->nodetable->sync(pd->nodetable, 0);
   if (pd->scenetable != NULL) pd->scenetable->sync(pd->scenetable, 0);
   if (pd->moduletable != NULL) pd->moduletable->sync(pd->moduletable, 0);
}

EOLIAN static void
_engineer_game_file_close(Eo *obj EINA_UNUSED, Engineer_Game_Data *pd)
{
   //if (pd->nodes != NULL) eina_hash_free_buckets(pd->nodes);
   if (pd->scenes != NULL) eina_hash_free_buckets(pd->scenes);
   if (pd->modules != NULL) eina_hash_free_buckets(pd->modules);

   //if (pd->nodetable != NULL) pd->nodetable->close(pd->nodetable, 0);
   if (pd->scenetable != NULL) pd->scenetable->close(pd->scenetable, 0);
   if (pd->moduletable != NULL) pd->moduletable->close(pd->moduletable, 0);
}

EOLIAN static void
_engineer_game_scene_create(Eo *obj EINA_UNUSED, Engineer_Game_Data *pd EINA_UNUSED,
        const char *name)
{
   // Make sure that a scene with this name does not already exist in the scene db.
   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = name;
   key.size = sizeof(uint);
   key.flags = DB_DBT_USERMEM;
   if (pd->scenetable->get(pd->scenetable, NULL, &key, &data, 0) != DB_NOTFOUND) return;

   // Add an entry to the scene database here.
   pd->scenetable->put(pd->scenetable, NULL, &key, &data, 0);

   engineer_game_scene_load(obj, name);
}

EOLIAN static void
_engineer_game_scene_load(Eo *obj, Engineer_Game_Data *pd,
        const char *name)
{
   // Check to see if an entry for the target scene is present in the game scene database.
   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = name;
   key.size = sizeof(uint);
   key.flags = DB_DBT_USERMEM;
   if (pd->scenetable->get(pd->scenetable, NULL, &key, &data, 0) == DB_NOTFOUND) return;

   // Make sure that the scene file is valid.
   const char path[PATH_MAX];
   snprintf(path, sizeof(path), "%s/data/scenes/%s/", pd->path, name); //fixme
   if (!ecore_file_is_dir(path)) return;

   // Create the scene object and load the data into it.
   Efl_Object *scene;
   scene = efl_add(ENGINEER_SCENE_CLASS, obj,
              engineer_scene_game_set(efl_added, pd->title),
              engineer_scene_name_set(efl_added, name));

   // Add the newly created scene object to the pd->scenes list using it's name as the key.
   if (eina_hash_find(pd->scenes, name)) return;
   eina_hash_add(pd->scenes, name, scene);
}

EOLIAN static void
_engineer_game_scene_save(Eo *obj EINA_UNUSED, Engineer_Game_Data *pd EINA_UNUSED,
        const char *name EINA_UNUSED)
{
}

EOLIAN static void
_engineer_game_scene_unload(Eo *obj, Engineer_Game_Data *pd EINA_UNUSED,
        const char *name)
{
   engineer_game_scene_save(obj, name);
}

EOLIAN static void
_engineer_game_module_register(Eo *obj EINA_UNUSED, Engineer_Game_Data *pd EINA_UNUSED,
        const char *name)
{
   char file[PATH_MAX];
   snprintf(file, sizeof(*file), "data/modules/%s.module", name);
}

EOLIAN static void
_engineer_game_module_load(Eo *obj EINA_UNUSED, Engineer_Game_Data *pd,
       const char *name)
{
   Engineer_Game_Module module;

   char file[PATH_MAX];
   snprintf(file, sizeof(*file), "data/modules/%s.module", name);

   module.handle  = eina_module_new(file);
   eina_module_load(module.handle);

   module.add    = eina_module_symbol_get(module.handle, "engineer_module_add");
   module.load   = eina_module_symbol_get(module.handle, "engineer_module_component_load");
   module.save   = eina_module_symbol_get(module.handle, "engineer_module_component_save");

   module.awake  = eina_module_symbol_get(module.handle, "engineer_module_component_awake");
   module.start  = eina_module_symbol_get(module.handle, "engineer_module_component_start");
   module.update = eina_module_symbol_get(module.handle, "engineer_module_component_update");

   eina_hash_add(pd->modules, name, &module);
}

EOLIAN static void
_engineer_game_module_unload(Eo *obj EINA_UNUSED, Engineer_Game_Data *pd EINA_UNUSED,
        Eo *target EINA_UNUSED)
{
  // Eina_Module *module;

  // module = eina_list_find(pd->modulecache, target);
}

EOLIAN static void
_engineer_game_module_unregister(Eo *obj EINA_UNUSED, Engineer_Game_Data *pd EINA_UNUSED,
        const char *name EINA_UNUSED)
{
}

EOLIAN static char *
_engineer_game_module_lookup(Eo *obj EINA_UNUSED, Engineer_Game_Data *pd,
        uint target)
{
   char *index = eina_hash_find(pd->modulelookup, &target);
   return index;
}
static uint
_engineer_game_module_id_use(Eo *obj EINA_UNUSED, Engineer_Game_Data *pd)
{
   if (eina_inarray_count(pd->modulequeue) == 0)
   {
      eina_inarray_insert_at(pd->modulequeue, 0, &pd->modulecount);
      pd->modulecount += 1;
   }
   uint *newid = eina_inarray_pop(pd->modulequeue);
   return *newid;
}

EOLIAN static void
_engineer_game_module_id_free(Eo *obj EINA_UNUSED, Engineer_Game_Data *pd,
        uint target)
{
   //engineer_scene_component_status_set(obj, target, 0);
   eina_inarray_insert_at(pd->modulequeue, 0, &target);
}

#include "engineer_game.eo.c"
