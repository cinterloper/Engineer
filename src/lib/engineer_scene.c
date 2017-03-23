#include "engineer_scene.h"

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

Eina_Bool
module_fill(const Eina_Hash *hash EINA_UNUSED, const void *key EINA_UNUSED, void *data,
        void *fdata)
{
   Engineer_Component_Class *class = data;
   Eo *scene = fdata;

   engineer_scene_module_new(scene, class);

   return EINA_TRUE;
}

Efl_Object *
_engineer_scene_efl_object_finalize(Eo *obj, Engineer_Scene_Data *pd)
{
   obj = efl_finalize(efl_super(obj, ENGINEER_SCENE_CLASS));

   Eo *node = efl_parent_get(obj);
   static const
   Engineer_Scene_Frame  blank;
   Engineer_Scene_Frame *frame;
   Engineer_Node_Data   *nodepd;
   //uint32_t count;

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

   pd->modules = eina_hash_pointer_new(eng_free_cb);

   // Create and fill our pd->modules array with a new Eo instance for each registered module.
   nodepd = efl_data_scope_get(node, ENGINEER_NODE_CLASS);
   eina_hash_foreach(nodepd->classes, module_fill, obj);

   pd->iterator = ecore_timer_add((double)1/pd->clockrate, _engineer_scene_iterate_cb, obj);
   //ecore_timer_freeze(pd->iterator);

   // If our Scene is new, create a root Entity and set it up.
   if (eina_inarray_count(pd->id) == 0)
   {
      uint64_t id;

      id = engineer_node_entity_id_use(efl_parent_get(obj));

      printf("\nRoot Entity Create Checkpoint.\n");
      engineer_scene_entity_factory(obj, id, ULONG_NULL);
   }

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
        Engineer_Component_Class *class)
{
   return eina_hash_find(pd->modules, (void*)class->id);
}

EOLIAN static Eina_Bool
_engineer_scene_module_new(Eo *obj, Engineer_Scene_Data *pd,
        Engineer_Component_Class *class)
{
   eina_hash_add(pd->modules, &class->id, class->module_new(obj));

   return EINA_TRUE;
}

static Eina_Bool
engineer_scene_module_update(const Eina_Hash *hash EINA_UNUSED, const void *key, void *data,
        void *fdata)
{
   Engineer_Component_Class *class;
   Eo *node = efl_parent_get(fdata);
   Eo *module = data;
   Engineer_Node_Data *nodepd;

   nodepd = efl_data_scope_get(node, ENGINEER_NODE_CLASS);
   class  = eina_hash_find(nodepd->classes, key);

   return class->module_update(module);
}

/*** Iteration Methods. These are what make everything happen. ***/

