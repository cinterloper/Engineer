#include "engineer_scene.h"

// eolian_gen `pkg-config --variable=eolian_flags ecore eo evas efl` -I . -g h engineer_scene.eo
// eolian_gen `pkg-config --variable=eolian_flags ecore eo evas efl` -I . -g c engineer_scene.eo

EOLIAN Eo *
engineer_scene_add(Eo *parent, const char *name)
{
   Eo *scene = efl_add(ENGINEER_SCENE_CLASS, parent,
      engineer_scene_name_set(efl_added, name));

   return scene;
}

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
   Eo *node = efl_super(obj, ENGINEER_SCENE_CLASS);
   obj = efl_finalize(node);
   pd->node = node;

   // The Scene size is in units of (2^x)/(2^16) meters where x is the setting. Max: bitwidth--.
   pd->size = 63;

   // Set up the Scene iterator defaults.
   pd->clockrate = 32;
   pd->retention = 3;
   pd->current   = 0;

   // Create and initialize the minimum space (3 frames) needed to start our timeline.
   pd->timeline = eina_inarray_new(sizeof(Engineer_Scene_Frame), 0);
   engineer_scene_timeline_push(obj);
   engineer_scene_timeline_push(obj);
   engineer_scene_timeline_push(obj);

   uint count = eina_inarray_count(pd->timeline);

   printf("Scene Finalize Checkpoint 1. Number of Frames: %d\n", count);

   // We need to set up our timeline pointers for the first time here.
   // Note that past and present point to the same dataset for the initial frame to prevent
   //    interpolation bugs and saves us from having to duplicate the initial dataset.
   pd->past    = eina_inarray_nth(pd->timeline, 1);
   pd->present = eina_inarray_nth(pd->timeline, 1);
   pd->future  = eina_inarray_nth(pd->timeline, 0);

   printf("Scene Finalize Checkpoint 2.\n");

   // Create the in-memory data cache.
   pd->datacache = eina_hash_pointer_new(eng_free_cb);

   printf("Scene Finalize Checkpoint 3.\n");

   // Create and fill our pd->scenecache array with a new Eo instance for each registered module.
   count = eina_hash_population(pd->datacache); // Needs to be the node module cache.
   if (count != 0)
   {
      Engineer_Node_Module *module;
      Eo *(*module_factory)(Eo *obj);
      uint current;

      for (current = 0; current < count; current++)
      {
         module = eina_hash_find(pd->datacache, &current);
         module_factory = module->factory;
         eina_hash_add(pd->datacache, &module->id, module_factory(obj));
      }
   }

   printf("Scene Finalize Checkpoint 4.\n");

   // Enqueue the creation of our scene iteration clock to run in the threadpool.
   ecore_thread_run(
      _engineer_scene_iterate_init_task,
      _engineer_scene_iterate_init_done,
      _engineer_scene_iterate_init_cancel,
      obj);

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
   printf("Scene Finalize Checkpoint 5.\n");

   // If our Scene is new, create a root Entity and set it up.
   if (pd->entitycount == 0)
   {
      Engineer_Scene_Entity *root, blank;
      uint buffer;

      root = &blank;
      memset(root, 0, sizeof(Engineer_Scene_Entity));

      root->name = eina_stringshare_add("Scene Root");
      printf("before\n");
      root->id   = engineer_node_entity_id_use(obj);
      printf("after\n");

      buffer = eina_inarray_push(pd->present->entitycache, root);
      root   = eina_inarray_nth(pd->present->entitycache, buffer);
      eina_hash_add(pd->present->entitylookup, &root->id, root);

      //root->status         = 3; // Fixme: needs to refer to node data.
      //root->referencecount = 1; // This one too.

      root->parent         = 0;
      root->siblingnext    = 0;
      root->siblingprev    = 0;
      root->firstcomponent = UINT_NULL;
      root->firstentity    = UINT_NULL;

      printf("Root Entity Create Checkpoint. EID: %d\n", root->id);
   }

   printf("Scene Finalize Checkpoint 6.\n");

   return obj;
}

