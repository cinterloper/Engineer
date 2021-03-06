#include "engineer_node.h"

/*** Node EFL API ***/

Eo *
engineer_node_new(Eo *parent, const char *path EINA_UNUSED, const char *title EINA_UNUSED)
{
   Eo *node = efl_add(ENGINEER_NODE_CLASS, parent);
      //engineer_node_path_set(efl_added,  path),
      //engineer_node_title_set(efl_added, title));

   return node;
}

/*** Node Eo Constructors/Destructors ***/

EOLIAN static Efl_Object *
_engineer_node_efl_object_constructor(Eo *obj, Engineer_Node_Data *pd EINA_UNUSED)
{
   return efl_constructor(efl_super(obj, ENGINEER_NODE_CLASS));
}

EOLIAN static Efl_Object *
_engineer_node_efl_object_finalize(Eo *obj, Engineer_Node_Data *pd)
{
    obj = efl_finalize(efl_super(obj, ENGINEER_NODE_CLASS));

   // Set up our path elements.
   //if (pd->path == NULL) getcwd(pd->path, sizeof(PATH_MAX));
   if (pd->game == NULL) pd->game = "Default Node Title";

   pd->ipaddress    = 1; // 2130706433; // For now, (127).0.0.1
   pd->mode         = 0; // Standalone = 0; Client = 1; Server = 2;.
   pd->peers        = eina_hash_string_superfast_new(eng_free_cb);
   pd->scenes       = eina_hash_string_superfast_new(eng_free_cb);

   pd->classes      = eina_hash_string_superfast_new(eng_free_cb);

   pd->entitycount  = 0;
   pd->entityqueue  = eina_inarray_new(sizeof(uint64_t), 0);
   pd->entitylocate = eina_hash_int32_new(eng_free_cb);
   pd->entitystatus = eina_hash_int64_new(eng_free_cb);

   pd->componentcount  = 0;
   pd->componentqueue  = eina_inarray_new(sizeof(uint64_t), 0);
   pd->componentlocate = eina_hash_int32_new(eng_free_cb);
   pd->componentstatus = eina_hash_int64_new(eng_free_cb);
   pd->componentclass  = eina_hash_int64_new(NULL);

   printf("Finalize Path: %s, Title: %s\n", pd->path, pd->game);
   printf("Active Threads Test: %d\n", ecore_thread_available_get());

   // Set up our path var.  Usually /opt/$GAMENAME.
   //Eina_Stringshare *gamepath = eina_stringshare_printf("%s/%s/", pd->path, pd->title);

   //printf("Game Module Checkpoint.\n\n");

   // Load any registered modules automatically.

   return obj;
}

EOLIAN static void
_engineer_node_efl_object_destructor(Eo *obj, Engineer_Node_Data *pd EINA_UNUSED)
{
   efl_destructor(efl_super(obj, ENGINEER_NODE_CLASS));
}

/*** Node Eo @property getter/setters. ***/

EOLIAN static const char *
_engineer_node_path_get(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd)
{
  return pd->path;
}

EOLIAN static void
_engineer_node_path_set(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd, const char *path)
{
   pd->path = eina_stringshare_add(path);
}

EOLIAN static const char *
_engineer_node_title_get(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd)
{
  return pd->game;
}

