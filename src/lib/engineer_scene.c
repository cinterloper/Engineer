#include "engineer_scene.h"

// eolian_gen `pkg-config --variable=eolian_flags ecore eo evas efl` -I . -g h engineer_scene.eo
// eolian_gen `pkg-config --variable=eolian_flags ecore eo evas efl` -I . -g c engineer_scene.eo

Eo *
engineer_scene_new(Eo *parent, const char *name EINA_UNUSED)
{
   Eo *scene = efl_add(ENGINEER_SCENE_CLASS, parent);
                  //engineer_scene_name_set(efl_added, name));

   return scene;
}

/*** Constructors ***/

EOLIAN static Efl_Object *
_engineer_scene_efl_object_constructor(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED)
{
   return efl_constructor(efl_super(obj, ENGINEER_SCENE_CLASS));
}

Efl_Object *
_engineer_scene_efl_object_finalize(Eo *obj, Engineer_Scene_Data *pd)
{
   obj = efl_finalize(efl_super(obj, ENGINEER_SCENE_CLASS));

   static const
   Engineer_Scene_Frame  blank;
   Engineer_Scene_Frame *frame;
   Engineer_Node_Data   *nodepd;
   uint32_t count;

   // The Scene size is in units of (2^x)/(2^16) meters where x is the setting. Max: bitwidth--.
   pd->size = 63;

   // Set up the Scene iterator default clockrate.
   pd->clockrate = 32;

   // Create and initialize the space (3 frames) needed to iterate our timeline.
   pd->buffer = eina_inarray_new(sizeof(Engineer_Scene_Frame), 0);
   eina_inarray_push(pd->buffer, &blank);
   eina_inarray_push(pd->buffer, &blank);
   eina_inarray_push(pd->buffer, &blank);

   // Initialize the inarrays needed to store the Frame's contents.
   EINA_INARRAY_FOREACH(pd->buffer, frame)
   {
      frame->name = eina_inarray_new(sizeof(Eina_Stringshare*), 0);

      frame->parent         = eina_inarray_new(sizeof(uint64_t), 0);
      frame->siblingnext    = eina_inarray_new(sizeof(uint64_t), 0);
      frame->siblingprev    = eina_inarray_new(sizeof(uint64_t), 0);
      frame->firstentity    = eina_inarray_new(sizeof(uint64_t), 0);
      frame->firstcomponent = eina_inarray_new(sizeof(uint64_t), 0);

      frame->inbox  = eina_inarray_new(sizeof(Eina_Inarray*), 0);
      frame->outbox = eina_inarray_new(sizeof(Eina_Inarray*), 0);
   }

   // We need to set up our timeline pointers for the first time here.
   pd->future  = eina_inarray_nth(pd->buffer, 0);
   pd->present = eina_inarray_nth(pd->buffer, 1);
   pd->past    = eina_inarray_nth(pd->buffer, 2);

   pd->timecard = eina_inarray_new(sizeof(uint64_t), 3);
   pd->id       = eina_inarray_new(sizeof(uint64_t), 0);
   pd->lookup   = eina_hash_int64_new(NULL);

   // Create and fill our pd->scenecache array with a new Eo instance for each registered module.
   pd->modules = eina_hash_pointer_new(eng_free_cb);
   nodepd = efl_data_scope_get(efl_parent_get(obj), ENGINEER_NODE_CLASS);
   count  = eina_hash_population(nodepd->classes);
   if (count != 0)
   {
      Engineer_Module_Class *module;
      Eo *(*module_new)(Eo *obj);
      uint32_t current;
      for (current = 0; current < count; current++)
      {
         module = eina_hash_find(nodepd->classes, &current);
         module_new = module->factory;
         eina_hash_add(pd->modules, &module->id, module_new(obj));
      }
   }

   pd->iterator = ecore_timer_add((double)1/pd->clockrate, _engineer_scene_iterate_cb, obj);
   //ecore_timer_freeze(pd->iterator);

   // If our Scene is new, create a root Entity and set it up.
   if (eina_inarray_count(pd->id) == 0)
   {
      uint64_t id;

      id = engineer_node_entity_id_use(efl_parent_get(obj));
      engineer_scene_entity_create(obj, id, ULONG_NULL, "Scenegraph Root");

      printf("Root Entity Create Checkpoint. EID: %ld\n", id);
   }

   printf("Active Threads Test: %d\n", ecore_thread_available_get());

   return obj;
}