EOLIAN static void
_engineer_scene_efl_object_destructor(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
   // For each loaded entity and it's components, flush all data in cache to DB.
   if (pd->componenttable != NULL) pd->componenttable->close(pd->componenttable, 0);
   if (pd->entitytable    != NULL) pd->entitytable->close(pd->entitytable, 0);
}

/*** Scene Efl Object property getter/setters. ***/

EOLIAN static const char *
_engineer_scene_name_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
  return pd->name;
}

EOLIAN static void
_engineer_scene_name_set(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd, const char *name)
{
   pd->name = eina_stringshare_add(name);
}

/*** Iteration Methods. These are what make everything happen. ***/

static void
_engineer_scene_iterate_init_task(void *data, Ecore_Thread *thread EINA_UNUSED)
{
   printf("Engineer Scene Iterate Init Checkpoint.\n");

   Eo *obj = data;
   Engineer_Scene_Data *pd = efl_data_scope_get(obj, ENGINEER_SCENE_CLASS);

   // Create and pause our Sector's iteration clock on Frame 0.
   pd->iterator = ecore_timer_add(1/pd->clockrate, _engineer_scene_iterate_cb, obj);
   ecore_timer_freeze(pd->iterator);
}

static void
_engineer_scene_iterate_init_done(void *data EINA_UNUSED, Ecore_Thread *thread EINA_UNUSED)
{
   printf("Engineer Scene Iterate Init Done Checkpoint.\n");
}

static void
_engineer_scene_iterate_init_cancel(void *data EINA_UNUSED, Ecore_Thread *thread EINA_UNUSED)
{
   printf("Engineer Scene Iterate Init Cancel Checkpoint.\n");
}

EOLIAN static Eina_Bool
_engineer_scene_iterate(Eo *obj, Engineer_Scene_Data *pd)
{
   uint  count;
   float timestamp;

   // Store the timestamp for when this Sector's clock tick begins.
   timestamp = ecore_time_get();

   printf("Scene Iterate Checkpoint 1.\n");

   // Check to see if our timeline Frame count is currently equal to our retention value.
   //    If not, modify the size of the timeline by one Frame in the correct direction.
   count = eina_inarray_count(pd->timeline);
   if (count != pd->retention) engineer_scene_timeline_adjust(obj);

   printf("Scene Iterate Checkpoint 2.\n");

   // Cycle the timeline to get to our next frame. This also resets our pointers in case they
   //    were nuked by an eina_inarray_push.
   pd->future  = eina_inarray_nth(pd->timeline, (pd->future->index-1 + count) % count);
   pd->present = eina_inarray_nth(pd->timeline,  pd->future->index++ % count);
   pd->past    = eina_inarray_nth(pd->timeline,  pd->future->index+2 % count);

   printf("Scene Iterate Checkpoint 3.\n");

   // Wipe clean the allocated space reserved for our next Frame's Entity and Component metadata.
   eina_hash_free_buckets(pd->future->entitylookup);
   eina_hash_free_buckets(pd->future->componentlookup);

   // Clear all payload data for the future frame.
   eina_inarray_flush(pd->future->entitycache);
   eina_inarray_flush(pd->future->componentcache);

   // Copy over our present Scenegraph metadata to the next Frame.
   eina_hash_foreach(pd->present->entitylookup,    _engineer_scene_iterate_entity_cb,    obj);
   eina_hash_foreach(pd->present->componentlookup, _engineer_scene_iterate_component_cb, obj);

   // Iterate thru each module's component code active in the scene.
   eina_hash_foreach(pd->datacache, _engineer_scene_iterate_module_cb, obj);

   timestamp -= ecore_time_get();

   // Check to see if we are taking more than 85% of our tick time, if so, decrease the clock rate.
   if (pd->clockrate != 1 && timestamp > 1/pd->clockrate * 0.85)
   {
      pd->clockrate--;
      ecore_timer_interval_set(pd->iterator, 1/pd->clockrate);
   }
   // If TiDi is engaged, but the tick time load is less than 70%, if so, increase the clock rate.
   else if (pd->clockrate != 32 && timestamp < 1/pd->clockrate * 0.70)
   {
      pd->clockrate++;
      ecore_timer_interval_set(pd->iterator, 1/pd->clockrate);
   }

   return ECORE_CALLBACK_RENEW;
}

