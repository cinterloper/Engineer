#include "engineer_module.h"

Eo *
engineer_module_new(Eo *parent)
{
   Eo *module = efl_add(ENGINEER_MODULE_CLASS, parent);
                  //engineer_scene_name_set(efl_added, name));

   return module;
}

uint64_t
engineer_module_classid(void)
{
   printf("Engineer Module ClassID Check: "STRINGIFY(COMPONENT)".\n");
   return engineer_hash_murmur3(STRINGIFY(COMPONENT), strlen(STRINGIFY(COMPONENT)), 242424);
}

/*** Constructors ***/

EOLIAN static Efl_Object *
_engineer_module_efl_object_constructor(Eo *obj, Engineer_Module_Data *pd EINA_UNUSED)
{
   return efl_constructor(efl_super(obj, ENGINEER_MODULE_CLASS));
}

Efl_Object *
_engineer_module_efl_object_finalize(Eo *obj, Engineer_Module_Data *pd)
{
   obj = efl_finalize(efl_super(obj, ENGINEER_MODULE_CLASS));

   static const
   Engineer_Module_Frame  blank;
   Engineer_Module_Frame *frame;
   Engineer_Component     eventid EINA_UNUSED;
   uint64_t               hash    EINA_UNUSED;
   uint64_t               index   EINA_UNUSED;

   // Create the State Field Enumeration Hash Lookup Table.
   pd->fields = eina_hash_int64_new(NULL);
   #define FIELD(key, type) \
      hash  = engineer_hash_murmur3(STRINGIFY(key), strlen(STRINGIFY(key)), 242424); \
      index = key##STATE; \
      eina_hash_add(pd->fields, &hash, (uint64_t*)index);
   STATE
   #undef FIELD

   // Create the Event Enumeration Hash Lookup Table.
   pd->events = eina_hash_int64_new(NULL);
   #define EVENT(key) \
      hash  = engineer_hash_murmur3(STRINGIFY(key), strlen(STRINGIFY(key)), 242424); \
      index = key##EVENT; \
      eina_hash_add(pd->events, &hash, (uint64_t*)index);
   EVENTS
   #undef EVENT

   // Create and initialize the space (3 frames) needed to iterate our timeline.
   pd->buffer = eina_inarray_new(sizeof(Engineer_Module_Frame), 3);
   eina_inarray_push(pd->buffer, &blank);
   eina_inarray_push(pd->buffer, &blank);
   eina_inarray_push(pd->buffer, &blank);

   // Initialize the inarrays needed to store the Frame's contents.
   EINA_INARRAY_FOREACH(pd->buffer, frame)
   {
      frame->name = eina_inarray_new(sizeof(Eina_Stringshare*), 0);

      frame->parent      = eina_inarray_new(sizeof(uint64_t), 0);
      frame->siblingnext = eina_inarray_new(sizeof(uint64_t), 0);
      frame->siblingprev = eina_inarray_new(sizeof(uint64_t), 0);

      #define FIELD(key, type) \
         type##NEW(&frame->key);
      STATE
      #undef FIELD
   }

   // We need to set up our timeline pointers for the first time here.
   pd->future  = eina_inarray_nth(pd->buffer, 0);
   pd->present = eina_inarray_nth(pd->buffer, 1);
   pd->past    = eina_inarray_nth(pd->buffer, 2);

   pd->id     = eina_inarray_new(sizeof(uint64_t), 0);
   pd->lookup = eina_hash_int64_new(NULL);

   return obj;
}

EOLIAN static void
_engineer_module_efl_object_destructor(Eo *obj, Engineer_Module_Data *pd EINA_UNUSED)
{
   efl_destructor(efl_super(obj, ENGINEER_MODULE_CLASS));
}

