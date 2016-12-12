#include "engineer_scene.h"

// In order to set up a Scene, create and attach a Scene object to the Engine, and then add your
// desired Modules in afterwards.

// eolian_gen `pkg-config --variable=eolian_flags ecore eo evas efl` --include=. --gc -o engineer_scene.eo.c engineer_scene.eo

typedef struct
{
   uint         id;         // This is a unique id on a per-scene basis.
   Eina_Module *module;
   DB          *components; // Pointer to the db file handle.

   //void        *data;
   void        *add,   *load,  *save;
   void        *awake, *start, *update;
}
Engineer_Scene_DB_Module;

/*** Object Data ***/

typedef struct
{
   const char   *game;           // Title of the game this scene belongs to. Must also be unique.
   const char   *name;            // The name of this scene. MUST be unique, the code will check.

   unsigned int  entitycount;
   Eina_Inarray *entityqueue;
   unsigned int  componentcount;
   Eina_Inarray *componentqueue;

   Eina_Inarray *modulecache;
   Eina_Hash    *modulelookup;

   Eina_Inarray *entitycache;     // Our in-core Entity data cache.
   Eina_Hash    *entitylookup;    // EntityID lookup hashtable.
   Eina_Inarray *componentcache;  // Our in-core Component data cache.
   Eina_Hash    *componentlookup; // ComponentID lookup hashtable.
   Eina_Inarray *sectorcache;     // Our in-core Gremlin data cache.
   Eina_Hash    *sectorlookup;    // Gremlin component lookup hashtable, uses a ComponentID.

   DB           *moduletable;

   DB           *entitymeta;
   DB           *entitytable;
   DB           *componentmeta;
   DB           *componenttable;
   DB           *sectortable;
}
Engineer_Scene_Data;

/*** Constructors ***/

EOLIAN static Efl_Object *
_engineer_scene_efl_object_constructor(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED)
{
   // Check to see if null has been passed in the name variable.
   /*if (projectname == NULL)
   {
      fprintf(stderr, "[ERROR] Sce*ne construction failed: Invalid project name! (NULL)");
      return NULL;
   }
   if (scenename == NULL)
   {
      fprintf(stderr, "[ERROR] Scene construction failed: Invalid scene name! (NULL)");
      return NULL;
   }*/

   // Check to see if the given names' string contains illegal characters.
   //if (strstr(scenename, "\0") || strstr(scenename, "/") || strstr(scenename, "*") ||
   //    strstr(scenename, ".") ) {}

   // Check to see if the given names' string matches any other Scene's name string.

   return efl_constructor(efl_super(obj, ENGINEER_SCENE_CLASS));
}

Efl_Object *
_engineer_scene_efl_object_finalize(Eo *obj, Engineer_Scene_Data *pd)
{
   // Set up the free ID queues.
   pd->entitycount    = 0;
   pd->entityqueue    = eina_inarray_new(sizeof(unsigned int), 0);
   pd->componentcount = 0;
   pd->componentqueue = eina_inarray_new(sizeof(unsigned int), 0);

   // Create the in-memory data cache and it's lookup tables.
   pd->modulecache     = eina_inarray_new(sizeof(Engineer_Game_Module*), 0);
   pd->modulelookup    = eina_hash_int32_new(eng_free_cb);

   pd->entitycache     = eina_inarray_new(sizeof(Engineer_Scene_Entity), 0);
   pd->entitylookup    = eina_hash_int32_new(eng_free_cb);
   pd->componentcache  = eina_inarray_new(sizeof(Engineer_Scene_Component), 0);
   pd->componentlookup = eina_hash_int32_new(eng_free_cb);
   pd->sectorcache     = eina_inarray_new(sizeof(Engineer_Scene_Sector), 0);
   pd->sectorlookup    = eina_hash_int32_new(eng_free_cb);
/*
   Eina_List *tables = NULL, *list, *next;
   struct { DB *handle; char *name; } *table, buffer1, buffer2, buffer3, buffer4, buffer5;
   char scenefile[PATH_MAX];

   buffer1.handle = pd->entitymeta;
   buffer1.name   = "Entity.Metadata";
   tables = eina_list_append(tables, &buffer1);
   buffer2.handle = pd->entitytable;
   buffer2.name   = "Entity";
   tables = eina_list_append(tables, &buffer2);
   buffer3.handle = pd->componentmeta;
   buffer3.name   = "Component.Metadata";
   tables = eina_list_append(tables, &buffer3);
   buffer4.handle = pd->componenttable;
   buffer4.name   = "Component";
   tables = eina_list_append(tables, &buffer4);
   buffer5.handle = pd->sectortable;
   buffer5.name   = "Sector";
   tables = eina_list_append(tables, &buffer5);

   EINA_LIST_FOREACH_SAFE(tables, list, next, table)
   {
      printf("Scene Table Name: %s\n", table->name);
      snprintf(scenefile, sizeof(scenefile), "data/scenes/%s/%s.db", pd->name, table->name);

      table->handle = NULL;
      db_create(&table->handle, NULL, 0);
      table->handle->open(
         table->handle,    // DB structure pointer.
         NULL,             // Transaction pointer.
         scenefile,        // On-disk file that holds the database.
         scenefile,        // Optional logical database name.
         DB_QUEUE,         // Database access method.
         DB_CREATE,        // Open flags.
         0);               // File mode (using defaults).
   }

   //engineer_scene_file_load(obj);
*/
   // If our database is new, create a root Entity and set it up.
   if (pd->entitycount == 0)
   {
      Engineer_Scene_Entity *root, blank;
      uint buffer;

      root = &blank;
      memset(root, 0, sizeof(Engineer_Scene_Entity));

      root->name = eina_stringshare_add("Scene Root");
      root->id   = engineer_scene_entity_id_use(obj);

      buffer = eina_inarray_push(pd->entitycache, root);
      root   = eina_inarray_nth(pd->entitycache, buffer);
      eina_hash_add(pd->entitylookup, &root->id, root);

      root->sector         = 0;
      root->status         = 3;
      root->referencecount = 1;

      root->parent         = 0;
      root->siblingnext    = 0;
      root->siblingprev    = 0;
      root->firstcomponent = UINT_NULL;
      root->firstentity    = UINT_NULL;

      printf("Root Entity Create Checkpoint. EID: %d\n", root->id);
   }

   return obj;
}