EOLIAN static void
_engineer_scene_efl_object_destructor(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd EINA_UNUSED)
{
   efl_destructor(efl_super(obj, ENGINEER_SCENE_CLASS));
}

/*** Scene Efl Object property getter/setters. ***/

EOLIAN static const char *
_engineer_scene_name_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd)
{
  return pd->name;
}

EOLIAN static void
_engineer_scene_name_set(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        const char *name)
{
   pd->name = eina_stringshare_add(name);
}

EOLIAN static Eo *
_engineer_scene_module_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint64_t *classid)
{
   Eo *module;

   module = eina_hash_find(pd->modules, classid);

   return module;
}

/*** Iteration Methods. These are what make everything happen. ***/

EOLIAN static Eina_Bool
_engineer_scene_iterate(Eo *obj, Engineer_Scene_Data *pd)
{
   double   timestamp;
   uint32_t index, count;

   Engineer_Scene_Frame  *buffer;
   Engineer_Module_Class *class;

   // Store the timestamp for when this Sector's clock tick begins.
   timestamp = ecore_time_get();

   // Cycle the timeline to get to our next frame.
   buffer      = pd->past;
   pd->past    = pd->present;
   pd->present = pd->future;
   pd->future  = buffer;

   printf("\nScene Iterator Checkpoint 1.\n");

   // Copy over our present Scenegraph Entity metadata to the future Frame.
   for(index = 0; index < eina_inarray_count(pd->id); index++)
   {
      #define METADATA \
         FIELD(name) \
         FIELD(parent) \
         FIELD(siblingnext) \
         FIELD(siblingprev) \
         FIELD(firstentity) \
         FIELD(firstcomponent)

      #define FIELD(key) \
         eina_inarray_replace_at(pd->future->key, index, \
            eina_inarray_nth(pd->present->key, index));
      METADATA
      #undef FIELD
      #undef METADATA
   }

   printf("Scene Iterator Checkpoint 2.\n");

   // Empty the future frame's inboxen (into the history).
   count = 0;
   for(index = 0; index < eina_inarray_count(pd->present->outbox); index++)
   {
      eina_inarray_flush(*(Eina_Inarray**)eina_inarray_nth(pd->future->outbox, index));
      eina_inarray_push(*(Eina_Inarray**)eina_inarray_nth(pd->future->outbox, index), &count);
   }
   for(index = 0; index < eina_inarray_count(pd->present->inbox); index++)
   {
      eina_inarray_flush(*(Eina_Inarray**)eina_inarray_nth(pd->future->inbox, index));
      eina_inarray_push(*(Eina_Inarray**)eina_inarray_nth(pd->future->inbox, index), &count);
   }

   printf("Scene Iterator Checkpoint 3.\n");

   // Alter the Scenegraph according to the present Entities' outboxen.
   index = 0;
   Eina_Inarray **outbox;
   EINA_INARRAY_FOREACH(pd->present->outbox, outbox)
   {
      printf("Scene Iterator Response Checkpoint.\n");
      engineer_scene_respond(obj, *outbox);
      index += 1;
   }

   // Iterate thru each component's data in the scene for every attached module.
   printf("Scene Iterate Module Tasks Start Checkpoint.\n");
   Eo *(*iterate)(Eo *obj);

   Eina_Iterator   *iterator;
   Eina_Hash_Tuple *tuple;
   iterator = eina_hash_iterator_tuple_new(pd->modules);
   while (eina_iterator_next(iterator, (void**)&tuple))
   {
      class   = engineer_node_module_class_lookup(efl_parent_get(obj), (uint64_t)tuple->key);
      iterate = class->iterate;
      iterate(tuple->data);
   }
   eina_iterator_free(iterator);

   // Check to see if we are taking more than 85% of our tick time, if so, decrease the clock rate.
   timestamp -= ecore_time_get();
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

   // Set our completion timestamp for this frame.
   timestamp = ecore_time_get();
   count = eina_inarray_push(pd->timecard, &timestamp);

   printf("Scene Iterator End Checkpoint. Clockrate: %d Htz, Timestamp: %1.5f\n",
      pd->clockrate, *(double*)eina_inarray_nth(pd->timecard, count));

   return ECORE_CALLBACK_RENEW;
}