EOLIAN static Eina_Bool
_engineer_scene_iterate_cb(void *data)
{
   return engineer_scene_iterate(data);
}

EOLIAN static Eina_Bool
_engineer_scene_iterate_module(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint *key)
{
   Engineer_Node_Module *module;
   Eo *(*module_update)(Eo *obj);

   // Get the correct update() function pointer and invoke it targeting the right datacache member.
   module = engineer_node_module_lookup(pd->node, *key);
   module_update = module->update;
   module_update(eina_hash_find(pd->datacache, key));

   return 1;
}

EOLIAN static Eina_Bool
_engineer_scene_iterate_module_cb(const Eina_Hash *hash EINA_UNUSED, const void *key,
        void *data EINA_UNUSED, void *fdata)
{
   return engineer_scene_iterate_module(fdata, (uint*)key);
}

EOLIAN static Eina_Bool
_engineer_scene_iterate_entity(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        void *key, void *data)
{
   Engineer_Scene_Entity *buffer;
   uint                   index = *(uint*)data;

   // Copy over our Entity lookup data into the new Frame's Entity hashtable.
   eina_hash_add(pd->future->entitylookup, key, data);

   // Copy the associated cache data for this Entity into the next Frame.
   buffer = eina_inarray_nth(pd->present->entitycache, index);
   eina_inarray_replace_at(pd->future->entitycache, index, buffer);

   return EINA_TRUE;
}

EOLIAN static Eina_Bool
_engineer_scene_iterate_entity_cb(const Eina_Hash *hash EINA_UNUSED, const void *key,
        void *data, void *fdata)
{
   return engineer_scene_iterate_entity(fdata, (void*)key, data);
}

EOLIAN static Eina_Bool
_engineer_scene_iterate_component(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        void *key, void *data)
{
   Engineer_Scene_Component *buffer;
   uint                      index = *(uint*)data;

   // Copy over our Component lookup data into the new Frame's Component hashtable.
   eina_hash_add(pd->future->componentlookup, key, data);

   // Copy the associated cache data for this Component into the next Frame.
   buffer = eina_inarray_nth(pd->present->componentcache, index);
   eina_inarray_replace_at(pd->future->componentcache, index, buffer);

   return EINA_TRUE;
}

EOLIAN static Eina_Bool
_engineer_scene_iterate_component_cb(const Eina_Hash *hash EINA_UNUSED, const void *key,
        void *data, void *fdata)
{
   return engineer_scene_iterate_component(fdata, (void*)key, data);
}

/*** Timeline Methods ***/

EOLIAN static void
_engineer_scene_timeline_adjust(Eo *obj, Engineer_Scene_Data *pd)
{
   // Before we start, we need to know what our present timeline index is, and how large it is.
   uint count = eina_inarray_count(pd->timeline);
   uint index = pd->present->index;

   // If the count is more than our retention value and our future Frame pointer is pointing
   //    at the end of the pd->timeline inarray.
   if ((pd->retention > count) &&
      (index++ == count))
   {
      engineer_scene_timeline_push(obj);
      count += 1;
   }

   // If it is less than our retention value, and we are in the correct timeline window.
   if ((pd->retention < count) &&
      (index++ <= pd->retention) &&
      (index-- >= count - pd->retention))
   {
      engineer_scene_timeline_pop(obj);
      count -= 1;
   }
}

EOLIAN static void
_engineer_scene_timeline_push(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
   uint index;
   Engineer_Scene_Frame *frame, blank;

   // Allocate the main memory space needed to store the Frame and zero it out.
   memset(&blank, 0, sizeof(Engineer_Scene_Frame));
   index = eina_inarray_push(pd->timeline, &blank);
   frame = eina_inarray_nth(pd->timeline, index);

   // Set up the Frame's interior data structures.
   frame->index           = index;
   frame->timestamp       = 0;

   frame->entitycache     = eina_inarray_new(sizeof(Engineer_Scene_Entity), 0);
   frame->entitylookup    = eina_hash_int32_new(eng_free_cb);

   frame->componentcache  = eina_inarray_new(sizeof(Engineer_Scene_Component), 0);
   frame->componentlookup = eina_hash_int32_new(eng_free_cb);
}

