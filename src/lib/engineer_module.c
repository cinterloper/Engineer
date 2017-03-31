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
   uint64_t               hash  EINA_UNUSED;
   uint64_t               index EINA_UNUSED;

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
   #define EVENT(key, size) \
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

      frame->parent      = eina_inarray_new(sizeof(EntityID),    0);
      frame->siblingnext = eina_inarray_new(sizeof(ComponentID), 0);
      frame->siblingprev = eina_inarray_new(sizeof(ComponentID), 0);

      #define FIELD(key, type) \
         type##NEW(&frame->key);
      STATE
      #undef FIELD
   }

   // We need to set up our timeline pointers for the first time here.
   pd->future  = eina_inarray_nth(pd->buffer, 0);
   pd->present = eina_inarray_nth(pd->buffer, 1);
   pd->past    = eina_inarray_nth(pd->buffer, 2);

   pd->id     = eina_inarray_new(sizeof(ComponentID), 0);
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
   //printf("Murmur3 Test Hash Output: %ld.\n", engineer_module_classid());
   printf("Engineer Module Check: "STRINGIFY(COMPONENT)".\n");
   Engineer_Component     buffer;
   Engineer_Module_Frame *frame;
   uint64_t               this, index;

   // Cycle the timeline to get to our next frame.
   frame       = pd->past;
   pd->past    = pd->present;
   pd->present = pd->future;
   pd->future  = frame;

   // Copy over our present Module Component metadata to the future Frame.
   printf("Module metadata Copy Checkpoint. Component Count: %d\n", eina_inarray_count(pd->id));
   for(index = 0; index < eina_inarray_count(pd->id); index++)
   {
      // FIELD(name)
      #define METADATA \
         FIELD(parent) \
         FIELD(siblingnext) \
         FIELD(siblingprev)

      #define FIELD(key) \
         eina_inarray_replace_at(pd->future->key, index, eina_inarray_nth(pd->present->key, index));
      METADATA
      #undef FIELD

      #undef METADATA
   }

   // Alter the Scenegraph according to the present Entities' inboxen.
   index = 0;
   Eina_Inarray *inbox;
   uint64_t     *parent;
   EINA_INARRAY_FOREACH(pd->present->parent, parent)
   {
      this = *(ComponentID*)eina_inarray_nth(pd->id, index);

      // Set up our buffer here.
      engineer_module_cache_read(obj, &buffer, index);

      inbox = engineer_scene_entity_inbox_get(efl_parent_get(obj), *parent);
      engineer_module_dispatch(obj, &buffer, inbox);

      // Run our modules update() method here.
      engineer_module_component_update(obj, this, index, &buffer);

      // Flush our buffer here
      engineer_module_cache_write(obj, &buffer, index);
      index += 1;
   }
   return ECORE_CALLBACK_RENEW;
}

EOLIAN static void
_engineer_module_dispatch(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd,
        Engineer_Component *buffer EINA_UNUSED, Eina_Inarray *inbox)
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
         #define EVENT(key, arraysize) \
            case key##EVENT:                                            \
               event(key, buffer, eina_inarray_nth(inbox, offset + 3)); \
            break;
         EVENTS
         #undef EVENT
         case nullEVENT:
         break;
      }
      offset += (size + 3);
   }
}

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
   //buffer->name = *(char**)eina_inarray_nth(pd->present->name, index);
   buffer->parent      = *(EntityID*)eina_inarray_nth(pd->present->parent,         index);
   buffer->nextsibling = *(ComponentID*)eina_inarray_nth(pd->present->siblingnext, index);
   buffer->prevsibling = *(ComponentID*)eina_inarray_nth(pd->present->siblingprev, index);

   #define FIELD(key, type) \
      type##READ(&pd->present->key, &buffer->key, index);
   STATE
   #undef FIELD
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

/*** Event Services ***/

EOLIAN static uint64_t
_engineer_module_event_sizeof(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        EventID event)
{
   uint64_t result = 0;

   switch(event)
   {
      #define EVENT(key, size) \
         case key##EVENT:      \
            result = size;     \
         break;
      EVENTS
      #undef EVENT
   }
   return result;
}

/*** Component Services ***/