EOLIAN static void
_engineer_scene_efl_object_destructor(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
   // For each loaded entity and it's components, flush all data in cache to DB.
   if (pd->sectortable    != NULL) pd->sectortable->close(pd->sectortable, 0);
   if (pd->componenttable != NULL) pd->componenttable->close(pd->componenttable, 0);
   if (pd->entitytable    != NULL) pd->entitytable->close(pd->entitytable, 0);
}

/*** Project property getter/setters. ***/

EOLIAN static const char *
_engineer_scene_game_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
  return pd->game;
}

EOLIAN static void
_engineer_scene_game_set(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd, const char *path)
{
   pd->game = path;
}

EOLIAN static const char *
_engineer_scene_name_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
  return pd->name;
}

EOLIAN static void
_engineer_scene_name_set(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd, const char *name)
{
   pd->name = name;
}

/*** Database File Methods ***/

EOLIAN static void
_engineer_scene_file_load(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
   //ecore_file_is_dir(path)

   // Load the entity population from the first entitymeta index.
   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = 0;
   key.size = sizeof(uint);
   key.flags = DB_DBT_USERMEM;

   if (pd->entitymeta->get(pd->entitymeta, NULL, &key, &data, 0) != DB_NOTFOUND)
   {
      pd->entitycount = *(uint*)data.data;
   }

   // For each valid entitymeta entry after the first entry, push it to the entityqueue.
   uint keyindex = 1;
   while(keyindex != 0)
   {
      memset(&key, 0, sizeof(DBT));
      memset(&data, 0, sizeof(DBT));
      key.data = &keyindex;
      key.size = sizeof(uint);
      key.flags = DB_DBT_USERMEM;

      if (pd->entitymeta->get(pd->entitymeta, NULL, &key, &data, 0) != DB_NOTFOUND)
      {
         eina_inarray_push(pd->entityqueue, (uint*)data.data);
         keyindex += 1;
      }
      else keyindex = 0;
   }

   // Load the component population from the first componentmeta index.
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = 0;
   key.size = sizeof(uint);
   key.flags = DB_DBT_USERMEM;

   if (pd->componentmeta->get(pd->componentmeta, NULL, &key, &data, 0) != DB_NOTFOUND)
   {
      pd->componentcount = *(uint*)data.data;
   }

   // For each valid componentmeta entry after the first entry, push it to the componentqueue.
   keyindex = 1;
   while(keyindex != 0)
   {
      memset(&key, 0, sizeof(DBT));
      memset(&data, 0, sizeof(DBT));
      key.data = &keyindex;
      key.size = sizeof(uint);
      key.flags = DB_DBT_USERMEM;

      if (pd->componentmeta->get(pd->componentmeta, NULL, &key, &data, 0) != DB_NOTFOUND)
      {
         eina_inarray_push(pd->componentqueue, (uint*)data.data);
         keyindex += 1;
      }
      else keyindex = 0;
   }
}

EOLIAN static void
_engineer_scene_file_save(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd EINA_UNUSED)
{
}

EOLIAN static void
_engineer_scene_file_sync(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
   pd->entitytable->sync(pd->entitytable, 0);
   pd->componenttable->sync(pd->componenttable, 0);
   pd->sectortable->sync(pd->sectortable, 0);
}

/*** Entity Methods ***/