EOLIAN static void
_engineer_node_title_set(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd, const char *game)
{
   pd->game = eina_stringshare_add(game);
}
/*
EOLIAN static void
_engineer_node_scene_archive(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd EINA_UNUSED,
        Eina_Stringshare *name EINA_UNUSED)
{
}

EOLIAN static Efl_Object *
_engineer_node_scene_recall(Eo *obj, Engineer_Node_Data *pd,
        Eina_Stringshare *name)
{
   printf("Scene Load Checkpoint 1.\n");

   // Create the scene object and load the data into it.
   Efl_Object *scene = engineer_scene_new(obj, name);

   printf("Scene Load Checkpoint 2.\n");

   // Add the newly created scene object to the pd->scenes list using it's name as the key.
   if (eina_hash_find(pd->scenes, name)) return NULL;
   eina_hash_add(pd->scenes, name, scene);

   printf("Scene Load Checkpoint 3.\n");

   return scene;
}

EOLIAN static void
_engineer_node_scene_flush(Eo *obj, Engineer_Node_Data *pd EINA_UNUSED,
        Eina_Stringshare *name)
{
}
*/
EOLIAN static uint64_t
_engineer_node_module_load(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        const char *symbol)
{
   Engineer_Component_Class *class = malloc(sizeof(Engineer_Component_Class));
   uint64_t classid = engineer_hash_murmur3(symbol, strlen(symbol), 242424);

   // Make sure our module file exists before loading it.
   Eina_Stringshare *file = eina_stringshare_printf("../lib/lib%s.so", symbol);
   if(!ecore_file_exists(file)) {eina_stringshare_del(file); return ULONG_NULL;}

   // Check to see if the module class is already registered.
   uint64_t *test = eina_hash_find(pd->classes, &classid);
   if(test != NULL) return *test;

   // Create our eina_module reference handle.
   class->eina = eina_module_new(file);
   if(class->eina == NULL) {eina_stringshare_del(file); return ULONG_NULL;}
   eina_module_load(class->eina);

   #define RETURN {eina_module_free(class->eina); eina_stringshare_del(file); return ULONG_NULL;}

   class->module_new = eina_module_symbol_get(class->eina, "engineer_module_new");
   if(class->module_new == NULL) RETURN;
   class->module_update = eina_module_symbol_get(class->eina, "engineer_module_update");
   if(class->module_update == NULL) RETURN;

   class->cache_sizeof = eina_module_symbol_get(class->eina,
                                 "engineer_module_cache_sizeof");
   if(class->cache_sizeof == NULL) RETURN;

   class->component_factory = eina_module_symbol_get(class->eina,
                                 "engineer_module_component_factory");
   if(class->component_factory == NULL) RETURN;

   class->component_index_get  = eina_module_symbol_get(class->eina,
                                 "engineer_module_component_index_get");
   if(class->component_index_get == NULL) RETURN;
   class->component_parent_set = eina_module_symbol_get(class->eina,
                                 "engineer_module_component_parent_set");
   if(class->component_parent_set == NULL) RETURN;
   class->component_parent_get = eina_module_symbol_get(class->eina,
                                 "engineer_module_component_parent_get");
   if(class->component_parent_get == NULL) RETURN;
   class->component_siblingnext_set = eina_module_symbol_get(class->eina,
                                 "engineer_module_component_siblingnext_set");
   if(class->component_siblingnext_set  == NULL) RETURN;
   class->component_siblingnext_get = eina_module_symbol_get(class->eina,
                                 "engineer_module_component_siblingnext_get");
   if(class->component_siblingnext_get  == NULL) RETURN;
   class->component_siblingprev_set = eina_module_symbol_get(class->eina,
                                 "engineer_module_component_siblingprev_set");
   if(class->component_siblingprev_set  == NULL) RETURN;
   class->component_siblingprev_get = eina_module_symbol_get(class->eina,
                                 "engineer_module_component_siblingprev_get");
   if(class->component_siblingprev_get  == NULL) RETURN;
   class->component_state_get  = eina_module_symbol_get(class->eina,
                                 "engineer_module_component_state_get");
   if(class->component_state_get  == NULL) RETURN;

   #undef RETURN

   // Set up our module class lookup data.
   //eina_stringshare_add(symbol);
   class->id = classid;
   eina_hash_add(pd->classes, &classid, class);

   printf("Module Loaded. | ClassId: %"PRId64" | File: %s\n", classid, file);
   return classid;
}
/*
EOLIAN static void
_engineer_node_module_flush(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd EINA_UNUSED,
        Eo *target EINA_UNUSED)
{
}
*/

EOLIAN static uint64_t
_engineer_node_entity_id_use(Eo *obj, Engineer_Node_Data *pd)
{
   uint64_t newid;

   //eina_lock();
   if (eina_inarray_count(pd->entityqueue) == 0)
   {
      newid = pd->entitycount;
      pd->entitycount += 1;
   }
   else newid = *(uint64_t*)eina_inarray_pop(pd->entityqueue);
   //eina_unlock();

   engineer_node_entity_location_set(obj, newid, pd->ipaddress);

   return newid;
}