Eina_Bool _engineer_scene_iterate_cb(void *obj)
{
    engineer_scene_iterate(obj);
    return ECORE_CALLBACK_RENEW;
}

EOLIAN static void
_engineer_scene_respond(Eo *obj, Engineer_Scene_Data *pd,
        Eina_Inarray *outbox)
{
   uint64_t count, offset, current, type, size, target, parent;

   Engineer_Module_Class *class;
   Eo                    *module;
   Eina_Inarray          *input;

   count  = *(uint64_t*)eina_inarray_nth(outbox, 0);
   offset = 1;
   for(current = 0; current < count; current++)
   {
      type = (*(uint64_t*)eina_inarray_nth(outbox, offset + 1));
      switch(type)
      {
         case 0: // Respond by creating an Entity and attaching it to a parent Entity.
         size  = 4;
         target = *(uint64_t*)eina_inarray_nth(outbox, offset + 2);
         parent = *(uint64_t*)eina_inarray_nth(outbox, offset + 3);

         engineer_scene_entity_create(obj, target, parent, NULL);
         break;

         case 1: // Respond by creating a Component and attaching it to a parent Entity.
         input  = eina_inarray_nth(outbox, offset + 2);
         class  = engineer_node_module_class_lookup(efl_parent_get(obj), *(uint64_t*)input);
         module = engineer_scene_module_get(obj, (uint64_t*)input);
         size   = class->size;
         target = *(uint64_t*)eina_inarray_nth(outbox, offset + 3);
         parent = *(uint64_t*)eina_inarray_nth(outbox, offset + 4);

         // Push our resident notice payload to the input buffer.
         input  =  eina_inarray_new(sizeof(uint64_t), class->size);
         for(count = 0; count < class->size; count++)
            eina_inarray_push(input, eina_inarray_nth(outbox, offset + count + 5));

         // Invoke our module's component_create method.
         uint64_t (*component_create)(Eo *module, uint64_t target, uint64_t parent, void *input);
         component_create = class->component_create;
         target = *(uint64_t*)eina_inarray_nth(pd->id, target);

         component_create(module, target, parent, input);

         eina_inarray_free(input);
         break;
         /*
         case 2: // Request to Reattach an Entity to a new parent Entity.
         break;

         case 3: // Request to Reattach a Component to a new parent Entity.
         break;

         case 4: // Request to Destroy an Entity and it's descendants.
         break;

         case 5: // Request to Destroy Component.
         break;

         case 6: // Request to Archive Entity and it's descendants.
         break;

         case 7: // Request to Archive Component.
         break;

         case 8: // Request to Recall Entity and it's descendants.
         break;

         case 9: // Request to Recall Component.
         break;
        */
      }
      offset += size;
   }
}

/*** Entity Methods ***/