EOLIAN static void
_engineer_scene_timeline_pop(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
   Engineer_Scene_Frame *frame, blank;

   // Deallocate the main memory space occupide by the old Frame.
   frame = eina_inarray_pop(pd->timeline);
   blank = *frame;
   frame = &blank;

   // Now free it's contents.
   eina_inarray_free(frame->componentcache);
   eina_hash_free(frame->componentlookup);

   eina_inarray_free(frame->entitycache);
   eina_hash_free(frame->entitylookup);
}

/*** Entity Methods ***/

EOLIAN static uint
_engineer_scene_entity_create(Eo *obj, Engineer_Scene_Data *pd,
        uint parent, const char *name)
{
   uint buffer;
   Engineer_Scene_Entity *entity, blank;
   entity = &blank;
   memset(entity, 0, sizeof(Engineer_Scene_Entity));

   entity->name = eina_stringshare_printf("%s", name);
   entity->id   = engineer_node_entity_id_use(pd->node);

   buffer = eina_inarray_push(pd->future->entitycache, entity);
   entity = eina_inarray_nth(pd->future->entitycache, buffer);
   eina_hash_add(pd->future->entitylookup, &entity->id, entity);

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
   printf("Entity Create Checkpoint. \
      EID: %d, Parent EID: %d, NextSib EID: %d, PrevSib EID: %d, Name: %s\n",
      entity->id, entity->parent, entity->siblingprev, entity->siblingnext, entity->name);

   return entity->id;
}

EOLIAN static void
_engineer_scene_entity_load(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target EINA_UNUSED)
{
/*
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
*/
}

EOLIAN static void
_engineer_scene_entity_save(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target EINA_UNUSED)
{
/*
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
*/
}

EOLIAN static void
_engineer_scene_entity_destroy(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint target)
{
  engineer_node_entity_status_set(pd->node, target, 1);
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
   return eina_hash_find(pd->present->entitylookup, &target);
}

EOLIAN static void
_engineer_scene_entity_data_swap(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint targeta, uint targetb)
{
   Engineer_Scene_Entity *payloada, *payloadb, payloadbuffer;
   uint *targetalookup = eina_hash_find(pd->future->entitylookup, &targeta);
   uint *targetblookup = eina_hash_find(pd->future->entitylookup, &targetb);
   if (targetalookup == NULL || targetblookup == NULL) return;
   uint  lookupbuffer = *targetalookup;

   payloada = eina_inarray_nth(pd->future->entitycache, *targetalookup);
   payloadb = eina_inarray_nth(pd->future->entitycache, *targetblookup);
   payloadbuffer = *payloada;
   *payloada = *payloadb;
   *payloadb = payloadbuffer;

   eina_hash_modify(pd->future->entitylookup, &targeta, targetblookup);
   eina_hash_modify(pd->future->entitylookup, &targetb, &lookupbuffer);
}

EOLIAN static uint
_engineer_scene_entity_parent_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint target)
{
   Engineer_Scene_Entity *entity =  eina_hash_find(pd->present->entitylookup, &target);
   if (entity == NULL) return UINT_NULL;
   return entity->parent;
}

EOLIAN static void
_engineer_scene_entity_parent_set(Eo *obj, Engineer_Scene_Data *pd,
        uint target, uint parent)
{
   Engineer_Scene_Entity *entity = engineer_scene_entity_lookup(obj, target);
   if (entity == NULL) return;
   Engineer_Scene_Entity *entitynext = eina_hash_find(pd->future->entitylookup, &entity->siblingnext); // engineer_scene_entity_lookup(obj, entity->siblingnext);
   Engineer_Scene_Entity *entityprev = eina_hash_find(pd->future->entitylookup, &entity->siblingprev); // engineer_scene_entity_lookup(obj, entity->siblingprev);
   Engineer_Scene_Entity *oldparent  = eina_hash_find(pd->future->entitylookup, &entity->parent);      // engineer_scene_entity_lookup(obj, entity->parent);
   Engineer_Scene_Entity *newparent  = eina_hash_find(pd->future->entitylookup, &parent);              // engineer_scene_entity_lookup(obj, parent);

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
      entitynext = eina_hash_find(pd->future->entitylookup, &newparent->firstentity);  // engineer_scene_entity_lookup(obj, newparent->firstentity);
      entityprev = eina_hash_find(pd->future->entitylookup, &entitynext->siblingprev); // engineer_scene_entity_lookup(obj, entitynext->siblingprev);

      entity->siblingnext = entityprev->siblingnext;
      entity->siblingprev = entitynext->siblingprev;
      entitynext->siblingprev = target;
      entityprev->siblingnext = target;
   }
}