EOLIAN static Eina_Bool
_engineer_scene_iterate(Eo *obj, Engineer_Scene_Data *pd)
{
   double   timestamp;
   uint32_t index;
   uint64_t count;

   Engineer_Scene_Frame  *buffer;

   // Store the timestamp for when this Sector's clock tick begins.
   timestamp = ecore_time_get();

   // Cycle the timeline to get to our next frame.
   buffer      = pd->past;
   pd->past    = pd->present;
   pd->present = pd->future;
   pd->future  = buffer;

   printf("\nScene Iterator Checkpoint.\n");

   // Copy over our present Scenegraph Entity metadata to the future Frame.
   for(index = 0; index < eina_inarray_count(pd->id); index++)
   {
      // FIELD(name)
      #define METADATA \
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

   // Empty the future frame's outboxen and inboxen (into the history).
   count = 0;
   for(index = 0; index < eina_inarray_count(pd->future->outbox); index++)
   {
      Eina_Inarray *outbox = *(Eina_Inarray**)eina_inarray_nth(pd->future->outbox, index);
      eina_inarray_flush(outbox);
      eina_inarray_push(outbox, &count);
   }
   for(index = 0; index < eina_inarray_count(pd->future->inbox); index++)
   {
      Eina_Inarray *inbox = *(Eina_Inarray**)eina_inarray_nth(pd->future->inbox, index);
      eina_inarray_flush(inbox);
      eina_inarray_push(inbox, &count);
   }

   // Alter the Scenegraph according to the present Entities' outboxen.
   index = 0;
   Eina_Inarray **outbox;
   EINA_INARRAY_FOREACH(pd->present->outbox, outbox)
   {
      engineer_scene_dispatch(obj, *outbox);
      index += 1;
   }

   // Iterate thru each component's data in the scene for every attached module.
   eina_hash_foreach(pd->modules, engineer_scene_module_update, obj);

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

   // Call the render update.
   //
   // If the viewport is ready for a new renderstate from the camera, have the camera do an intersection test on the scene.
   // Store the resulting objects for the next renderstate.
   //

   printf("Scene Iterator End Checkpoint. Clockrate: %d Htz, Timestamp: %1.5f\n",
      pd->clockrate, *(double*)eina_inarray_nth(pd->timecard, count));

   return ECORE_CALLBACK_RENEW;
}

Eina_Bool
_engineer_scene_iterate_cb(void *obj)
{
    engineer_scene_iterate(obj);
    return ECORE_CALLBACK_RENEW;
}

EOLIAN static void
_engineer_scene_dispatch(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        Eina_Inarray *outbox)
{
   uint64_t count, offset, current, type, size, target, parent;

   Engineer_Component_Class *class;
   Eina_Inarray *input;

   count  = *(uint64_t*)eina_inarray_nth(outbox, 0);
   offset = 1;
   for(current = 0; current < count; current++)
   {
      printf("Dispatch Checkpoint | Count: %ld | Current: %ld\n", count, current);

      type = (*(uint64_t*)eina_inarray_nth(outbox, offset + 1));
      switch(type)
      {
         case 0: // Respond by creating an Entity and attaching it to a parent Entity.
         //printf("Entity Creation Notice Dispatched.\n");
         target = *(uint64_t*)eina_inarray_nth(outbox, offset + 2);
         parent = *(uint64_t*)eina_inarray_nth(outbox, offset + 3);

         size = 4;

         engineer_scene_entity_factory(obj, target, parent);

         break;

         case 1: // Respond by creating a Component and attaching it to a parent Entity.
         //printf("Component Creation Notice Dispatched.\n");
         target = *(ComponentID*)eina_inarray_nth(outbox, offset + 3);
         parent = *(EntityID*)eina_inarray_nth(outbox, offset + 4);

         class  = engineer_node_component_class_get(efl_parent_get(obj), target);
         size   = class->size;

         // Push our resident notice payload to the input buffer.
         input  =  eina_inarray_new(sizeof(uint64_t), class->size);
         for(count = 0; count < class->size; count++)
            eina_inarray_push(input, eina_inarray_nth(outbox, offset + 5 + count));

         // Invoke our module's component_factory method.
         engineer_scene_component_factory(obj, target, parent, (Data*)input);

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

/*** Entity Metadata Getter/Setter API ***/

EOLIAN static void
_engineer_scene_entity_index_set(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        EntityID entityid, Index index)
{
    entityid += 1;
    index    += 1;
    eina_hash_add(pd->lookup, &entityid, (void*)index);
}

EOLIAN Index
_engineer_scene_entity_index_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        EntityID entityid)
{
   Index index = (Index)-1;

   entityid += 1;
   index    += (Index)eina_hash_find(pd->lookup, &entityid);

   return index;
}

EOLIAN Index
_engineer_scene_entity_lookup(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        EntityID entityid)
{
   entityid += 1;
   return (Index)eina_hash_find(pd->lookup, &entityid) - 1;
}

EOLIAN static void
_engineer_scene_entity_parent_set(Eo *obj, Engineer_Scene_Data *pd,
        EntityID target, EntityID newparent)
{
   target = engineer_scene_entity_index_get(obj, target);
   eina_inarray_replace_at(pd->future->parent, target, &newparent);
}

EOLIAN static EntityID
_engineer_scene_entity_parent_get(Eo *obj, Engineer_Scene_Data *pd,
        EntityID target, uint64_t offset)
{
   target = engineer_scene_entity_index_get(obj, target);

   switch(offset)
   {
      case 0:
         return *(EntityID*)eina_inarray_nth(pd->future->parent, target);
      break;
      case 1:
         return *(EntityID*)eina_inarray_nth(pd->present->parent, target);
      break;
      case 2:
         return *(EntityID*)eina_inarray_nth(pd->past->parent, target);
      break;
      default:
         return ULONG_NULL;
      break;
   }
}

EOLIAN static void
_engineer_scene_entity_siblingnext_set(Eo *obj, Engineer_Scene_Data *pd,
        EntityID target, EntityID siblingnext)
{
   target = engineer_scene_entity_index_get(obj, target);
   eina_inarray_replace_at(pd->future->siblingnext, target, &siblingnext);
}

EOLIAN static EntityID
_engineer_scene_entity_siblingnext_get(Eo *obj, Engineer_Scene_Data *pd,
        EntityID target)
{
   target = engineer_scene_entity_index_get(obj, target);
   return *(EntityID*)eina_inarray_nth(pd->future->siblingnext, target);
}

EOLIAN static void
_engineer_scene_entity_siblingprev_set(Eo *obj, Engineer_Scene_Data *pd,
        EntityID target, EntityID siblingprev)
{
   target = engineer_scene_entity_index_get(obj, target);
   eina_inarray_replace_at(pd->future->siblingprev, target, &siblingprev);
}

EOLIAN static EntityID
_engineer_scene_entity_siblingprev_get(Eo *obj, Engineer_Scene_Data *pd,
        EntityID target)
{
   target = engineer_scene_entity_index_get(obj, target);
   return *(EntityID*)eina_inarray_nth(pd->future->siblingprev, target);
}

EOLIAN static void
_engineer_scene_entity_firstentity_set(Eo *obj, Engineer_Scene_Data *pd,
        EntityID target, EntityID entity)
{
   target = engineer_scene_entity_lookup(obj, target);
   eina_inarray_replace_at(pd->future->firstentity, target, &entity);
}

EOLIAN static EntityID
_engineer_scene_entity_firstentity_get(Eo *obj, Engineer_Scene_Data *pd,
        EntityID target)
{
   target = engineer_scene_entity_lookup(obj, target);
   return *(EntityID*)eina_inarray_nth(pd->future->firstentity, target);
}

EOLIAN static void
_engineer_scene_entity_firstcomponent_set(Eo *obj, Engineer_Scene_Data *pd,
        EntityID target, ComponentID component)
{
   target = engineer_scene_entity_lookup(obj, target);
   eina_inarray_replace_at(pd->future->firstcomponent, target, &component);
}

EOLIAN static ComponentID
_engineer_scene_entity_firstcomponent_get(Eo *obj, Engineer_Scene_Data *pd,
        EntityID target)
{
   target = engineer_scene_entity_lookup(obj, target);
   return *(ComponentID*)eina_inarray_nth(pd->future->firstcomponent, target);
}

EOLIAN static Eina_Inarray *
_engineer_scene_entity_inbox_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        EntityID entityid)
{
   return eina_inarray_nth(pd->present->inbox, *(uint64_t*)eina_hash_find(pd->lookup, &entityid));
}

EOLIAN static Eina_Inarray *
_engineer_scene_entity_outbox_get(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        EntityID entityid)
{
   return eina_inarray_nth(pd->present->outbox, *(uint64_t*)eina_hash_find(pd->lookup, &entityid));
}

/*** Entity Services API (Not for external use.) ***/

EOLIAN static Eina_Bool
_engineer_scene_entity_factory(Eo *obj, Engineer_Scene_Data *pd,
        EntityID newid, EntityID parent)
{
   Engineer_Scene_Frame *frame;
   Eina_Inarray         *box;
   Index                 index;
   uint64_t              buffer;

   buffer = ULONG_NULL;
   if(engineer_scene_entity_index_get(obj, newid) == (Index)ULONG_NULL)
   {
      //eina_inarray_push(pd->history, eina_inarray_new(sizeof(uint64_t), 0));
      index = eina_inarray_push(pd->id, &newid);
      engineer_scene_entity_index_set(obj, newid, index);

      //name = eina_stringshare_printf("%s", name);
      EINA_INARRAY_FOREACH(pd->buffer, frame)
      {
         //eina_inarray_push(frame->name,           &name);
         eina_inarray_push(frame->parent,         &parent);
         eina_inarray_push(frame->siblingnext,    &newid);
         eina_inarray_push(frame->siblingprev,    &newid);
         eina_inarray_push(frame->firstcomponent, &buffer);
         eina_inarray_push(frame->firstentity,    &buffer);
         index = 0;
         box = eina_inarray_new(sizeof(uint64_t), 0);
         eina_inarray_push(box, &index);
         eina_inarray_push(frame->outbox, &box);
         box = eina_inarray_new(sizeof(uint64_t), 0);
         eina_inarray_push(box, &index);
         eina_inarray_push(frame->inbox, &box);
      }
      engineer_scene_entity_attach(obj, newid, parent);

      printf("Entity Created. | Index: %ld, EntityID: %ld, Parent: %ld, NextSib: %ld, PrevSib: %ld\n",
         index, newid, parent, newid, newid);
   }

   return EINA_TRUE;
}

/*** Entity Method API ***/

EOLIAN static EntityID
_engineer_scene_entity_create(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        EntityID sender, EntityID parent)
{
   Eo *node;
   EntityID newid;

   node  = efl_parent_get(obj);
   newid = engineer_node_entity_id_use(node);

   engineer_scene_notify_entity_create(obj, sender, newid, parent);

   return newid;
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
*/
EOLIAN static void
_engineer_scene_entity_attach(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        EntityID target, EntityID newparent)
{
   uint64_t buffer, targetnext, targetprev, oldparent, firstentity;

   if (target == (EntityID)ULONG_NULL || newparent == (EntityID)ULONG_NULL) return;

   targetnext  = engineer_scene_entity_siblingnext_get(obj, target);
   targetprev  = engineer_scene_entity_siblingprev_get(obj, target);
   oldparent   = engineer_scene_entity_parent_get(obj, target, 0);
   firstentity = engineer_scene_entity_firstentity_get(obj, oldparent);

   // Check to see if this Entity has it's relationship data defined.
   if (oldparent == ULONG_NULL || targetnext == ULONG_NULL || targetprev == ULONG_NULL) return;

   // Check to see if the target is the old parents first child.
   if ((uint64_t)target == firstentity)
   {
      engineer_scene_entity_firstentity_set(obj, oldparent, targetnext);
   }

   // Check to see if the old parent has any children.
   if (firstentity != ULONG_NULL)
   {
      // Check to see if the old parent has only one child Entity.
      if (engineer_scene_entity_siblingnext_get(obj, firstentity) ==
          engineer_scene_entity_siblingprev_get(obj, firstentity)  )
      {
         buffer = ULONG_NULL;
         engineer_scene_entity_firstentity_set(obj, oldparent, buffer);
      }
      else // relink the remaining child Entities.
      {
         engineer_scene_entity_siblingnext_set(obj, targetprev, targetnext);
         engineer_scene_entity_siblingprev_set(obj, targetnext, targetprev);
      }
   }

   // Set the new parent EntityID for the target Entity.
   engineer_scene_entity_parent_set(obj, target, newparent);

   // Check to see if new parent has any children. If not, set up the first child properly.
   if (engineer_scene_entity_firstentity_get(obj, newparent) == (EntityID)ULONG_NULL)
   {
      engineer_scene_entity_firstentity_set(obj, newparent, target);

      engineer_scene_entity_siblingnext_set(obj, target, target);
      engineer_scene_entity_siblingprev_set(obj, target, target);
   }
   else // add the target Entity to the back end of the new parent's child list.
   {
      firstentity = engineer_scene_entity_firstcomponent_get(obj, newparent);
      targetnext  = engineer_scene_entity_siblingnext_get(obj, firstentity);
      targetprev  = engineer_scene_entity_siblingprev_get(obj, firstentity);

      engineer_scene_entity_siblingnext_set(obj, target,
         engineer_scene_entity_siblingnext_get(obj, targetprev));
      engineer_scene_entity_siblingprev_set(obj, target,
         engineer_scene_entity_siblingprev_get(obj, targetnext));

      engineer_scene_entity_siblingnext_set(obj, targetprev, target);
      engineer_scene_entity_siblingprev_set(obj, targetnext, target);
   }
}

EOLIAN ComponentID
_engineer_scene_entity_component_search(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        EntityID entityid, ClassLabel target)
{
   Engineer_Component_Class *class;
   Eo *module, *node = efl_parent_get(obj);
   uint64_t first, component, classid, currentid;

   first = engineer_scene_entity_firstcomponent_get(obj, entityid);
   classid = engineer_hash_from_string(target, 242424);
   if (classid == (uint64_t)engineer_node_component_classid_get(node, first)) return first;
   class = engineer_node_component_class_get(node, classid);

   module    = engineer_scene_module_get(obj, class);
   component = class->component_siblingnext_get(module, first, 1);
   while(component != first)
   {
      currentid = engineer_node_component_classid_get(node, component);
      if (currentid == classid) return component;
      class     = engineer_node_component_class_get(node, currentid);

      module    = engineer_scene_module_get(obj, class);
      component = class->component_siblingnext_get(module, component, 1);
   }
   return ULONG_NULL;
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

/*** Component Service API (Wrapper Methods, Not for external use.) ***/

EOLIAN static Eina_Bool
_engineer_scene_component_factory(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        ComponentID target, EntityID parent, Data *payload)
{
   Eo *node, *module;
   Engineer_Component_Class *class;

   node   = efl_parent_get(obj);
   class  = engineer_node_component_class_get(node, target);
   module = engineer_scene_module_get(obj, class);

   class->component_factory(module, target, parent, payload);

   return EINA_TRUE;
}

/*** Component Method API (Wrapper Methods) ***/

EOLIAN static ComponentID
_engineer_scene_component_create(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        EntityID sender, ClassLabel classlabel, EntityID parent, Data *payload)
{
   Eo *node;
   uint64_t classid, newid;
   Engineer_Component_Class *class;

   classid = engineer_hash_murmur3(classlabel, strlen(classlabel), 242424);

   node  = efl_parent_get(obj);
   newid = engineer_node_component_id_use(node);

   engineer_node_component_classid_set(node, newid, classid);
   class = engineer_node_component_class_get(node, newid);
   engineer_scene_notify_component_create(obj, sender, class, newid, parent, payload);

   return newid;
}

EOLIAN static void
_engineer_scene_component_attach(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        ComponentID target, EntityID newparent)
{
   Eo *node, *module;
   Engineer_Component_Class *class;

   node   = efl_parent_get(obj);
   class  = engineer_node_component_class_get(node, target);
   module = engineer_scene_module_get(obj, class);

   class->component_attach(module, target, newparent);
}

EOLIAN static EntityID
_engineer_scene_component_parent_get(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        ComponentID target, uint64_t offset)
{
   Eo *node, *module;
   Engineer_Component_Class *class;

   node   = efl_parent_get(obj);
   class  = engineer_node_component_class_get(node, target);
   module = engineer_scene_module_get(obj, class);

   return class->component_parent_get(module, target, offset);
}

EOLIAN static State *
_engineer_scene_component_state_get(Eo *obj, Engineer_Scene_Data *pd EINA_UNUSED,
        ComponentID target, StateLabel key)
{
   Eo *node, *module;
   Engineer_Component_Class *class;

   node   = efl_parent_get(obj);
   class  = engineer_node_component_class_get(node, target);
   module = engineer_scene_module_get(obj, class);

   return class->component_state_get(module, target, key);
}

/*** Scene Notification Requests ***/

EOLIAN static void
_engineer_scene_notify_event(Eo *obj, Engineer_Scene_Data *pd,
        ComponentID sender, EntityID reciever, EventID type, Payload *payload, uint64_t size)
{
   Eina_Inarray *inbox;
   uint64_t     *input;
   uint64_t      index, count;

   index = engineer_scene_entity_lookup(obj, reciever);
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
_engineer_scene_notify_event_ancestors(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t entityid, uint32_t response, uint32_t size, void *payload)
{
}

EOLIAN static void
_engineer_scene_notify_event_descendants(Eo *obj, Engineer_Scene_Data *pd,
        uint64_t entityid, uint64_t response, uint32_t size, void *payload)
{
}
*/
EOLIAN static void
_engineer_scene_notify_entity_create(Eo *obj, Engineer_Scene_Data *pd, EntityID sender,
        EntityID entityid, EntityID parent)
{
   Eina_Inarray *outbox;
   uint64_t type, *input;
   uint32_t index;

   type   = 0;
   index  = engineer_scene_entity_index_get(obj, sender);
   outbox = *(Eina_Inarray**)eina_inarray_nth(pd->future->outbox, index);

   eina_inarray_push(outbox, &sender);
   eina_inarray_push(outbox, &type);
   eina_inarray_push(outbox, &entityid);
   eina_inarray_push(outbox, &parent);

   input = eina_inarray_nth(outbox, 0);
   *input += 1;
}

EOLIAN static void
_engineer_scene_notify_component_create(Eo *obj, Engineer_Scene_Data *pd, EntityID sender,
        Engineer_Component_Class *class, ComponentID componentid, EntityID parent, Data *payload)
{
   Eina_Inarray *outbox;
   uint64_t empty, type, *input;
   uint32_t index, count;

   empty  = 0;
   index  = engineer_scene_entity_lookup(obj, componentid);
   outbox = *(Eina_Inarray**)eina_inarray_nth(pd->future->outbox, index);

   eina_inarray_push(outbox, &sender);
   eina_inarray_push(outbox, &type);
   eina_inarray_push(outbox, &class->id);
   eina_inarray_push(outbox, &componentid);
   eina_inarray_push(outbox, &parent);

   if(payload != NULL)
   for (count = 0; count < class->size; count++)
      eina_inarray_push(outbox, payload + (count * 8));
   else
   for (count = 0; count < class->size; count++)
      eina_inarray_push(outbox, &empty);

   input = eina_inarray_nth(outbox, 0);
   *input += 1;
}

#include "engineer_scene.eo.c"