EOLIAN static void
_engineer_node_entity_id_free(Eo *obj, Engineer_Node_Data *pd,
        uint64_t target)
{
   engineer_node_entity_status_set(obj, target, 0);
   eina_inarray_insert_at(pd->entityqueue, 0, &target);
}

EOLIAN static uint64_t
_engineer_node_entity_location_get(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        uint64_t target)
{
  return (uint64_t)eina_hash_find(pd->entitylocate, &target);
}

EOLIAN static void
_engineer_node_entity_location_set(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        uint64_t target, uint64_t location)
{
   eina_hash_set(pd->entitylocate, &target, &location);
}

EOLIAN static uint32_t
_engineer_node_entity_status_get(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        uint64_t target)
{
   uint32_t *status = eina_hash_find(pd->entitystatus, &target);
   if (status == NULL) return 0;
   return *status;
}

EOLIAN static void
_engineer_node_entity_status_set(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        uint64_t target, char mode)
{
   if (mode < 4) // Make sure that our mode is either zero, one, two, or three.
   {
      eina_hash_set(pd->entitystatus, &target, &mode);
   }
}

EOLIAN static uint64_t
_engineer_node_component_id_use(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd)
{
   if (eina_inarray_count(pd->componentqueue) == 0)
   {
      eina_inarray_insert_at(pd->componentqueue, 0, &pd->componentcount);
      pd->componentcount += 1;
   }
   uint64_t *newid = eina_inarray_pop(pd->componentqueue);
   engineer_node_component_location_set(obj, *newid, pd->ipaddress);
   return *newid;
}

EOLIAN static void
_engineer_node_component_id_free(Eo *obj, Engineer_Node_Data *pd,
        uint64_t target)
{
   engineer_node_component_status_set(obj, target, 0);  // Fixme: this no longer refers to the scene.
   eina_inarray_insert_at(pd->componentqueue, 0, &target);
}

EOLIAN static uint64_t
_engineer_node_component_location_get(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        ComponentID target)
{
  return (uint64_t)eina_hash_find(pd->componentlocate, &target);
}

EOLIAN static void
_engineer_node_component_location_set(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        ComponentID target, uint64_t location)
{
   eina_hash_set(pd->componentlocate, &target, &location);
}

EOLIAN static uint32_t
_engineer_node_component_status_get(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        ComponentID target)
{
   uint32_t *status = eina_hash_find(pd->componentstatus, &target);
   if (status == NULL) return 0;
   return *status;
}

EOLIAN static void
_engineer_node_component_status_set(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        ComponentID target, char mode)
{
   if (mode < 4) // Make sure that our mode is either zero, one, two, or three.
   {
      eina_hash_set(pd->componentstatus, &target, &mode);
   }
}

// Takes in a ComponentID and returns the associated Class interface pointer.
EOLIAN static Engineer_Component_Class *
_engineer_node_component_class_get(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        ComponentID target)
{
   ClassID classid;

   classid = (ClassID)eina_hash_find(pd->componentclass, &target);
   return eina_hash_find(pd->classes, &classid);
}

// Takes in a ClassID and returns the associated Class interface pointer.
EOLIAN static Engineer_Component_Class *
_engineer_node_component_class_get_by_id(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        ClassID classid)
{
   return eina_hash_find(pd->classes, &classid);
}

EOLIAN static Engineer_Component_Class *
_engineer_node_component_class_get_by_label(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        ClassLabel classlabel)
{
   ClassID classid;

   classid = engineer_hash_murmur3(classlabel, strlen(classlabel), 242424);
   return eina_hash_find(pd->classes, &classid);
}

// Takes in a ComponentID and returns it's ClassID.
EOLIAN static ClassID
_engineer_node_component_classid_get(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        ComponentID target)
{
   return (ClassID)eina_hash_find(pd->componentclass, &target);
}

// Set a Component's Class to the Class type indicated by the classid;
EOLIAN static void
_engineer_node_component_classid_set(Eo *obj EINA_UNUSED, Engineer_Node_Data *pd,
        ComponentID target, ClassID classid)
{
   eina_hash_set(pd->componentclass, &target, (ClassID*)classid);
}

#include "engineer_node.eo.c"