EOLIAN static Eina_Bool
_engineer_module_update(Eo *obj, Engineer_Module_Data *pd)
{
   printf("Engineer Module Update Checkpoint.\n");
   printf("Murmur3 Test Hash Output 3: %ld.\n", engineer_module_classid());
   Engineer_Component     buffer;
   Engineer_Module_Frame *frame;
   uint64_t               index;

   // Cycle the timeline to get to our next frame.
   frame       = pd->past;
   pd->past    = pd->present;
   pd->present = pd->future;
   pd->future  = frame;

   // Copy over our present Module Component metadata to the future Frame.
   for(index = 0; index < eina_inarray_count(pd->id); index++)
   {
      #define METADATA \
         FIELD(name) \
         FIELD(parent) \
         FIELD(siblingnext) \
         FIELD(siblingprev)

      #define FIELD(key) \
         eina_inarray_replace_at(pd->future->key, index, eina_inarray_nth(pd->present->key, index));
      METADATA
      #undef FIELD

      #define FIELD(key, type) \
         type##COPY(&pd->present->key, &pd->future->key, index);
      STATE
      #undef FIELD

      #undef METADATA
   }

   // Alter the Scenegraph according to the present Entities' outboxen.
   index = 0;
   Eina_Inarray *inbox;
   uint64_t     *parent;
   EINA_INARRAY_FOREACH(pd->present->parent, parent)
   {
      // Set up our buffer here.
      engineer_module_cache_read(obj, &buffer, index);

      inbox = engineer_scene_entity_inbox_get(efl_parent_get(obj), *parent);
      engineer_module_dispatch(obj, &buffer, inbox);

      // Run our modules update() method here.
      engineer_module_component_update(obj, index, &buffer);

      // Flush our buffer here
      engineer_module_cache_write(obj, &buffer, index);
      index += 1;
   }
   return ECORE_CALLBACK_RENEW;
}

EOLIAN static void
_engineer_module_dispatch(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        Engineer_Component *buffer EINA_UNUSED, Eina_Inarray *inbox EINA_UNUSED)
{
   uint64_t count, offset, current, event, size;
   Component_Event type;

   count  = *(uint64_t*)eina_inarray_nth(inbox, 0);
   offset = 1;
   for(current = 0; current < count; current++)
   {
      event = *(uint64_t*)eina_inarray_nth(inbox, offset + 1);
      type  =  (uint64_t)eina_hash_find(pd->events, (uint64_t*)event);
      size  = *(uint64_t*)eina_inarray_nth(inbox, offset + 2);
      switch(type)
      {
         #define EVENT(key) \
            case key##EVENT: \
            event(key, buffer, eina_inarray_nth(inbox, offset + 3), size); \
            break;
         EVENTS
         #undef EVENT
         case nullEVENT:
         break;
      }
      offset += (size + 3);
   }
}

/*** Module Notification Wrappers ***/
/*
EOLIAN static void
_engineer_module_notify_event(Eo *obj, Engineer_Module_Data *pd,
        EntityID target, EntityID sender, EventLabel *type, void *payload, uint64_t size)
{
   Eo *scene;
   uint64_t eventid;

   scene   = efl_parent_get(obj);
   sender  = *(uint64_t*)eina_inarray_nth(pd->id, sender);
   eventid = engineer_hash_murmur3(type, strlen(type), 242424);
   engineer_scene_notify_event(scene, target, sender, eventid, payload, size);
}

EOLIAN static EntityID
_engineer_module_notify_entity_create(Eo *obj, Engineer_Module_Data *pd,
        EntityID parent, Index senderindex)
{
   Eo *scene = efl_parent_get(obj);
   Eo *node  = efl_parent_get(scene);
   uint64_t senderid, entityid;

   senderid = *(EntityID*)eina_inarray_nth(pd->future->parent, senderindex);
   entityid = engineer_node_entity_id_use(node);

   engineer_scene_entity_create(scene, senderid, entityid, parent);

   return entityid;
}

*/
/*** Module Cache Access Methods ***/

EOLIAN static uint64_t
_engineer_module_cache_sizeof(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED)
{
   uint64_t counter = 0;
   #define FIELD(key, type) \
      type##SIZE(&counter);
   STATE
   #undef FIELD
   return counter;
}

