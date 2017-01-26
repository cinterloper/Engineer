#include "engineer_module.h"

// All Modules are actually classes that inherit from the Engineer_Module class.
// All actual Component data is held in a simple struct of linear arrays.
//
// Our data index space is divided into 3 contiguous regions as follows: |  Legend:
// Low Index >--X---------------Y---> High Index                         |  X == offsetactive
// ActiveRegion | PassiveRegion | DisposalRegion                         |  Y == offsetpassive

/*** Constructors ***/

EOLIAN static Efl_Object *
_engineer_module_efl_object_constructor(Eo *obj, Engineer_Module_Data *pd EINA_UNUSED)
{
   return efl_constructor(efl_super(obj, ENGINEER_MODULE_CLASS));
}

Efl_Object *
_engineer_module_efl_object_finalize(Eo *obj, Engineer_Module_Data *pd)
{
   // Create and initialize the minimum space (3 frames) needed to start our timeline.
   pd->timeline = eina_inarray_new(sizeof(Engineer_Module_Frame), 0);

   engineer_module_timeline_push(obj);
   engineer_module_timeline_push(obj);
   engineer_module_timeline_push(obj);

   pd->past    = eina_inarray_nth(pd->timeline, 0);
   pd->present = eina_inarray_nth(pd->timeline, 0);
   pd->future  = eina_inarray_nth(pd->timeline, 1);
/*
   pd->table->handle = NULL;
   db_create(&pd->table->handle, NULL, 0);
   pd->table->handle->open(
      pd->table->handle,    // DB structure pointer
      NULL,                 // Transaction pointer
      scene,                // On-disk file that holds the database.
      "Module.NAME",        // Optional logical database name
      DB_QUEUE,             // Database access method
      DB_CREATE,            // Open flags
      0);                   // File mode (using defaults)
*/
   return obj;
}

EOLIAN static void
_engineer_module_efl_object_destructor(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED)
{
}

/*** Module Iterator ***/

EOLIAN static void
_engineer_module_iterate(Eo *obj, Engineer_Module_Data *pd)
{
   HANDLE *next, *last;
   uint count = eina_inarray_count(pd->timeline);

   // Cycle the timeline to get to our next frame. This is the frame with the index immediately less
   //    than the current one. This also resets our pointers in case they were nuked by an
   //    eina_inarray_push.
   pd->future   = eina_inarray_nth(pd->timeline, (pd->future->index-1 + count) % count);
   pd->present  = eina_inarray_nth(pd->timeline,  pd->future->index++ % count);
   pd->past     = eina_inarray_nth(pd->timeline,  pd->future->index+2 % count);

   // Wipe clean the allocated space reserved for our next Frame's Entity and Component metadata.
   // Clear all payload data for the future frame.
   eina_inarray_flush((Eina_Inarray*)pd->future->cache);
   eina_hash_free_buckets(pd->future->lookup);

   last = engineer_module_handle_alloc(obj);
   next = engineer_module_handle_alloc(obj);

   // For each component stored in this object, do the engineer_module_update() method.
   for (uint cacheid = 0; cacheid <= pd->future->offsetactive; cacheid += 1)
   {
      engineer_module_cache_lookup(obj, pd->present, cacheid, last);
      engineer_module_cache_lookup(obj, pd->future,  cacheid, next);

      engineer_module_update(obj, last, next, 32);
   }

   engineer_module_handle_free(obj, next);
   engineer_module_handle_free(obj, last);
}

/*** Module Timeline Methods ***/

EOLIAN static void
_engineer_module_timeline_adjust(Eo *obj, Engineer_Module_Data *pd)
{
   // Before we start, we need to know what our present timeline index is, and how large it is.
   uint count = eina_inarray_count(pd->timeline);
   uint index = pd->present->index;

   Eo *parent = efl_parent_get(obj);
   Engineer_Scene_Data *ppd = efl_data_scope_get(parent, ENGINEER_SCENE_CLASS);

   // If the count is more than our retention value and our future Frame pointer is pointing
   //    at the end of the pd->timeline inarray.
   if ((ppd->retention > count) &&
      (index++ == count))
   {
      engineer_module_timeline_push(obj);
      count += 1;
   }

   // If it is less than our retention value, and we are in the correct timeline window.
   if ((ppd->retention < count) &&
      (index++ <= ppd->retention) &&
      (index-- >= count - ppd->retention))
   {
      engineer_module_timeline_pop(obj);
      count -= 1;
   }
}