EOLIAN static uint
_engineer_scene_entity_create(Eo *obj, Engineer_Scene_Data *pd,
        uint parent, const char *name)
{
   Engineer_Scene_Entity *entity, blank;
   uint buffer;

   entity = &blank;
   memset(entity, 0, sizeof(Engineer_Scene_Entity));

   entity->name = eina_stringshare_printf("%s", name);
   entity->id   = engineer_scene_entity_id_use(obj);

   buffer = eina_inarray_push(pd->entitycache, entity);
   entity = eina_inarray_nth(pd->entitycache, buffer);
   eina_hash_add(pd->entitylookup, &entity->id, entity);

   entity->firstcomponent = UINT_NULL;
   entity->firstentity    = UINT_NULL;

   engineer_scene_entity_parent_set(obj, entity->id, parent);
/*
   // Create a database entry for the entity.
   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &payload.id;
   key.size = sizeof(uint);
   data.data = &payload;
   data.size = sizeof(payload);

   pd->entitytable->put(pd->entitytable, NULL, &key, &data, 0);
*/
   printf("Entity Create Checkpoint. EID: %d, Parent EID: %d, NextSib EID: %d, PrevSib EID: %d, Name: %s\n",
      entity->id, entity->parent, entity->siblingprev, entity->siblingnext, entity->name);

   return entity->id;
}

EOLIAN static void
_engineer_scene_entity_load(Eo *obj, Engineer_Scene_Data *pd,
        uint target)
{
   Engineer_Scene_Entity *payload = engineer_scene_entity_lookup(obj, target);

   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &target;
   key.size = sizeof(uint);
   key.flags = DB_DBT_USERMEM;

   pd->entitytable->get(pd->entitytable, NULL, &key, &data, 0);
   payload = data.data;

   // If this entity does not exist in the db, return without doing anything.
   if (payload == NULL) return;

   // If this entities' current sector is not loaded, return without doing anything.
   if (payload->sector == 0) return;

   // If this entity has an unloaded parent, return without doing anything.
   if (eina_hash_find(pd->entitylookup, &payload->parent) == NULL) return;

   // We need to call engineer_module_component_load() on each of this Entities' component data,
   // in this Entities' Sector cache.
   Eo *(*component_load)(Eo *obj, uint target);
   Engineer_Scene_Sector *sector = engineer_scene_sector_lookup(obj, payload->sector);
   Engineer_Game_Module  *module;
   uint index, count = eina_inarray_count(pd->modulecache);
   for (uint current = 0; current < count; current++)
   {
      module = eina_inarray_nth(pd->modulecache, current);
      component_load = module->load;
      index = *(uint*)eina_hash_find(sector->lookup, &current);
      component_load(eina_inarray_nth(sector->cache, index), target);
   }

   // If this entity does not have a sector component, and has any child entities, load them.
   if (payload->firstentity != UINT_NULL) // && sector component check
   {
      Engineer_Scene_Entity *current  = engineer_scene_entity_lookup(obj, payload->firstentity);
      Engineer_Scene_Entity *terminus = engineer_scene_entity_lookup(obj, current->siblingprev);

      while (current->id != terminus->id)
      {
         engineer_scene_entity_load(obj, current->id);
         current = engineer_scene_entity_lookup(obj, current->siblingnext);
      }
      engineer_scene_entity_load(obj, terminus->id);
   }

   // Add the Entity data entry to the Entity cache and lookup table.
   uint cacheindex = eina_inarray_push(pd->entitycache, payload);
   eina_hash_add(pd->entitylookup, &payload->id, &cacheindex);
}

EOLIAN static void
_engineer_scene_entity_save(Eo *obj, Engineer_Scene_Data *pd,
        uint target)
{
   Engineer_Scene_Entity *payload = engineer_scene_entity_lookup(obj, target);

   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &target;
   key.size = sizeof(uint);
   data.data = payload;
   data.size = sizeof(*payload);

   pd->entitytable->put(pd->entitytable, NULL, &key, &data, 0);

   // We need to call engineer_module_data_save() on each of it's components for each of the parent sector's modules.

   // If this entity has any child entities, save those as well, unless this entity has a Sector component.

   // Remove the entity data entry from the Entity cache and lookup table.
   Engineer_Scene_Entity *swapee = eina_inarray_nth(pd->entitycache, eina_inarray_count(pd->entitycache));
   engineer_scene_entity_data_swap(obj, target, swapee->id);
   eina_hash_del(pd->entitylookup, &target, NULL);
   eina_inarray_pop(pd->entitycache);
}

EOLIAN static void
_engineer_scene_entity_destroy(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target)
{
  engineer_scene_entity_status_set(obj, target, 1);
}

EOLIAN static void
_engineer_scene_entity_dispose(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target EINA_UNUSED)
{
}

EOLIAN Engineer_Scene_Entity *
_engineer_scene_entity_lookup(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint target)
{
   return eina_hash_find(pd->entitylookup, &target);
}

