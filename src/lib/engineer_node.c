#include "engineer_node.h"

EOLIAN static Efl_Object *
_engineer_node_efl_object_constructor(Eo *obj, Engineer_Node_Data *pd EINA_UNUSED)
{
   return efl_constructor(efl_super(obj, ENGINEER_NODE_CLASS));
}

EOLIAN static Efl_Object *
_engineer_node_efl_object_finalize(Eo *obj, Engineer_Node_Data *pd)
{
   // Set up our path elements.
   if (pd->path  == NULL) getcwd(pd->path, sizeof(PATH_MAX));
   if (pd->title == NULL) pd->title = "Untitled";

 //pd->nodes        = eina_hash_string_superfast_new(eng_free_cb);
   pd->scenes       = eina_hash_string_superfast_new(eng_free_cb);
   pd->modules      = eina_inarray_new(sizeof(Engineer_Node_Module), 0);
   pd->modulelookup = eina_hash_string_superfast_new(eng_free_cb);

   printf("Finalize Path: %s, Title: %s\n", pd->path, pd->title);

   // Set up our path var.  Usually /opt/$GAMENAME.
   //Eina_Stringshare *gamepath = eina_stringshare_printf("%s/%s/", pd->path, pd->title);
/*
   // Open the database environment.
   pd->database = NULL;
   db_env_create(&pd->database, 0);
   pd->database->open(
      pd->database,              // DB_ENV ptr.
      gamepath,                  // Environment home directory.
      DB_CREATE | DB_INIT_MPOOL, // Open flags.
      0);

   // Load the table files pointed to by the path var.
   engineer_game_file_load(obj);
*/
   printf("Game Module Checkpoint.\n");

   // Load the Sector component module data.
   Engineer_Node_Module *module, blank;
   module = &blank;

   engineer_node_module_register(obj, "Sector");

 //module->add     = &engineer_scene_sector_create;
 //module->load    = &engineer_scene_sector_load;
 //module->save    = &engineer_scene_sector_save;
 //module->destroy = &engineer_scene_sector_destroy;
 //module->dispose = &engineer_scene_sector_dispose;
 //module->lookup  = &engineer_scene_sector_lookup;

 //module->awake = ;
 //module->start = ;
 //module->update = &engineer_scene_sector_iterate;

   eina_inarray_replace_at(pd->modules, 0, module);

   // Load any registered modules automatically.

   return obj;
}

EOLIAN static void
_engineer_node_efl_object_destructor(Eo *obj, Engineer_Node_Data *pd)
{
   if (pd->database != NULL) pd->database->close(pd->database, 0);

   efl_destructor(efl_super(obj, ENGINEER_NODE_CLASS));
}

EOLIAN static const char *
_engineer_node_path_get(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd)
{
  return pd->path;
}

EOLIAN static void
_engineer_node_path_set(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd, const char *path)
{
   pd->path = (char*)path;
}

EOLIAN static const char *
_engineer_node_title_get(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd)
{
  return pd->title;
}

EOLIAN static void
_engineer_node_title_set(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd, const char *title)
{
   pd->title = (char*)title;
}