EOLIAN static Eina_Bool
_engineer_scene_entity_create(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t id, uint64_t parent, const char *name)
{
   Engineer_Scene_Frame *frame;
   Eina_Inarray         *box;
   uint64_t              index;
   uint32_t              buffer;

   buffer = UINT_NULL;
   if(engineer_scene_entity_lookup(obj, id) == UINT_NULL)
   {
      //eina_inarray_push(pd->history, eina_inarray_new(sizeof(uint64_t), 0));
      eina_inarray_push(pd->id, &id);
      index = eina_inarray_count(pd->id) - 1;
      eina_hash_add(pd->lookup, &id, (void*)index);

      name = eina_stringshare_printf("%s", name);
      EINA_INARRAY_FOREACH(pd->buffer, frame)
      {
         eina_inarray_push(frame->name,           &name);
         eina_inarray_push(frame->parent,         &parent);
         eina_inarray_push(frame->siblingnext,    &id);
         eina_inarray_push(frame->siblingprev,    &id);
         eina_inarray_push(frame->firstcomponent, &buffer);
         eina_inarray_push(frame->firstentity,    &buffer);
         index = 0;
         box = eina_inarray_new(sizeof(uint64_t), 0);
         eina_inarray_push(box, &index);
         eina_inarray_push(frame->outbox,         &box);
         box = eina_inarray_new(sizeof(uint64_t), 0);
         eina_inarray_push(box, &index);
         eina_inarray_push(frame->inbox,          &box);
      }
      engineer_scene_entity_parent_set(obj, id, parent);

      printf("Entity Create Checkpoint. EID: %ld, Parent: %ld, NextSib: %ld, PrevSib: %ld, Name: %s\n",
         id, parent, id, id, name);
   }

   return EINA_TRUE;
}
/*
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

EOLIAN static void
_engineer_scene_entity_archive(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target EINA_UNUSED)
{
}

EOLIAN static void
_engineer_scene_entity_recall(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd EINA_UNUSED,
        uint target EINA_UNUSED)
{
}
*/
EOLIAN uint64_t
_engineer_scene_entity_lookup(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint64_t entityid)
{
   return (uint64_t)eina_hash_find(pd->lookup, &entityid) - 1;
}
/*
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

EOLIAN static uint64_t
_engineer_scene_entity_parent_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint64_t target)
{
   target = eina_hash_find(pd->present->lookup, &target) - 1;
   if (target == UINT_NULL) return UINT_NULL;

   return *(uint64_t*)eina_inarray_nth(pd->present->parent, target);
}
*/
EOLIAN static void
_engineer_scene_entity_parent_set(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t target, uint64_t newparent)
{
   uint32_t buffer;

   target    = engineer_scene_entity_lookup(obj, target);
   newparent = engineer_scene_entity_lookup(obj, newparent);

   if (target == UINT_NULL || newparent == UINT_NULL) return;

   uint64_t targetnext     = *(uint64_t*)eina_inarray_nth(pd->future->siblingnext, target);
   uint64_t targetprev     = *(uint64_t*)eina_inarray_nth(pd->future->siblingprev, target);
   uint64_t oldparent      = *(uint64_t*)eina_inarray_nth(pd->future->parent,      target);
   uint64_t oldfirstentity = *(uint64_t*)eina_inarray_nth(pd->future->firstentity, oldparent);

   // Check to see if this Entity has it's relationship data defined.
   if (oldparent == UINT_NULL || targetnext == UINT_NULL || targetprev == UINT_NULL) return;

   oldparent  = engineer_scene_entity_lookup(obj, oldparent);
   targetnext = engineer_scene_entity_lookup(obj, targetnext);
   targetprev = engineer_scene_entity_lookup(obj, targetprev);

   // Check to see if the target is the old parents first child.
   if (target == oldfirstentity)
   {
      eina_inarray_replace_at(pd->future->firstentity, oldparent,
        eina_inarray_nth(pd->id, targetnext));
   }

   // Check to see if the old parent has only one child Entity.
   if (*(uint64_t*)eina_inarray_nth(pd->future->siblingnext, oldfirstentity) ==
       *(uint64_t*)eina_inarray_nth(pd->future->siblingprev, oldfirstentity)  )
   {
      buffer = UINT_NULL;
      eina_inarray_replace_at(pd->future->firstentity, oldparent, &buffer);
   }
   else // relink the remaining child Entities.
   {
      eina_inarray_replace_at(pd->future->siblingprev, targetnext,
         eina_inarray_nth(pd->future->siblingprev,
         *(uint64_t*)eina_inarray_nth(pd->id, target)));
      eina_inarray_replace_at(pd->future->siblingnext, targetprev,
         eina_inarray_nth(pd->future->siblingnext,
         *(uint64_t*)eina_inarray_nth(pd->id, target)));
   }

   // Set the new parent EntityID for the target Entity.
   eina_inarray_replace_at(pd->future->parent, target,
      eina_inarray_nth(pd->id, newparent));

   // Check to see if new parent has any children. If not, set up the first child properly.
   if (*(uint64_t*)eina_inarray_nth(pd->future->firstentity, newparent) == UINT_NULL)
   {
      eina_inarray_replace_at(pd->future->firstentity, newparent,
         eina_inarray_nth(pd->id, target));

      eina_inarray_replace_at(pd->future->siblingnext, target,
         eina_inarray_nth(pd->id, target));
      eina_inarray_replace_at(pd->future->siblingprev, target,
         eina_inarray_nth(pd->id, target));
   }
   else // add the target Entity to the back end of the new parent's child list.
   {
      targetnext = engineer_scene_entity_lookup(obj,
                      *(uint64_t*)eina_inarray_nth(pd->future->firstentity, newparent));
      targetnext = engineer_scene_entity_lookup(obj,
                      *(uint64_t*)eina_inarray_nth(pd->future->siblingprev, targetnext));

      eina_inarray_replace_at(pd->future->siblingnext, target,
         eina_inarray_nth(pd->future->siblingnext, targetprev));
      eina_inarray_replace_at(pd->future->siblingprev, target,
         eina_inarray_nth(pd->future->siblingprev, targetnext));

      eina_inarray_replace_at(pd->future->siblingprev, targetnext,
         eina_inarray_nth(pd->id, target));
      eina_inarray_replace_at(pd->future->siblingnext, targetnext,
         eina_inarray_nth(pd->id, target));
   }
}