EOLIAN static void
_engineer_scene_entity_data_swap(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint targeta, uint targetb)
{
   Engineer_Scene_Entity *payloada, *payloadb, payloadbuffer;
   uint *targetalookup = eina_hash_find(pd->entitylookup, &targeta);
   uint *targetblookup = eina_hash_find(pd->entitylookup, &targetb);
   if (targetalookup == NULL || targetblookup == NULL) return;
   uint  lookupbuffer = *targetalookup;

   payloada = eina_inarray_nth(pd->entitycache, *targetalookup);
   payloadb = eina_inarray_nth(pd->entitycache, *targetblookup);
   payloadbuffer = *payloada;
   *payloada = *payloadb;
   *payloadb = payloadbuffer;

   eina_hash_modify(pd->entitylookup, &targeta, targetblookup);
   eina_hash_modify(pd->entitylookup, &targetb, &lookupbuffer);
}

EOLIAN static uint
_engineer_scene_entity_status_get(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target)
{
   Engineer_Scene_Entity *entity = engineer_scene_entity_lookup(obj, target);
   if (entity == NULL) return 0;
   return entity->status;
}

EOLIAN static void
_engineer_scene_entity_status_set(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target, char mode)
{
   if (mode < 4) // Make sure that our mode is either zero, one, two, or three.
   {
      Engineer_Scene_Entity *entity = engineer_scene_entity_lookup(obj, target);
      if (entity == NULL) return;
      entity->status = mode;
   }
}

EOLIAN static uint
_engineer_scene_entity_parent_get(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target)
{
   Engineer_Scene_Entity *entity = engineer_scene_entity_lookup(obj, target);
   if (entity == NULL) return UINT_NULL;
   return entity->parent;
}

EOLIAN static void
_engineer_scene_entity_parent_set(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target, uint parent)
{
   Engineer_Scene_Entity *entity = engineer_scene_entity_lookup(obj, target);
   if (entity == NULL) return;
   Engineer_Scene_Entity *entitynext = engineer_scene_entity_lookup(obj, entity->siblingnext);
   Engineer_Scene_Entity *entityprev = engineer_scene_entity_lookup(obj, entity->siblingprev);
   Engineer_Scene_Entity *oldparent = engineer_scene_entity_lookup(obj, entity->parent);
   Engineer_Scene_Entity *newparent = engineer_scene_entity_lookup(obj, parent);

   // Check to see if this Entity has it's relationship data defined.
   if (oldparent != NULL && entitynext != NULL && entityprev != NULL)
   {
      // Check to see if the target is the old parents first child.
      if (oldparent->firstentity == target)
      {
         oldparent->firstentity = entity->siblingnext;
      }

      // Check to see if the old parent has only one child.
      if (entitynext->siblingprev == target)
      {
         oldparent->firstentity = UINT_NULL;
      }
      else // relink the remaining child Entities.
      {
         entitynext->siblingprev = entity->siblingprev;
         entityprev->siblingnext = entity->siblingnext;
      }
   }

   entity->parent = parent; // Set the new parent EntityID for the target Entity.

   // Check to see if new parent has any children. If not, set up the first child properly.
   if (newparent->firstentity == UINT_NULL)
   {
      newparent->firstentity = target;
      entity->siblingnext = target;
      entity->siblingprev = target;
   }
   else // add the target Entity to the back end of the new parent's child list.
   {
      entitynext = engineer_scene_entity_lookup(obj, newparent->firstentity);
      entityprev = engineer_scene_entity_lookup(obj, entitynext->siblingprev);

      entity->siblingnext = entityprev->siblingnext;
      entity->siblingprev = entitynext->siblingprev;
      entitynext->siblingprev = target;
      entityprev->siblingnext = target;
   }
}

EOLIAN static void
_engineer_scene_entity_sibling_swap(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint siblinga, uint siblingb)
{
   Engineer_Scene_Entity *entitya = engineer_scene_entity_lookup(obj, siblinga);
   Engineer_Scene_Entity *entityb = engineer_scene_entity_lookup(obj, siblingb);
   if (entitya == NULL || entityb == NULL) return;

   if (entitya->parent == entityb->parent)
   {
      Engineer_Scene_Entity *parent  = engineer_scene_entity_lookup(obj, entitya->parent);

      if (siblinga == parent->firstentity)
      {
         parent->firstentity = siblingb;
      }
      if (siblingb == parent->firstentity)
      {
         parent->firstentity = siblinga;
      }

      Engineer_Scene_Entity *entityanext = engineer_scene_entity_lookup(obj, entitya->siblingnext);
      Engineer_Scene_Entity *entityaprev = engineer_scene_entity_lookup(obj, entitya->siblingprev);
      Engineer_Scene_Entity *entitybnext = engineer_scene_entity_lookup(obj, entityb->siblingnext);
      Engineer_Scene_Entity *entitybprev = engineer_scene_entity_lookup(obj, entityb->siblingprev);

      uint  buffernext         = entitya->siblingnext;
      uint  bufferprev         = entitya->siblingprev;
      uint  buffernextbacklink = entityanext->siblingprev;
      uint  bufferprevbacklink = entityaprev->siblingnext;

      entitya->siblingnext     = entityb->siblingnext;
      entitya->siblingprev     = entityb->siblingprev;
      entityanext->siblingprev = entitybnext->siblingprev;
      entityaprev->siblingnext = entitybprev->siblingnext;

      entityb->siblingnext     = buffernext;
      entityb->siblingprev     = bufferprev;
      entitybnext->siblingprev = buffernextbacklink;
      entitybprev->siblingnext = bufferprevbacklink;
   }
}