EOLIAN static void
_engineer_scene_entity_sibling_swap(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint siblinga, uint siblingb)
{
   Engineer_Scene_Entity *entitya = eina_hash_find(pd->future->entitylookup, &siblinga); // engineer_scene_entity_lookup(obj, siblinga);
   Engineer_Scene_Entity *entityb = eina_hash_find(pd->future->entitylookup, &siblingb); // engineer_scene_entity_lookup(obj, siblingb);
   if (entitya == NULL || entityb == NULL) return;

   if (entitya->parent == entityb->parent)
   {
      Engineer_Scene_Entity *parent = eina_hash_find(pd->future->entitylookup, &entitya->parent); // engineer_scene_entity_lookup(obj, entitya->parent);

      if (siblinga == parent->firstentity)
      {
         parent->firstentity = siblingb;
      }
      if (siblingb == parent->firstentity)
      {
         parent->firstentity = siblinga;
      }

      Engineer_Scene_Entity *entityanext = eina_hash_find(pd->future->entitylookup, &entitya->siblingnext); // engineer_scene_entity_lookup(obj, entitya->siblingnext);
      Engineer_Scene_Entity *entityaprev = eina_hash_find(pd->future->entitylookup, &entitya->siblingprev); // engineer_scene_entity_lookup(obj, entitya->siblingprev);
      Engineer_Scene_Entity *entitybnext = eina_hash_find(pd->future->entitylookup, &entityb->siblingnext); // engineer_scene_entity_lookup(obj, entityb->siblingnext);
      Engineer_Scene_Entity *entitybprev = eina_hash_find(pd->future->entitylookup, &entityb->siblingprev); // engineer_scene_entity_lookup(obj, entityb->siblingprev);

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
_engineer_scene_entity_children_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        unsigned int target)
{
   Eina_Inarray          *results = eina_inarray_new(sizeof(unsigned int), 0);
   Engineer_Scene_Entity *first   = eina_hash_find(pd->present->entitylookup, &target);             // engineer_scene_entity_lookup(obj, target);
   Engineer_Scene_Entity *current = eina_hash_find(pd->present->entitylookup, &first->siblingnext); // engineer_scene_entity_lookup(obj, first->siblingnext);

   while (current != first)
   {
      eina_inarray_push(results, current);
      current = eina_hash_find(pd->present->entitylookup, &current->siblingnext); // engineer_scene_entity_lookup(obj, current->siblingnext);
   }
   eina_inarray_push(results, current);

   return results;
}

EOLIAN static Eina_Inarray *
_engineer_scene_entity_components_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        unsigned int target)
{
   Eina_Inarray *results = eina_inarray_new(sizeof(unsigned int), 0);
   Engineer_Scene_Component *first   = eina_hash_find(pd->present->entitylookup, &target);             // engineer_scene_component_lookup(obj, target);
   Engineer_Scene_Component *current = eina_hash_find(pd->present->entitylookup, &first->siblingnext); // engineer_scene_component_lookup(obj, first->siblingnext);

   while (current != first)
   {
      eina_inarray_push(results, current);
      current = eina_hash_find(pd->present->entitylookup, &current->siblingnext); // engineer_scene_component_lookup(obj, current->siblingnext);
   }
   eina_inarray_push(results, current);

   return results;
}

/*** Component Methods ***/