EOLIAN static void
_engineer_scene_entity_siblingnext_set(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t target, uint64_t siblingnext)
{
   target = engineer_scene_entity_lookup(obj, target);
   eina_inarray_replace_at(pd->future->siblingnext, target, &siblingnext);
}

EOLIAN static uint64_t
_engineer_scene_entity_siblingnext_get(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t target)
{
   target = engineer_scene_entity_lookup(obj, target);
   return *(uint64_t*)eina_inarray_nth(pd->future->siblingnext, target);
}

EOLIAN static void
_engineer_scene_entity_siblingprev_set(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t target, uint64_t siblingprev)
{
   target = engineer_scene_entity_lookup(obj, target);
   eina_inarray_replace_at(pd->future->siblingprev, target, &siblingprev);
}

EOLIAN static uint64_t
_engineer_scene_entity_siblingprev_get(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t target)
{
   target = engineer_scene_entity_lookup(obj, target);
   return *(uint64_t*)eina_inarray_nth(pd->future->siblingprev, target);
}

EOLIAN static void
_engineer_scene_entity_firstentity_set(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t target, uint64_t component)
{
   target = engineer_scene_entity_lookup(obj, target);
   eina_inarray_replace_at(pd->future->firstentity, target, &component);
}

EOLIAN static uint64_t
_engineer_scene_entity_firstentity_get(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t target)
{
   target = engineer_scene_entity_lookup(obj, target);
   return *(uint64_t*)eina_inarray_nth(pd->future->firstentity, target);
}

EOLIAN static void
_engineer_scene_entity_firstcomponent_set(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t target, uint64_t component)
{
   target = engineer_scene_entity_lookup(obj, target);
   eina_inarray_replace_at(pd->future->firstcomponent, target, &component);
}

EOLIAN static uint64_t
_engineer_scene_entity_firstcomponent_get(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t target)
{
   target = engineer_scene_entity_lookup(obj, target);
   return *(uint64_t*)eina_inarray_nth(pd->future->firstcomponent, target);
}

EOLIAN static Eina_Inarray *
_engineer_scene_entity_inbox_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint64_t entityid)
{
   return eina_inarray_nth(pd->present->inbox, *(uint64_t*)eina_hash_find(pd->lookup, &entityid));
}