EOLIAN static Eina_Bool
_engineer_module_component_factory(Eo *obj, Engineer_Module_Data *pd,
        ComponentID newid, EntityID parent, Engineer_Component *template)
{
   Eo *scene = efl_parent_get(obj);
   Index index;
   EntityID blank = ULONG_NULL;

   if(engineer_module_component_index_get(obj, newid) == (Index)ULONG_NULL)
   {
      //eina_inarray_push(pd->history, eina_inarray_new(sizeof(uint64_t), 0));
      index = eina_inarray_push(pd->id, &newid);

      engineer_module_component_index_set(obj, newid, index);

      eina_inarray_push(pd->future->parent,      &blank);
      eina_inarray_push(pd->future->siblingnext, &blank);
      eina_inarray_push(pd->future->siblingprev, &blank);

      engineer_scene_component_attach(scene, newid, parent);

      eina_inarray_push(pd->present->parent,      eina_inarray_nth(pd->future->parent,      index));
      eina_inarray_push(pd->present->siblingnext, eina_inarray_nth(pd->future->siblingnext, index));
      eina_inarray_push(pd->present->siblingprev, eina_inarray_nth(pd->future->siblingprev, index));

      engineer_module_component_awake(obj, newid, index, template);

      eina_inarray_push(pd->past->parent,      eina_inarray_nth(pd->present->parent,      index));
      eina_inarray_push(pd->past->siblingnext, eina_inarray_nth(pd->present->siblingnext, index));
      eina_inarray_push(pd->past->siblingprev, eina_inarray_nth(pd->present->siblingprev, index));

      // Push our awake() processed template data to the active frames. (Was type##WRITE)
      #define FIELD(key, type)                          \
         type##PUSH(&pd->future->key,  &template->key); \
         type##PUSH(&pd->present->key, &template->key); \
         type##PUSH(&pd->past->key,    &template->key);
      STATE
      #undef FIELD

      printf("Component Created. | ComponentID: %ld, Parent: %ld, NextSib: %ld, PrevSib: %ld\n",
         newid,
         parent,
         *(ComponentID*)eina_inarray_nth(pd->present->siblingnext, index),
         *(ComponentID*)eina_inarray_nth(pd->present->siblingprev, index)
      );
   }

   return EINA_TRUE;
}

EOLIAN static void
_engineer_module_component_index_set(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd,
        ComponentID componentid, Index index)
{
    componentid += 1;
    index       += 1;
    eina_hash_add(pd->lookup, &componentid, (void*)index);
}

EOLIAN static Index
_engineer_module_component_index_get(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd,
        ComponentID componentid)
{
   Index index = (Index)-1;

   componentid += 1;
   index    += (Index)eina_hash_find(pd->lookup, &componentid);

   return index;
}

EOLIAN static void
_engineer_module_component_parent_set(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target, EntityID newparent)
{
   target = engineer_module_component_index_get(obj, target);
   eina_inarray_replace_at(pd->future->parent, target, &newparent);
}

EOLIAN static EntityID
_engineer_module_component_parent_get(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target, uint64_t offset)
{
   target = engineer_module_component_index_get(obj, target);

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
_engineer_module_component_siblingnext_set(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target, ComponentID newsibling)
{
   target = engineer_module_component_index_get(obj, target);
   eina_inarray_replace_at(pd->future->siblingnext, target, &newsibling);
}

EOLIAN static ComponentID
_engineer_module_component_siblingnext_get(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target, uint64_t offset)
{
   target = engineer_module_component_index_get(obj, target);

   switch(offset)
   {
      case 0:
         return *(ComponentID*)eina_inarray_nth(pd->future->siblingnext, target);
      break;
      case 1:
         return *(ComponentID*)eina_inarray_nth(pd->present->siblingnext, target);
      break;
      case 2:
         return *(ComponentID*)eina_inarray_nth(pd->past->siblingnext, target);
      break;
      default:
         return ULONG_NULL;
      break;
   }
}

EOLIAN static void
_engineer_module_component_siblingprev_set(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target, ComponentID newsibling)
{
   target = engineer_module_component_index_get(obj, target);
   eina_inarray_replace_at(pd->future->siblingprev, target, &newsibling);
}

EOLIAN static ComponentID
_engineer_module_component_siblingprev_get(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target, uint64_t offset)
{
   target = engineer_module_component_index_get(obj, target);

   switch(offset)
   {
      case 0:
         return *(ComponentID*)eina_inarray_nth(pd->future->siblingprev, target);
      break;
      case 1:
         return *(ComponentID*)eina_inarray_nth(pd->present->siblingprev, target);
      break;
      case 2:
         return *(ComponentID*)eina_inarray_nth(pd->past->siblingprev, target);
      break;
      default:
         return ULONG_NULL;
      break;
   }
}

EOLIAN static void *
_engineer_module_component_state_get(Eo *obj, Engineer_Module_Data *pd,
        ComponentID target, StateLabel key)
{
   uint64_t fieldid, index;
   void *result;
   Component_State field;

   fieldid = engineer_hash_murmur3(key, strlen(key), 242424);
   field   = (Component_State)eina_hash_find(pd->fields, &fieldid);
   index   = engineer_module_component_index_get(obj, target);
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

#include "engineer_module.eo.c"