EOLIAN static uint
_engineer_scene_component_create(Eo *obj, Engineer_Scene_Data *pd,
        Eina_Stringshare *type, uint parent)
{
   uint buffer;
   Engineer_Scene_Component *component, blank;
   component = &blank;
   memset(component, 0, sizeof(Engineer_Scene_Component));

   // Register this Component's identifying information.
   component->name = eina_stringshare_printf("%s", type);
   component->id   = engineer_node_component_id_use(pd->node);

   // Set up our Component cache data and lookup reference.
   buffer    = eina_inarray_push(pd->future->componentcache, component);
   component = eina_inarray_nth(pd->future->componentcache, buffer);
   eina_hash_add(pd->future->componentlookup, &component->id, component);

   // Order the relevant module to create an appropriate Component data payload in it's cache.
   Engineer_Node_Module *module = engineer_node_module_lookup_by_type(pd->node, type);
   Eo *cache = eina_hash_find(pd->datacache, &module->id);
   Eo *(*module_component_create)(Eo*, uint);
   module_component_create = module->create;
   module_component_create(cache, component->id);

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
_engineer_scene_component_load(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target EINA_UNUSED)
{
/*
   Engineer_Scene_Component *payload, payloaddata;
   payload = &payloaddata;

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

   // We need to call engineer_module_component_load() on each of this Entities' component data,
   // in this Entities' Sector cache.
   Eo *(*component_load)(Eo *obj, uint target);
   Engineer_Scene_Sector *sector = engineer_scene_sector_lookup(obj, payload->sector); // Fixme Type is deprecated.
   Engineer_Game_Module  *module;
   uint index, count = eina_inarray_count(pd->modulecache);
   for (uint current = 0; current < count; current++)
   {
      module = eina_inarray_nth(pd->modulecache, current);
      component_load = module->load;
      index = *(uint*)eina_hash_find(sector->lookup, &current);
      component_load(eina_inarray_nth(sector->cache, index), target);
   }

   // Add the Component data entry to the Component cache and lookup table.
   uint cacheindex = eina_inarray_push(pd->componentcache, payload);
   eina_hash_add(pd->componentlookup, &payload->id, &cacheindex);
*/
}

EOLIAN static void
_engineer_scene_component_save(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target EINA_UNUSED)
{
   /*
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
   */
}

EOLIAN static void
_engineer_scene_component_destroy(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint target)
{
   engineer_node_component_status_set(pd->node, target, 1);
}

EOLIAN static void
_engineer_scene_component_dispose(Eo *obj, Engineer_Scene_Data *pd,
        uint target)
{
   // Remove the component data entry from the cache and lookup table.
   Engineer_Scene_Component *swapee;
   uint count;

   count = eina_inarray_count(pd->future->componentcache);
   swapee = eina_inarray_nth(pd->future->componentcache, count);
   engineer_scene_entity_data_swap(obj, target, swapee->id);
   eina_hash_del(pd->future->componentlookup, &target, NULL);
   eina_inarray_pop(pd->future->componentcache);
}

EOLIAN static Engineer_Scene_Component *
_engineer_scene_component_lookup(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint target)
{
   return eina_hash_find(pd->present->componentlookup, &target);
}

EOLIAN static void
_engineer_scene_component_data_swap(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint targeta, uint targetb)
{
   Engineer_Scene_Component *payloada, *payloadb, payloadbuffer;
   uint *targetalookup = eina_hash_find(pd->future->componentlookup, &targeta);
   uint *targetblookup = eina_hash_find(pd->future->componentlookup, &targetb);
   uint  lookupbuffer = *targetalookup;

   payloada = eina_inarray_nth(pd->future->componentcache, *targetalookup);
   payloadb = eina_inarray_nth(pd->future->componentcache, *targetblookup);
   payloadbuffer = *payloada;
   *payloada = *payloadb;
   *payloadb = payloadbuffer;

   eina_hash_modify(pd->future->componentlookup, &targeta, targetblookup);
   eina_hash_modify(pd->future->componentlookup, &targetb, &lookupbuffer);
}

EOLIAN static uint
_engineer_scene_component_parent_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint target)
{
   Engineer_Scene_Component *component = eina_hash_find(pd->present->componentlookup, &target); // engineer_scene_component_lookup(obj, target);
   return component->parent;
}