EOLIAN static Eina_Inarray *
_engineer_scene_entity_outbox_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint64_t entityid)
{
   return eina_inarray_nth(pd->present->outbox, *(uint64_t*)eina_hash_find(pd->lookup, &entityid));
}
/*
EOLIAN static void
_engineer_scene_entity_sibling_swap(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint siblinga, uint siblingb)
{
   Engineer_Entity *entitya = eina_hash_find(pd->future->entitylookup, &siblinga);
   Engineer_Entity *entityb = eina_hash_find(pd->future->entitylookup, &siblingb);
   if (entitya == NULL || entityb == NULL) return;

   if (entitya->parent == entityb->parent)
   {
      Engineer_Scene_Entity *parent = eina_hash_find(pd->future->entitylookup, &entitya->parent);

      if (siblinga == parent->firstentity)
      {
         parent->firstentity = siblingb;
      }
      if (siblingb == parent->firstentity)
      {
         parent->firstentity = siblinga;
      }

      Engineer_Entity *entityanext = eina_hash_find(pd->lookup, &entitya->siblingnext);
      Engineer_Entity *entityaprev = eina_hash_find(pd->lookup, &entitya->siblingprev);
      Engineer_Entity *entitybnext = eina_hash_find(pd->lookup, &entityb->siblingnext);
      Engineer_Entity *entitybprev = eina_hash_find(pd->lookup, &entityb->siblingprev);

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
        uint64_t target)
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
_engineer_scene_entity_components_get(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        uint64_t target)
{
   Eina_Inarray *results = eina_inarray_new(sizeof(Engineer_Scene_Component*), 0);
   Engineer_Scene_Entity    *entity  = engineer_scene_entity_lookup(obj, target);
   Engineer_Scene_Component *first   = engineer_scene_component_lookup(obj, entity->firstcomponent);
   Engineer_Scene_Component *current = engineer_scene_component_lookup(obj, first->siblingnext);

   while (current != first)
   {
      eina_inarray_push(results, current);
      current = engineer_scene_component_lookup(obj, current->siblingnext);
   }
   eina_inarray_push(results, current);

   return results;
}
*/
/*** Scene Notification Requests ***/

EOLIAN static void
_engineer_scene_notice_push_event(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t target, uint64_t sender, uint64_t type, void *payload, uint64_t size)
{
   Eina_Inarray *inbox;
   uint64_t     *input;
   uint64_t index, count;

   index = engineer_scene_entity_lookup(obj, target);
   inbox = eina_inarray_nth(pd->future->inbox, index);

   eina_inarray_push(inbox, &sender);
   eina_inarray_push(inbox, &type);
   eina_inarray_push(inbox, &size);
   for (count = 0; count < size; count++)
      eina_inarray_push(inbox, payload + (count << 3));

   input = eina_inarray_nth(inbox, 0);
   *input += 1;
}
/*
EOLIAN static void
_engineer_scene_notice_push_event_ancestors(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t entityid, uint32_t response, uint32_t size, void *payload)
{
}

EOLIAN static void
_engineer_scene_notice_push_event_descendants(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t entityid, uint64_t response, uint32_t size, void *payload)
{
}
*/
EOLIAN static void
_engineer_scene_notice_push_entity_create(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t sender, uint64_t entityid, uint64_t parent)
{
   Eina_Inarray *outbox;
   uint64_t type, *input;
   uint32_t index;

   index  = engineer_scene_entity_lookup(obj, entityid);
   outbox = eina_inarray_nth(pd->future->outbox, index);

   eina_inarray_push(outbox, &sender);
   eina_inarray_push(outbox, &type);
   eina_inarray_push(outbox, &entityid);
   eina_inarray_push(outbox, &parent);

   input = eina_inarray_nth(outbox, 0);
   *input += 1;
}

EOLIAN static void
_engineer_scene_notice_push_component_create(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t sender, uint64_t classid, uint64_t componentid, uint64_t parent, uint64_t *payload)
{
   Engineer_Module_Class *class;
   Eina_Inarray *outbox;
   uint64_t type, *input;
   uint32_t index, count;

   index  = engineer_scene_entity_lookup(obj, componentid);
   outbox = eina_inarray_nth(pd->future->outbox, index);
   class  = engineer_node_module_class_lookup(efl_parent_get(obj), classid);

   eina_inarray_push(outbox, &sender);
   eina_inarray_push(outbox, &type);
   eina_inarray_push(outbox, &classid);
   eina_inarray_push(outbox, &componentid);
   eina_inarray_push(outbox, &parent);
   for (count = 0; count < class->size; count ++)
      eina_inarray_push(outbox, payload + (count << 3));

   input = eina_inarray_nth(outbox, 0);
   *input += 1;
}

#include "engineer_scene.eo.c"