EOLIAN static void
_engineer_module_cache_read(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd,
        Engineer_Component *buffer, Index index)
{
   printf("Engineer Module Cache Read Checkpoint 1. \n");
   buffer->name = *(char**)eina_inarray_nth(pd->present->name, index);
   printf("Engineer Module Cache Read Checkpoint 2. \n");
   buffer->parent      = *(uint64_t*)eina_inarray_nth(pd->present->parent,      index);
   buffer->nextsibling = *(uint64_t*)eina_inarray_nth(pd->present->siblingnext, index);
   buffer->prevsibling = *(uint64_t*)eina_inarray_nth(pd->present->siblingprev, index);
   printf("Engineer Module Cache Read Checkpoint 3. \n");
   #define FIELD(key, type) \
      type##READ(&pd->present->key, &buffer->key, index);
   STATE
   #undef FIELD
   printf("Engineer Module Cache Read Checkpoint 4. \n");
}

EOLIAN static void
_engineer_module_cache_write(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        Engineer_Component *buffer EINA_UNUSED, Index index EINA_UNUSED)
{
   #define FIELD(key, type) \
      type##WRITE(&pd->future->key, &buffer->key, index);
   STATE
   #undef FIELD
}

/*** Component Metadata Getters/Setters ***/

EOLIAN static Index
_engineer_module_component_lookup(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd,
        ComponentID componentid)
{
   return (Index)eina_hash_find(pd->lookup, &componentid) - 1;
}

EOLIAN static void
_engineer_module_component_parent_set(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target, EntityID newparent)
{
   target = engineer_module_component_lookup(obj, target);
   eina_inarray_replace_at(pd->future->parent, target, &newparent);
}

EOLIAN static EntityID
_engineer_module_component_parent_get(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target)
{
   target = engineer_module_component_lookup(obj, target);
   return *(EntityID*)eina_inarray_nth(pd->future->parent, target);
}

EOLIAN static void
_engineer_module_component_siblingnext_set(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target, ComponentID newsibling)
{
   target = engineer_module_component_lookup(obj, target);
   eina_inarray_replace_at(pd->future->siblingnext, target, &newsibling);
}

EOLIAN static ComponentID
_engineer_module_component_siblingnext_get(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target)
{
   target = engineer_module_component_lookup(obj, target);
   return *(ComponentID*)eina_inarray_nth(pd->future->siblingnext, target);
}

EOLIAN static void
_engineer_module_component_siblingprev_set(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target, ComponentID newsibling)
{
   target = engineer_module_component_lookup(obj, target);
   eina_inarray_replace_at(pd->future->siblingprev, target, &newsibling);
}

EOLIAN static ComponentID
_engineer_module_component_siblingprev_get(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target)
{
   target = engineer_module_component_lookup(obj, target);
   return *(ComponentID*)eina_inarray_nth(pd->future->siblingprev, target);
}

/*** Component Services ***/

EOLIAN static Eina_Bool
_engineer_module_component_factory(Eo *obj, Engineer_Module_Data *pd,
        ComponentID newid, EntityID parent, Engineer_Component *template)
{
   Engineer_Module_Frame *frame;
   Index                  index;

   if(engineer_module_component_lookup(obj, newid) == UINT_NULL)
   {
      //eina_inarray_push(pd->history, eina_inarray_new(sizeof(uint64_t), 0));
      eina_inarray_push(pd->id, &newid);
      index = eina_inarray_count(pd->id) - 1;
      eina_hash_add(pd->lookup, &newid, (void*)index);

      template->name = eina_stringshare_printf("%s", template->name);
      EINA_INARRAY_FOREACH(pd->buffer, frame)
      {
         eina_inarray_push(frame->name,           &template->name);
         eina_inarray_push(frame->parent,         &parent);
         eina_inarray_push(frame->siblingnext,    &newid);
         eina_inarray_push(frame->siblingprev,    &newid);

         #define FIELD(key, type) \
            type##PUSH(&frame->key, &template->key);
         STATE
         #undef FIELD
      }
      engineer_module_component_attach(obj, newid, parent);

      printf("Component Create Checkpoint. CID: %ld, Parent: %ld, NextSib: %ld, PrevSib: %ld, Name: %s\n",
         newid, parent, newid, newid, template->name);
   }

   return EINA_TRUE;
}

/*** Component Methods ***/