EOLIAN static Eina_Inarray *
_engineer_scene_entity_children_get(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        unsigned int target)
{
   Eina_Inarray          *results = eina_inarray_new(sizeof(unsigned int), 0);
   Engineer_Scene_Entity *first = engineer_scene_entity_lookup(obj, target);
   Engineer_Scene_Entity *current = engineer_scene_entity_lookup(obj, first->siblingnext);

   while (current != first)
   {
      eina_inarray_push(results, current);
      current = engineer_scene_entity_lookup(obj, current->siblingnext);
   }
   eina_inarray_push(results, current);

   return results;
}

EOLIAN static Eina_Inarray *
_engineer_scene_entity_components_get(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        unsigned int target)
{
   Eina_Inarray *results = eina_inarray_new(sizeof(unsigned int), 0);
   Engineer_Scene_Component *first = engineer_scene_component_lookup(obj, target);
   Engineer_Scene_Component *current = engineer_scene_component_lookup(obj, first->siblingnext);

   while (current != first)
   {
      eina_inarray_push(results, current);
      current = engineer_scene_component_lookup(obj, current->siblingnext);
   }
   eina_inarray_push(results, current);

   return results;
}

EOLIAN uint
_engineer_scene_entity_id_use(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
   if (eina_inarray_count(pd->entityqueue) == 0)
   {
      eina_inarray_push(pd->entityqueue, &pd->entitycount);
      pd->entitycount += 1;
   }
   uint *result = eina_inarray_pop(pd->entityqueue);

   return *result;
}

EOLIAN void
_engineer_scene_entity_id_free(Eo *obj, Engineer_Scene_Data *pd,
        uint target)
{
   engineer_scene_entity_status_set(obj, target, 0);
   eina_inarray_insert_at(pd->entityqueue, 0, &target);
}

/*** Component Methods ***/

EOLIAN static uint
_engineer_scene_component_create(Eo *obj, Engineer_Scene_Data *pd,
        uint parent, const char *name)
{
   Engineer_Scene_Component *component, blank;
   uint buffer;

   component = &blank;
   memset(component, 0, sizeof(Engineer_Scene_Component));

   component->name = eina_stringshare_printf("%s", name);
   component->id   = engineer_scene_component_id_use(obj);

   buffer    = eina_inarray_push(pd->componentcache, component);
   component = eina_inarray_nth(pd->componentcache, buffer);
   eina_hash_add(pd->componentlookup, &component->id, component);

   engineer_scene_component_parent_set(obj, component->id, parent);
/*
   // Create a database entry for the Component.
   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &component.id;
   key.size = sizeof(uint);
   data.data = &component;
   data.size = sizeof(component);

   pd->componenttable->put(pd->componenttable, NULL, &key, &data, 0);
*/
   printf("Component Create Checkpoint. CID: %d, Parent EID: %d, NextSib CID: %d, PrevSib CID: %d, Name: %s\n",
      component->id,
      component->parent,
      component->siblingprev,
      component->siblingnext,
      component->name);

   return component->id;
}

EOLIAN static void
_engineer_scene_component_load(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint target EINA_UNUSED)
{
   Engineer_Scene_Component *payload, payloaddata;
   payload = &payloaddata;
/*
   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &target;
   key.size = sizeof(uint);
   key.flags = DB_DBT_USERMEM;

   pd->componenttable->get(pd->componenttable, NULL, &key, &data, 0);
   payload = data.data;

   // If this component has an unloaded parent, return without doing anything.
   if (eina_hash_find(pd->componentlookup, &payload->parent) == NULL) return;
*/
   // Add the Component data entry to the Component cache and lookup table.
   uint cacheindex = eina_inarray_push(pd->componentcache, payload);
   eina_hash_add(pd->componentlookup, &payload->id, &cacheindex);
}

EOLIAN static void
_engineer_scene_component_save(Eo *obj, Engineer_Scene_Data *pd,
        uint target)
{
   Engineer_Scene_Component *payload = engineer_scene_component_lookup(obj, target);

   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &target;
   key.size = sizeof(uint);
   data.data = payload;
   data.size = sizeof(*payload);

   pd->componenttable->put(pd->componenttable, NULL, &key, &data, 0);

   // Remove the component data entry from the cache and lookup table.
   Engineer_Scene_Component *swapee;

   swapee = eina_inarray_nth(pd->componentcache, eina_inarray_count(pd->componentcache));
   engineer_scene_entity_data_swap(obj, target, swapee->id);
   eina_hash_del(pd->componentlookup, &target, NULL);
   eina_inarray_pop(pd->componentcache);
}

EOLIAN static void
_engineer_scene_component_destroy(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target)
{
   engineer_scene_component_status_set(obj, target, 1);
}