EOLIAN static void
_engineer_scene_component_parent_set(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint target, uint parent)
{
   Engineer_Scene_Component *component     = eina_hash_find(pd->future->componentlookup, &target); // engineer_scene_component_lookup(obj, target);
   if (component == NULL) return;
   Engineer_Scene_Component *componentnext = eina_hash_find(pd->future->componentlookup, &component->siblingnext); // engineer_scene_component_lookup(obj, component->siblingnext);
   Engineer_Scene_Component *componentprev = eina_hash_find(pd->future->componentlookup, &component->siblingprev); // engineer_scene_component_lookup(obj, component->siblingprev);
   Engineer_Scene_Entity    *oldparent     = eina_hash_find(pd->future->entitylookup, &component->parent); // engineer_scene_entity_lookup(obj, component->parent);
   Engineer_Scene_Entity    *newparent     = eina_hash_find(pd->future->entitylookup, &parent); // ;engineer_scene_entity_lookup(obj, parent);

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

      componentnext = eina_hash_find(pd->future->componentlookup, &newparent->firstcomponent);  // engineer_scene_component_lookup(obj, newparent->firstcomponent);
      componentprev = eina_hash_find(pd->future->componentlookup, &componentnext->siblingprev); // engineer_scene_component_lookup(obj, componentnext->siblingprev);

      component->siblingnext = componentprev->siblingnext;
      component->siblingprev = componentnext->siblingprev;
      componentnext->siblingprev = target;
      componentprev->siblingnext = target;
   }
}

EOLIAN static void
_engineer_scene_component_sibling_swap(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint siblinga, uint siblingb)
{
   Engineer_Scene_Component *componenta = eina_hash_find(pd->future->componentlookup, &siblinga); // engineer_scene_component_lookup(obj, siblinga);
   Engineer_Scene_Component *componentb = eina_hash_find(pd->future->componentlookup, &siblingb); // engineer_scene_component_lookup(obj, siblingb);

   if (componenta->parent == componentb->parent)
   {
      Engineer_Scene_Entity *parent = eina_hash_find(pd->future->componentlookup, &componenta->parent); //engineer_scene_entity_lookup(obj, componenta->parent);

      if (siblinga == parent->firstcomponent)
      {
         parent->firstcomponent = siblingb;
      }
      if (siblingb == parent->firstcomponent)
      {
         parent->firstcomponent = siblinga;
      }

      Engineer_Scene_Component *componentanext, *componentaprev, *componentbnext, *componentbprev;

      componentanext = eina_hash_find(pd->future->componentlookup, &componenta->siblingnext); // engineer_scene_component_lookup(obj, componenta->siblingnext);
      componentaprev = eina_hash_find(pd->future->componentlookup, &componenta->siblingprev); // engineer_scene_component_lookup(obj, componenta->siblingprev);
      componentbnext = eina_hash_find(pd->future->componentlookup, &componentb->siblingnext); // engineer_scene_component_lookup(obj, componentb->siblingnext);
      componentbprev = eina_hash_find(pd->future->componentlookup, &componentb->siblingprev); // engineer_scene_component_lookup(obj, componentb->siblingprev);

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

/*** Sector Callbacks ***/
/*
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
*/
/*** Sector Methods ***/
/*
EOLIAN static uint
_engineer_scene_sector_create(Eo *obj, Engineer_Scene_Data *pd,
        uint parent)
{
   Engineer_Scene_Sector *sector, sectordata;
   sector = &sectordata;
   memset(sector, 0, sizeof(Engineer_Scene_Sector));

   uint buffer;

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

   // Create and fill our sector->module array with a new module cache for each registered module.
   sector->cache = NULL;
   Eo *(*module_add)(Eo *obj);
   Engineer_Game_Module *module;
   Efl_Object *cache;
   uint count = eina_inarray_count(pd->modulecache);
   if (count != 0)
   {
      // fixme
      for (uint current = 1; current <= count; current++) //for (uint current = 0; current < count; current++)
      {
         module = eina_inarray_nth(pd->modulecache, current);
         module_add = module->add;
         cache = module_add(obj);
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

   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &componentid;
   key.size = sizeof(uint);
   data.data = &payload;
   data.ulen = sizeof(payload);
   data.flags = DB_DBT_USERMEM;
   pd->sectortable->put(pd->sectortable, NULL, &key, &data, 0);

   return componentid;
}
*/
/*** Database File Methods ***/
/*
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
*/
#include "engineer_scene.eo.c"