EOLIAN static void
_engineer_module_timeline_push(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd)
{
   uint index;
   HANDLE *cache;
   Engineer_Module_Frame *frame, blank;

   // Allocate the main memory space needed to store the Frame and zero it out.
   memset(&blank, 0, sizeof(Engineer_Scene_Frame));
   index = eina_inarray_push(pd->timeline, &blank);
   frame = eina_inarray_nth(pd->timeline, index);

   cache = frame->cache;
   frame->offsetactive  = 0;
   frame->offsetpassive = 0;

   // Now allocate it's contents.
   #define VAR(TYPE, KEY) \
      cache->KEY = engineer_type_TYPE_soa_new();
   DATA
   #undef VAR
   frame->lookup = eina_hash_int32_new(eng_free_cb);
}

EOLIAN static void
_engineer_module_timeline_pop(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd)
{
   Engineer_Module_Frame *frame, blank;
   HANDLE *cache;

   // Deallocate the main memory space occupide by the old Frame.
   frame = eina_inarray_pop(pd->timeline);
   blank = *frame;
   frame = &blank;
   cache = frame->cache;

   // Now free it's contents.
   #define VAR(TYPE, KEY) \
      engineer_type_TYPE_soa_free(cache->KEY);
   DATA
   #undef VAR
   eina_hash_free(frame->lookup);
}

EOLIAN static void
_engineer_module_timeline_copy(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        uint cacheid, Engineer_Module_Frame *origin, Engineer_Module_Frame *destination)
{
   HANDLE *cache = origin->cache;
   HANDLE *component, buffer;
   component = &buffer;

   #define VAR(TYPE, KEY) \
      TYPE KEYbuffer; \
      component->KEY = &KEYbuffer;
   DATA
   #undef VAR

   component->component = eina_inarray_nth((Eina_Inarray*)cache->component, cacheid);

   #define VAR(TYPE, KEY) \
      engineer_type_TYPE_soa_nth(cache->KEY, cacheid, component->KEY);
   DATA
   #undef VAR

   cache = destination->cache;

   #define VAR(TYPE, KEY) \
      engineer_type_TYPE_soa_replace_at(cache->KEY, cacheid, component->KEY);
   DATA
   #undef VAR
}

/*** Buffer Methods ***/

EOLIAN static BUFFER *
_engineer_module_buffer_alloc(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED)
{
   return malloc(sizeof(BUFFER));
}

EOLIAN static void
_engineer_module_buffer_free(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        BUFFER *target)
{
   free(target);
}

/** Handle Methods ***/

EOLIAN static HANDLE *
_engineer_module_handle_alloc(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED)
{
   HANDLE *component = malloc(sizeof(HANDLE));

   #define VAR(TYPE, KEY) \
      component->KEY = engineer_type_TYPE_handle_alloc();
   DATA
   #undef VAR

   return component;
}

EOLIAN static void
_engineer_module_handle_free(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        HANDLE *target)
{
   #define VAR(TYPE, KEY) \
      target->KEY = engineer_type_TYPE_handle_free();
   DATA
   #undef VAR

   free(target);
}

/*** Frame Cache Methods ***/

EOLIAN static void
_engineer_module_cache_push(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd,
        uint componentid, HANDLE *data EINA_UNUSED) // Fixme COMPODATA->COMPONENT
{
   void      *lookup            = pd->future->lookup;
   HANDLE    *cache EINA_UNUSED = pd->future->cache;
   uint       cacheindex;

   // Push a new Component data entry into the cache inarrays.
   #define VAR(TYPE, KEY) \
      cacheindex = engineer_type_TYPE_soa_push(cache->KEY, data->KEY);
   DATA
   #undef VAR

   // Set up our lookup table entry for this Component.
   eina_hash_add(lookup, &componentid, &cacheindex);
}

EOLIAN static void
_engineer_module_cache_pop(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        uint target EINA_UNUSED)
{
}

// This method takes a COMPONENT reference tree and populates it with references to the
//    given target cache data.
EOLIAN static void
_engineer_module_cache_lookup(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        Engineer_Module_Frame *frame, uint cacheid, HANDLE *component)
{
   HANDLE *cache     = frame->cache;
   component->component = eina_inarray_nth((Eina_Inarray*)cache->component, cacheid);

   #define VAR(TYPE, KEY) \
      engineer_type_TYPE_soa_nth(cache->KEY, cacheid, component->KEY);
   DATA
   #undef VAR
}

