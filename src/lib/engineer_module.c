#include "engineer_module.h"

// All Modules are actually classes that inherit from the Engineer_Module class.
// All actual Component data is held in a simple struct of linear arrays.
//
// Our data index space is divided into 3 contiguous regions as follows: |  Legend:
// Low Index >--X---------------Y---> High Index                         |  X == offsetactive
// ActiveRegion | PassiveRegion | DisposalRegion                         |  Y == offsetpassive

typedef struct
{
 //  Engineer_Scene_Data *scene;         // Stores the pointer of the parent Scene data.
   uint  offsetactive;
   uint  offsetpassive;

   COMPONENT *cache;
   Eina_Hash *lookup;   // (ComponentID) -> (DataIndex) Reference.
   DB        *table;
}
Engineer_Module_Data;

/*** Constructors ***/

EOLIAN static Efl_Object *
_engineer_module_efl_object_constructor(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd)
{
 //  char scene[PATH_MAX];
 //  snprintf(scene, sizeof(scene), "%s.db", pd->scene->name);

   pd->offsetactive  = 0;
   pd->offsetpassive = 0;

   pd->lookup = eina_hash_int32_new(eng_free_cb);
   #define VAR(TYPE, KEY) \
      pd->cache->KEY = engineer_type_TYPE_soa_new();
   DATA
   #undef VAR
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
   return efl_constructor(efl_super(obj, ENGINEER_MODULE_CLASS));
}

EOLIAN static void
_engineer_module_efl_object_destructor(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED)
{
}

/*** Module Iterator ***/

EOLIAN static void
_engineer_module_iterate(Eo *obj, Engineer_Module_Data *pd)
{
   // Set up our iteration data buffer on the stack.
   COMPONENT *current, buffer;
   COMPODATA  payload EINA_UNUSED;
   current = &buffer;

   #define VAR(TYPE, KEY) \
      target->KEY = &payload.KEY
   DATA
   #undef VAR

   // For each component stored in this object, do the module update() func.
   for (uint cacheid = 0; cacheid <= pd->offsetactive; cacheid += 1)
   {
      engineer_module_data_get(obj, cacheid, current);
      engineer_module_component_update(obj, current, 32);
      engineer_module_data_set(obj, cacheid, current);
   }
}

/*** Internal Data Methods ***/

EOLIAN static void
_engineer_module_data_add(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        uint componentid, COMPODATA *data EINA_UNUSED)
{
   uint cacheindex;

   // Push a new Component data entry into the cache inarrays.
   #define VAR(TYPE, KEY) \
      cacheindex = engineer_type_TYPE_soa_push(pd->cache->KEY, data->KEY);
   DATA
   #undef VAR

   // Set up our lookup table entry for this Component.
   eina_hash_add(pd->lookup, &componentid, &cacheindex);
}

EOLIAN static void
_engineer_module_data_set(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        uint cacheid EINA_UNUSED, void *target)
{
   COMPODATA *component EINA_UNUSED = target;

   #define VAR(TYPE, KEY) \
      engineer_type_TYPE_soa_replace_at(pd->cache->KEY, cacheid, component->KEY);
   DATA
   #undef VAR
}

EOLIAN static void
_engineer_module_data_get(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd,
        uint cacheid, void *target)
{
   COMPODATA *component = target;
   component->component = eina_inarray_nth((Eina_Inarray*)pd->cache->component, cacheid);

   #define VAR(TYPE, KEY) \
      engineer_type_TYPE_soa_nth(pd->cache->KEY, cacheid, component->KEY);
   DATA
   #undef VAR
}

EOLIAN static void
_engineer_module_data_swap(EINA_UNUSED Eo *obj, Engineer_Module_Data *pd,
        uint componenta, uint componentb)
{
   uint *indexa = eina_hash_find(pd->lookup, &componenta);
   uint *indexb = eina_hash_find(pd->lookup, &componentb);

   // Swap the Component pointer data.
   void *bufferc = eina_inarray_nth((Eina_Inarray*)pd->cache->component, *indexa);
   eina_inarray_replace_at((Eina_Inarray*)pd->cache->component, *indexa, &indexb);
   eina_inarray_replace_at((Eina_Inarray*)pd->cache->component, *indexb, &bufferc);

   // Swap the data for componenta with the data of componentb in all defined VARs.
   #define VAR(TYPE, KEY) \
      TYPEData KEYbuffer; \
      engineer_type_TYPE_soa_nth(pd->cache->KEY, *indexa, &KEYbuffer); \
      engineer_type_TYPE_soa_replace_at(pd->cache->KEY, *indexa,  indexb); \
      engineer_type_TYPE_soa_replace_at(pd->cache->KEY, *indexb, &KEYbuffer);
   DATA
   #undef VAR

   // Switch the ID lookup hashtable entries.
   uint bufferl = *indexa;
   eina_hash_modify(pd->lookup, &componenta, indexb);
   eina_hash_modify(pd->lookup, &componentb, &bufferl);
}

/*** Component Methods ***/

// I think engineer_scene.c calls these as part of it's component management routines.
EOLIAN static uint
_engineer_module_component_create(EINA_UNUSED Eo *obj, Engineer_Module_Data *pd,
        uint parent)
{
   uint componentid = engineer_scene_component_create(pd->scene, parent);
   SclrData zero = 0;

   engineer_module_data_add(obj, componentid, &zero);

   return componentid;
}

EOLIAN static void
_engineer_module_component_load(Eo *obj, Engineer_Module_Data *pd,
        uint target)
{
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

   engineer_scene_component_load(obj, target);
}

EOLIAN static void
_engineer_module_component_save(Eo *obj, Engineer_Module_Data *pd,
        uint target)
{
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
}

EOLIAN static void
_engineer_module_component_destroy(Eo *obj, Engineer_Module_Data *pd,
        uint targetid)
{
   // Remove the component from the cache if it's currently in there.

   // Then remove the database entry.
}

EOLIAN static void
_engineer_module_component_dispose(Eo *obj, Engineer_Module_Data *pd,
        uint target)
{
}

EOLIAN static COMPONENT *
_engineer_module_component_lookup(EINA_UNUSED Eo *obj, Engineer_Module_Data *pd,
        uint componentid)
{
   uint *cacheid = eina_hash_find(pd->lookup, &componentid);
   cacheid -= 1;
   if ((ulong)cacheid == ULONG_NULL) return NULL;

   return engineer_module_data_get(obj, *cacheid);
}

#include "engineer_module.eo.c"