EOLIAN static void
_engineer_node_file_load(Eo *obj, Engineer_Node_Data *pd)
{
   if (pd->nodes     != NULL || pd->scenes     != NULL || pd->modules     != NULL ||
       pd->nodetable != NULL || pd->scenetable != NULL || pd->moduletable != NULL)
      engineer_node_file_close(obj);

   Eina_List *tables = NULL, *list, *next;
   struct { DB *handle; char *name; } *table, buffer1, buffer2, buffer3;
   char tablefile[PATH_MAX];

   buffer1.handle = pd->nodetable;
   buffer1.name   = "Node";
   tables = eina_list_append(tables, &buffer1);
   buffer2.handle = pd->scenetable;
   buffer2.name   = "Scene";
   tables = eina_list_append(tables, &buffer2);
   buffer3.handle = pd->moduletable;
   buffer3.name   = "Module";
   tables = eina_list_append(tables, &buffer3);

   EINA_LIST_FOREACH_SAFE(tables, list, next, table)
   {
      snprintf(tablefile, sizeof(tablefile), "data/game/%s.db", table->name);
      printf("File Iteration Checkpoint Tablefile: %s\n", tablefile);

      table->handle = NULL;
      db_create(&table->handle, pd->database, 0);
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
_engineer_node_file_save(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd)
{
   //if (pd->nodetable != NULL) pd->nodetable->sync(pd->nodetable, 0);
   if (pd->scenetable  != NULL) pd->scenetable->sync(pd->scenetable, 0);
   if (pd->moduletable != NULL) pd->moduletable->sync(pd->moduletable, 0);
}

EOLIAN static void
_engineer_node_file_close(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd)
{
   //if (pd->nodes != NULL) eina_hash_free_buckets(pd->nodes);
   if (pd->scenes != NULL) eina_hash_free_buckets(pd->scenes);
   //if (pd->modules != NULL) eina_hash_free_buckets(pd->modules);

   //if (pd->nodetable != NULL) pd->nodetable->close(pd->nodetable, 0);
   if (pd->scenetable != NULL) pd->scenetable->close(pd->scenetable, 0);
   if (pd->moduletable != NULL) pd->moduletable->close(pd->moduletable, 0);
}

EOLIAN static Efl_Object *
_engineer_node_scene_create(Eo *obj, Engineer_Node_Data *pd EINA_UNUSED,
        const char *name)
{
   printf("Scene Create Checkpoint\n");
   // Make sure that a scene with this name does not already exist in the scene db.
/*   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = name;
   key.size = sizeof(uint);
   key.flags = DB_DBT_USERMEM;
   if (pd->scenetable->get(pd->scenetable, NULL, &key, &data, 0) != DB_NOTFOUND) return;
*/
   //printf("Scene Create Checkpoint 2.\n");

   // Add an entry to the scene database here.
   //pd->scenetable->put(pd->scenetable, NULL, &key, &data, 0);

   //printf("Scene Create Checkpoint 3.\n");

   return engineer_node_scene_load(obj, name);
}

EOLIAN static Efl_Object *
_engineer_node_scene_load(Eo *obj, Engineer_Node_Data *pd,
        const char *name)
{
/*   // Check to see if an entry for the target scene is present in the game scene database.
   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = name;
   key.size = sizeof(uint);
   key.flags = DB_DBT_USERMEM;
   if (pd->scenetable->get(pd->scenetable, NULL, &key, &data, 0) == DB_NOTFOUND) return;
*/
   printf("Scene Load Checkpoint\n");

   // Make sure that the scene file is valid.
   //const char path[PATH_MAX];
   //snprintf(path, sizeof(path), "%s/data/scenes/%s/", pd->path, name); //fixme
   //if (!ecore_file_is_dir(path)) return;

   // Create the scene object and load the data into it.
   Efl_Object *scene;
   scene = efl_add(ENGINEER_SCENE_CLASS, obj,
              engineer_scene_game_set(efl_added, pd->title),
              engineer_scene_name_set(efl_added, name));

   // Add the newly created scene object to the pd->scenes list using it's name as the key.
   if (eina_hash_find(pd->scenes, name)) return NULL;
   eina_hash_add(pd->scenes, name, scene);

   return scene;
}

EOLIAN static void
_engineer_node_scene_save(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd EINA_UNUSED,
        const char *name EINA_UNUSED)
{
}

EOLIAN static void
_engineer_node_scene_unload(Eo *obj, Engineer_Node_Data *pd EINA_UNUSED,
        const char *name)
{
   engineer_node_scene_save(obj, name);
}

EOLIAN static uint
_engineer_node_module_register(Eo *obj, Engineer_Node_Data *pd,
        const char *name)
{
   // Make sure our module file exists before registering it.
   Eina_Stringshare *file = eina_stringshare_printf("data/modules/%s.module", name);
   if (!ecore_file_exists(file)) {eina_stringshare_del(file); return UINT_NULL;}

   // Check to see if the module name is already registered.
   uint moduleid = (uint)eina_hash_find(pd->modulelookup, name);
   if (moduleid != 0) return moduleid;

   // Set up our module cache data.
   moduleid = engineer_node_module_id_use(obj);
   eina_hash_add(pd->modulelookup, name, &moduleid);

   return moduleid;
}

EOLIAN static void
_engineer_node_module_load(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
       const char *name)
{
   Engineer_Node_Module *module, blank;
   module = &blank;

   engineer_node_module_register(obj, name);

   Eina_Stringshare *file = eina_stringshare_printf("data/modules/%s.module", name);

   printf("Engineer Game Module Load Checkpoint 1.\n");

   module->handle  = eina_module_new(file);
   if (module->handle == NULL) {eina_stringshare_del(file); return;}
   eina_module_load(module->handle);

   printf("Engineer Game Module Load Checkpoint 2.\n");

   #define RETURN {eina_module_free(module->handle); eina_stringshare_del(file); return;}

   module->add  = eina_module_symbol_get(module->handle, "engineer_module_new");
   if (module->add  == NULL) RETURN;
   module->load = eina_module_symbol_get(module->handle, "engineer_module_component_load");
   if (module->load == NULL) RETURN;
   module->save = eina_module_symbol_get(module->handle, "engineer_module_component_save");
   if (module->save == NULL) RETURN;

   module->awake  = eina_module_symbol_get(module->handle, "engineer_module_component_awake");
   if (module->awake  == NULL) RETURN;
   module->start  = eina_module_symbol_get(module->handle, "engineer_module_component_start");
   if (module->start  == NULL) RETURN;
   module->update = eina_module_symbol_get(module->handle, "engineer_module_component_update");
   if (module->update == NULL) RETURN;

   #undef RETURN

   printf("Engineer Game Module Load Checkpoint 3.\n");

   eina_inarray_push(pd->modules, module);

   printf("Engineer Game Module Load Checkpoint 4.\n");
}

EOLIAN static void
_engineer_node_module_unload(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd EINA_UNUSED,
        Eo *target EINA_UNUSED)
{
  // Eina_Module *module;

  // module = eina_list_find(pd->modulecache, target);
}

EOLIAN static void
_engineer_node_module_unregister(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd EINA_UNUSED,
        const char *name EINA_UNUSED)
{
}

EOLIAN static Engineer_Node_Module *
_engineer_node_module_lookup(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        uint target)
{
   Engineer_Node_Module *module;

   module = eina_inarray_nth(pd->modules, target);

   return module;
}

EOLIAN static Engineer_Node_Module *
_engineer_node_module_lookup_by_type(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        const char *target)
{
   uint index;
   Engineer_Node_Module *module;

   index  = (uint)eina_hash_find(pd->modulelookup, target);
   module = eina_inarray_nth(pd->modules, index);

   return module;
}

static uint
_engineer_node_module_id_use(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd)
{
   if (eina_inarray_count(pd->modulequeue) == 0)
   {
      Engineer_Node_Module blank;
      memset(&blank, 0, sizeof(Engineer_Node_Module));
      eina_inarray_push(pd->modules, &blank);

      eina_inarray_push(pd->modulequeue, &pd->modulecount);
      pd->modulecount += 1;
   }
   uint *newid = eina_inarray_pop(pd->modulequeue);
   return *newid;
}

EOLIAN static void
_engineer_node_module_id_free(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        uint target)
{
   //engineer_scene_component_status_set(obj, target, 0);
   eina_inarray_insert_at(pd->modulequeue, 0, &target);
}

#include "engineer_node.eo.c"