EOLIAN static void
_engineer_module_cache_copy(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        Engineer_Module_Frame *frame, uint cacheid EINA_UNUSED, HANDLE *component EINA_UNUSED)
{
   HANDLE EINA_UNUSED *cache = frame->cache;

   #define VAR(TYPE, KEY) \
      engineer_type_TYPE_soa_replace_at(cache->KEY, cacheid, component->KEY);
   DATA
   #undef VAR
}

EOLIAN static void
_engineer_module_cache_swap(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        Engineer_Module_Frame *frame, uint componenta, uint componentb)
{
   void   *lookup    = frame->lookup;
   HANDLE *cache     = frame->cache;
   void   *component = cache->component;

   // Swap the Component pointer data.
   uint *indexa = eina_hash_find(lookup, &componenta);
   uint *indexb = eina_hash_find(lookup, &componentb);
   void *indexc = eina_inarray_nth((Eina_Inarray*)component, *indexa);
   eina_inarray_replace_at((Eina_Inarray*)component, *indexa, indexb);
   eina_inarray_replace_at((Eina_Inarray*)component, *indexb, indexc);

   // Swap the data for componenta with the data of componentb in all defined VARs.
   #define VAR(TYPE, KEY) \
      TYPEData KEYbuffer; \
      engineer_type_TYPE_soa_nth(cache->KEY, *indexa, &KEYbuffer); \
      engineer_type_TYPE_soa_replace_at(cache->KEY, *indexa,  indexb); \
      engineer_type_TYPE_soa_replace_at(cache->KEY, *indexb, &KEYbuffer);
   DATA
   #undef VAR

   // Switch the ID lookup hashtable entries.
   indexc = indexa;
   eina_hash_modify(lookup, &componenta, indexb);
   eina_hash_modify(lookup, &componentb, indexc);
}

/*** Component Methods ***/

EOLIAN static uint
_engineer_module_component_create(Eo *obj, Engineer_Module_Data *pd EINA_UNUSED,
        uint componentid)
{
   HANDLE data;
   memset(&data, 0, sizeof(HANDLE));

   engineer_module_cache_push(obj, componentid, &data);

   return componentid;
}

EOLIAN static void
_engineer_module_component_load(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED ,
        uint target EINA_UNUSED)
{
 /*
   COMPONENT *payload = engineer_module_data_lookup(obj, target);

   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &target;
   key.size = sizeof(uint);
   data.data = payload;
   data.ulen = sizeof(*payload);
   data.flags = DB_DBT_USERMEM;
   pd->table->get(pd->table, NULL, &key, &data, 0);

   // If there is no component data in the module database that has the target id, do nothing.
   if (data.data == NULL) return;
*/
}

EOLIAN static void
_engineer_module_component_save(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        uint target EINA_UNUSED)
{
/*
   engineer_scene_component_save(obj, target);

   COMPONENT *payload = engineer_module_data_lookup(obj, target);

   // If there is no component data in this module cache that has the target id, do nothing.
   if (payload == NULL) return;

   DBT key, data;
   memset(&key, 0, sizeof(DBT));
   memset(&data, 0, sizeof(DBT));
   key.data = &target;
   key.size = sizeof(uint);
   data.data = payload;
   data.size = sizeof(*payload);

   pd->table->put(pd->table, NULL, &key, &data, 0);

   // Remove the sector data entry from the cache and lookup table.
   COMPONENT *swapee = eina_inarray_nth(pd->cache, eina_inarray_count(pd->cache));
   engineer_module_data_swap(obj, target, swapee->component->id);
   eina_hash_del(pd->lookup, &target, NULL);
   eina_inarray_pop(pd->cache);
*/
}

EOLIAN static void
_engineer_module_component_destroy(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        uint targetid EINA_UNUSED)
{
   // Remove the component from the cache if it's currently in there.
   // Then remove the database entry.
}

EOLIAN static void
_engineer_module_component_lookup(Eo *obj, Engineer_Module_Data *pd,
        uint timeoffset, uint componentid, HANDLE *component)
{
   uint count;
   Engineer_Module_Frame *frame;

   count = eina_inarray_count(pd->timeline);
   frame = eina_inarray_nth(pd->timeline, (pd->future->index + timeoffset) % count);

   uint *cacheid = eina_hash_find(frame->lookup, &componentid);
   cacheid -= 1;
   if ((ulong)cacheid == ULONG_NULL) return;

   engineer_module_cache_lookup(obj, frame, *cacheid, component);
}
/*
#undef NAME
#undef DATA

#undef BUFFER
#undef HANDLE
#undef SYMBOL
*/
#include "engineer_module.eo.c"