EOLIAN static void
_engineer_scene_component_dispose(Eo *obj, Engineer_Scene_Data *pd,
        uint target)
{
   // Remove the component data entry from the cache and lookup table.
   Engineer_Scene_Component *swapee;

   swapee = eina_inarray_nth(pd->componentcache, eina_inarray_count(pd->componentcache));
   engineer_scene_entity_data_swap(obj, target, swapee->id);
   eina_hash_del(pd->componentlookup, &target, NULL);
   eina_inarray_pop(pd->componentcache);
}

EOLIAN static Engineer_Scene_Component *
_engineer_scene_component_lookup(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint target)
{
   return eina_hash_find(pd->componentlookup, &target);
}

EOLIAN static void
_engineer_scene_component_data_swap(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint targeta, uint targetb)
{
   Engineer_Scene_Component *payloada, *payloadb, payloadbuffer;
   uint *targetalookup = eina_hash_find(pd->componentlookup, &targeta);
   uint *targetblookup = eina_hash_find(pd->componentlookup, &targetb);
   uint  lookupbuffer = *targetalookup;

   payloada = eina_inarray_nth(pd->componentcache, *targetalookup);
   payloadb = eina_inarray_nth(pd->componentcache, *targetblookup);
   payloadbuffer = *payloada;
   *payloada = *payloadb;
   *payloadb = payloadbuffer;

   eina_hash_modify(pd->componentlookup, &targeta, targetblookup);
   eina_hash_modify(pd->componentlookup, &targetb, &lookupbuffer);
}

EOLIAN static uint
_engineer_scene_component_status_get(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target)
{
   Engineer_Scene_Component *component = engineer_scene_component_lookup(obj, target);
   return component->status;
}

EOLIAN static void
_engineer_scene_component_status_set(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target, char mode)
{
   if (mode < 4) // Make sure that our mode is either zero, one, two, or three.
   {
      Engineer_Scene_Component *component = engineer_scene_component_lookup(obj, target);
      component->status = mode;
   }
}

EOLIAN static uint
_engineer_scene_component_parent_get(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target)
{
   Engineer_Scene_Component *component = engineer_scene_component_lookup(obj, target);
   return component->parent;
}

EOLIAN static void
_engineer_scene_component_parent_set(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target, uint parent)
{
   Engineer_Scene_Component *component     = engineer_scene_component_lookup(obj, target);
   if (component == NULL) return;
   Engineer_Scene_Component *componentnext = engineer_scene_component_lookup(obj, component->siblingnext);
   Engineer_Scene_Component *componentprev = engineer_scene_component_lookup(obj, component->siblingprev);
   Engineer_Scene_Entity    *oldparent     = engineer_scene_entity_lookup(obj, component->parent);
   Engineer_Scene_Entity    *newparent     = engineer_scene_entity_lookup(obj, parent);

   if (newparent == NULL) printf("ERROR: newparent == NULL!\n");

   if (oldparent != NULL && componentnext != NULL && componentprev != NULL)
   {
      // Check to see if the target is the old parents first child.
      if (oldparent->firstcomponent == target)
      {
         oldparent->firstcomponent = component->siblingnext;
      }

      // Check to see if the old parent has only one child.
      if (componentnext->siblingprev == target)
      {
         oldparent->firstcomponent = UINT_NULL;
      }
      else // relink the remaining child Entities.
      {
         componentnext->siblingprev = component->siblingprev;
         componentprev->siblingnext = component->siblingnext;
      }
   }

   component->parent = parent; // Set the new parent ComponentID for the target Entity.

   // Check to see if new parent has any children. If not, set up the first child properly.
   if (newparent->firstcomponent == UINT_NULL)
   {
      newparent->firstcomponent = target;
      component->siblingnext = target;
      component->siblingprev = target;
   }
   else // add the target Component to the back end of the new parent's child list.
   {

      componentnext = engineer_scene_component_lookup(obj, newparent->firstcomponent);
      componentprev = engineer_scene_component_lookup(obj, componentnext->siblingprev);

      component->siblingnext = componentprev->siblingnext;
      component->siblingprev = componentnext->siblingprev;
      componentnext->siblingprev = target;
      componentprev->siblingnext = target;
   }
}