EOLIAN static ComponentID
_engineer_module_component_create(Eo *obj, Engineer_Module_Data *pd EINA_UNUSED,
        EntityID sender, Engineer_Component_Class *class, EntityID parent, void *payload)
{
   Eo *scene = efl_parent_get(obj);

   return engineer_scene_component_create(scene, sender, class, parent, payload);
}

EOLIAN static void
_engineer_module_component_attach(Eo *obj, Engineer_Module_Data *pd EINA_UNUSED,
       ComponentID target, EntityID newparent)
{
   uint64_t buffer, targetnext, targetprev, oldparent, firstcom;
   Eo *scene = efl_parent_get(obj);

   if (target == UINT_NULL || newparent == UINT_NULL) return;

   targetnext = engineer_module_component_siblingnext_get(obj, target);
   targetprev = engineer_module_component_siblingprev_get(obj, target);
   oldparent  = engineer_module_component_parent_get(obj, target);
   firstcom   = engineer_scene_entity_firstcomponent_get(scene, oldparent);

   // Check to see if this Component has it's relationship data defined.
   if (targetnext == UINT_NULL || targetprev == UINT_NULL || oldparent == UINT_NULL) return;

   // Check to see if the target is the old parents first child component.
   // If so, reset the old parents first child to the next component sibling.
   if ((uint64_t)target == firstcom)
   {
      engineer_scene_entity_firstcomponent_set(scene, oldparent, targetnext);
   }

   // Check to see if the old parent has only one child Component.
   // If so, set the firstcomponent entry of the parent to the null stub.
   if (engineer_module_component_siblingnext_get(obj, firstcom) ==
       engineer_module_component_siblingprev_get(obj, firstcom)  )
   {
      buffer = UINT_NULL;
      engineer_scene_entity_firstcomponent_set(scene, oldparent, buffer);
   }
   else // relink the remaining child Entities.
   {
      engineer_module_component_siblingnext_set(obj, targetprev, targetnext);
      engineer_module_component_siblingprev_set(obj, targetnext, targetprev);
   }

   // Set the new parent EntityID for the target Entity.
   engineer_module_component_parent_set(obj, target, newparent);

   // Check to see if new parent has any children. If not, set up the first child properly.
   if (engineer_scene_entity_firstcomponent_get(scene, newparent) == UINT_NULL)
   {
      engineer_scene_entity_firstcomponent_set(scene, newparent, target);

      engineer_module_component_siblingnext_set(obj, target, target);
      engineer_module_component_siblingprev_set(obj, target, target);
   }
   else // add the target Component to the back end of the new parent's components list.
   {
      firstcom   = engineer_scene_entity_firstcomponent_get(scene, newparent);
      targetnext = engineer_module_component_siblingnext_get(obj, firstcom);
      targetprev = engineer_module_component_siblingprev_get(obj, firstcom);

      engineer_module_component_siblingnext_set(obj, target,
         engineer_module_component_siblingnext_get(obj, targetprev));
      engineer_module_component_siblingprev_set(obj, target,
         engineer_module_component_siblingprev_get(obj, targetnext));

      engineer_module_component_siblingnext_set(obj, targetprev, target);
      engineer_module_component_siblingprev_set(obj, targetnext, target);
   }
}

EOLIAN static void *
_engineer_module_component_state_get(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target, StateLabel key)
{
   uint64_t fieldid, index EINA_UNUSED;
   Eo *scene, *node;
   void *result;

   scene = efl_parent_get(obj);
   node  = efl_parent_get(scene);

   if((uint64_t)engineer_node_component_classid_get(node, target) == engineer_module_classid())
   {
      Component_State field;

      fieldid = engineer_hash_murmur3(key, strlen(key), 242424);
      field   = (Component_State)eina_hash_find(pd->fields, (uint64_t*)fieldid);
      index   = engineer_module_component_lookup(obj, target);
      switch(field)
      {
         #define FIELD(key, type) \
            case key##STATE: \
            result = malloc(sizeof(type)); \
            type##READ(&pd->present->key, result, index); \
            break;
         STATE
         #undef FIELD
         case nullSTATE:
           result = NULL;
         break;
         default:
           result = NULL;
      }

      return result;
   }
   else return engineer_scene_component_state_get(scene, target, key);
}

#include "engineer_module.eo.c"