EOLIAN static void
_engineer_scene_component_sibling_swap(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint siblinga, uint siblingb)
{
   Engineer_Scene_Component *componenta = engineer_scene_component_lookup(obj, siblinga);
   Engineer_Scene_Component *componentb = engineer_scene_component_lookup(obj, siblingb);

   if (componenta->parent == componentb->parent)
   {
      Engineer_Scene_Entity *parent  = engineer_scene_entity_lookup(obj, componenta->parent);

      if (siblinga == parent->firstcomponent)
      {
         parent->firstcomponent = siblingb;
      }
      if (siblingb == parent->firstcomponent)
      {
         parent->firstcomponent = siblinga;
      }

      Engineer_Scene_Component *componentanext, *componentaprev, *componentbnext, *componentbprev;

      componentanext = engineer_scene_component_lookup(obj, componenta->siblingnext);
      componentaprev = engineer_scene_component_lookup(obj, componenta->siblingprev);
      componentbnext = engineer_scene_component_lookup(obj, componentb->siblingnext);
      componentbprev = engineer_scene_component_lookup(obj, componentb->siblingprev);

      uint  buffernext            = componenta->siblingnext;
      uint  bufferprev            = componenta->siblingprev;
      uint  buffernextbacklink    = componentanext->siblingprev;
      uint  bufferprevbacklink    = componentaprev->siblingnext;

      componenta->siblingnext     = componentb->siblingnext;
      componenta->siblingprev     = componentb->siblingprev;
      componentanext->siblingprev = componentbnext->siblingprev;
      componentaprev->siblingnext = componentbprev->siblingnext;

      componentb->siblingnext     = buffernext;
      componentb->siblingprev     = bufferprev;
      componentbnext->siblingprev = buffernextbacklink;
      componentbprev->siblingnext = bufferprevbacklink;
   }
}

EOLIAN static uint
_engineer_scene_component_id_use(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
   if (eina_inarray_count(pd->componentqueue) == 0)
   {
      eina_inarray_insert_at(pd->componentqueue, 0, &pd->componentcount);
      pd->componentcount += 1;
   }
   uint *newid = eina_inarray_pop(pd->componentqueue);
   return *newid;
}

EOLIAN static void
_engineer_scene_component_id_free(Eo *obj, Engineer_Scene_Data *pd,
        uint target)
{
   engineer_scene_component_status_set(obj, target, 0);
   eina_inarray_insert_at(pd->componentqueue, 0, &target);
}

/*** Sector Callbacks ***/

EOLIAN static Eina_Bool
_engineer_scene_sector_iterate_cb(void *data)
{
   // Store the timestamp for when this Sector's clock tick begins.
   float time = ecore_time_get();

   Engineer_Scene_Sector *sector = data;
   Engineer_Scene_Data   *scene = sector->scene;
   Engineer_Game_Module  *module;
   Eo *(*module_update)(Eo *obj);
   uint *target, count = eina_inarray_count(scene->modulecache);
   for (uint index = 0; index < count; index++)
   {
      module = eina_inarray_nth(scene->modulecache, index);
      module_update = module->update;
      target = eina_hash_find(sector->lookup, &module->id);
      module_update(eina_inarray_nth(sector->cache, *target));
   }

   time -= ecore_time_get();

   // Check to see if we are taking more than 85% of our tick time, if so, decrease the clock rate.
   if (sector->rate != 1 && time > 1/sector->rate * 0.85)
   {
      sector->rate--;
      ecore_timer_interval_set(sector->clock, 1/sector->rate);
   }
   // If TiDi is engaged, but the tick time load is less than 70%, if so, increase the clock rate.
   else if (sector->rate != 32 && time < 1/sector->rate * 0.70)
   {
      sector->rate++;
      ecore_timer_interval_set(sector->clock, 1/sector->rate);
   }

   return ECORE_CALLBACK_RENEW;
}

/*** Sector Methods ***/

EOLIAN static uint
_engineer_scene_sector_create(Eo *obj, Engineer_Scene_Data *pd,
        uint parent)
{
   Engineer_Scene_Sector *sector, sectordata;
   uint buffer;

   sector = &sectordata;
   memset(sector, 0, sizeof(Engineer_Scene_Sector));

   // Set up our Sector's shell Component, and get it's ID.
   uint componentid = engineer_scene_component_create(obj, parent, "Sector Component"); //component.type = 0;

   // Add a new data entry for our new Sector to the *sectorcache and set up it's *sectorlookup.
   buffer = eina_inarray_push(pd->sectorcache, sector);
   sector = eina_inarray_nth(pd->sectorcache, buffer);
   eina_hash_add(pd->sectorlookup, &componentid, sector);

   // Include a pointer to the parent Scene's private data, we will need it during iteration.
   sector->scene = pd;

   // Pointer to the component metadata.
   sector->component = engineer_scene_component_lookup(obj, componentid);

   // Create and fill our sector->module array with a new module cache for each loaded module.
   sector->cache = NULL;
   Eo *(*module_new)(Eo *obj);
   Engineer_Game_Module *module;
   Efl_Object *cache;
   uint count = eina_inarray_count(pd->modulecache);
   if (count != 0)
   {
      // fixme
      for (uint current = 1; current <= count; current++) //for (uint current = 0; current < count; current++)
      {
         module = eina_inarray_nth(pd->modulecache, current);
         module_new = module->new;
         cache = module_new(obj);
         buffer = eina_inarray_push(sector->cache, cache);
         eina_hash_add(sector->lookup, &module->id, &buffer);
      }
   }

   // Set up Sector data defaults.
   sector->rate = 32;
   sector->size = 63;

   // Create and pause our Sector's iteration clock on frame 0.
   sector->clock = ecore_timer_add(1/sector->rate, _engineer_scene_sector_iterate_cb, sector);
   ecore_timer_freeze(sector->clock);
/*
   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &componentid;
   key.size = sizeof(uint);
   data.data = &payload;
   data.ulen = sizeof(payload);
   data.flags = DB_DBT_USERMEM;
   pd->sectortable->put(pd->sectortable, NULL, &key, &data, 0);
*/
   return componentid;
}

EOLIAN static void
_engineer_scene_sector_load(Eo *obj, Engineer_Scene_Data *pd,
        uint target)
{
   // Attempt to fetch the sector component from the relevant database file.
   Engineer_Scene_Sector_Entry *entry;
   Engineer_Scene_Sector        payload;
/*
   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &target;
   key.size = sizeof(uint);
   //data.data = entry;
   data.ulen = sizeof(*entry);
   data.flags = DB_DBT_USERMEM;
   pd->sectortable->get(pd->sectortable, NULL, &key, &data, 0);

   // Check to see if the target data was returned, if so, set our sector data from it.
   entry = data.data;
   if (entry == NULL) return;
*/
   // Include a pointer to the parent Scene's private data, we will need it during iteration.
   payload.scene = pd;

   // Load the sector component metadata and link to it.
   engineer_scene_component_load(obj, target);
   payload.component = engineer_scene_component_lookup(obj, target);

   // Create and fill our sector.module array with a new module cache for each loaded module.
   payload.cache = NULL;
   Eo *(*module_new)(Eo  *obj);
   Engineer_Game_Module  *module;
   Efl_Object            *cache;
   uint index, count = eina_inarray_count(pd->modulecache);
   for (uint current = 0; current < count; current++)
   {
      module = eina_inarray_nth(pd->modulecache, current);
      module_new = module->new;
      cache = module_new(obj);
      index = eina_inarray_push(payload.cache, cache);
      eina_hash_add(payload.lookup, &module->id, &index);
   }

   // Create and pause our Sector's iteration clock.
   ecore_timer_add(1/payload.rate, _engineer_scene_sector_iterate_cb, &payload.clock);
   ecore_timer_freeze(payload.clock);

   // Load our persistent data from the DB.
   payload.rate = entry->rate;
   payload.size = entry->size;

   // Add a new data entry for our loaded Sector to the *sectorcache and set up it's *sectorlookup.
   index = eina_inarray_push(pd->sectorcache, &payload);
   eina_hash_add(pd->sectorlookup, &target, &index);
}

EOLIAN static void
_engineer_scene_sector_save(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint target)
{
   engineer_scene_component_save(obj, target);

   Engineer_Scene_Sector *payload = engineer_scene_sector_lookup(obj, target);
   if (payload == NULL) return;

   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &target;
   key.size = sizeof(uint);
   data.data = payload;
   data.size = sizeof(*payload);

   pd->sectortable->put(pd->sectortable, NULL, &key, &data, 0);
   pd->sectortable->sync(pd->sectortable, 0);
}

EOLIAN static void
_engineer_scene_sector_unload(Eo *obj, Engineer_Scene_Data *pd,
        uint target)
{
   engineer_scene_sector_save(obj, target); // Should really be engineer_scene_component_unload

   // Remove the sector data entry from the cache and lookup table.
   Engineer_Scene_Sector *swapee = eina_inarray_nth(pd->sectorcache, eina_inarray_count(pd->sectorcache));
   engineer_scene_sector_data_swap(obj, target, swapee->component->id);
   eina_hash_del(pd->sectorlookup, &target, NULL);
   eina_inarray_pop(pd->sectorcache);
}

EOLIAN static void
_engineer_scene_sector_destroy(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target)
{
   engineer_scene_component_status_set(obj, target, 1);
}

EOLIAN static void
_engineer_scene_sector_dispose(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target EINA_UNUSED)
{
}

EOLIAN static Engineer_Scene_Sector *
_engineer_scene_sector_lookup(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint target)
{
   return eina_hash_find(pd->sectorlookup, &target);
}

EOLIAN static void
_engineer_scene_sector_data_swap(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint targeta, uint targetb)
{
   Engineer_Scene_Sector *payloada, *payloadb, payloadbuffer;
   uint *targetalookup = eina_hash_find(pd->entitylookup, &targeta);
   uint *targetblookup = eina_hash_find(pd->entitylookup, &targetb);
   if (targetalookup == NULL || targetblookup == NULL) return;
   uint  lookupbuffer = *targetalookup;

   payloada = eina_inarray_nth(pd->entitycache, *targetalookup);
   payloadb = eina_inarray_nth(pd->entitycache, *targetblookup);
   payloadbuffer = *payloada;
   *payloada = *payloadb;
   *payloadb = payloadbuffer;

   eina_hash_modify(pd->entitylookup, &targeta, targetblookup);
   eina_hash_modify(pd->entitylookup, &targetb, &lookupbuffer);
}

#include "engineer_scene.eo.c"
