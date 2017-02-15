#include "engineer_module.h"

// All Modules are actually classes that inherit from the Engineer_Module class.
// All active Component data is held in a struct (tree) of linear arrays.

/*** Constructors ***/

EOLIAN static Efl_Object *
_engineer_module_efl_object_constructor(Eo *obj, Engineer_Module_Data *pd EINA_UNUSED)
{
   obj = efl_constructor(efl_super(obj, ENGINEER_MODULE_CLASS));
   return obj;
}

EOLIAN static Efl_Object *
_engineer_module_efl_object_finalize(Eo *obj, Engineer_Module_Data *pd)
{
   obj = efl_finalize(efl_super(obj, ENGINEER_MODULE_CLASS));

   uint index;
   Engineer_Module_Frame *frame, blank;

   pd->lookup = eina_hash_int64_new(NULL);

   // Initialize the memory needed to start our triple buffer and allocate it's contents.
   pd->buffer = eina_inarray_new(sizeof(Engineer_Module_Frame), 3);
   for (uint32_t count = 0; count < 3; count++)
   {
      memset(&blank, 0, sizeof(Engineer_Module_Frame));
      index = eina_inarray_push(pd->buffer, &blank);
      frame = eina_inarray_nth(pd->buffer, index);

      frame->id   = eina_inarray_new(sizeof(uint64_t), 0);
      frame->name = eina_inarray_new(sizeof(Eina_Stringshare*), 0);

      frame->parent      = eina_inarray_new(sizeof(uint64_t), 0);
      frame->siblingnext = eina_inarray_new(sizeof(uint64_t), 0);
      frame->siblingprev = eina_inarray_new(sizeof(uint64_t), 0);

      #define FIELD(KEY, TYPE) \
         TYPE##NEW(&frame->KEY);
      FIELDS
      #undef FIELD
   }

   pd->past    = eina_inarray_nth(pd->buffer, 0);
   pd->present = eina_inarray_nth(pd->buffer, 1);
   pd->future  = eina_inarray_nth(pd->buffer, 2);

   return obj;
}

EOLIAN static void
_engineer_module_efl_object_destructor(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED)
{
   efl_destructor(efl_super(obj, ENGINEER_MODULE_CLASS));
}

/*** Module iteration Handler ***/

EOLIAN static void
_engineer_module_iterate(Eo *obj, Engineer_Module_Data *pd)
{
   COMPONENT component;
   void *buffer;
   Eina_Inarray *inbox;
   uint32_t index, size, target, count, offset;
   uint64_t *parent;

   // Cycle our Module's Component iteration buffer.
   buffer      = pd->past;
   pd->past    = pd->present;
   pd->present = pd->future;
   pd->future  = buffer;

   // Copy over our present Module Component metadata to the future Frame.
   size = engineer_module_cache_sizeof(obj);
   uint64_t presentfield[size], futurefield[size];

   presentfield[0] = pd->present->name;
   presentfield[1] = pd->present->parent;
   presentfield[2] = pd->present->siblingnext;
   presentfield[3] = pd->present->siblingprev;
   index = 3;
   #define FIELD(KEY, TYPE) \
      index = engineer_type_TYPE_reference(presentfield, pd->present->KEY, index);
   FIELDS
   #undef FIELD

   futurefield[0] = pd->future->name;
   futurefield[1] = pd->future->parent;
   futurefield[2] = pd->future->siblingnext;
   futurefield[3] = pd->future->siblingprev;
   index = 3;
   #define FIELD(KEY, TYPE) \
      index = engineer_type_TYPE_reference(futurefield, pd->future->KEY, index);
   FIELDS
   #undef FIELD

   count = eina_inarray_count(pd->present->id);
   for (index = 0; index < size; index++)
   {
      for(target = 0; target < count; target++)
      {
         eina_inarray_replace_at(futurefield[index], target,
            eina_inarry_nth(presentfield[index], target));
      }
   }


   // Now iterate over each Component stored in this Module.
   index = 0;
   EINA_INARRAY_FOREACH(pd->present->parent, parent)
   {
      // Read our COMPONENT buffer from our module SoA.
      engineer_module_cache_read(obj, &component, index);

      // Find the Entity this component belongs to and import it's inbox,
      //    then respond to the notices in it.
      inbox  = engineer_scene_entity_inbox_get(efl_parent_get(obj), *parent);
      count  = *(uint64_t*)eina_inarray_nth(inbox, 0);
      offset = 1;
      for(uint32_t subindex = 0; subindex < count; subindex++)
      {
         engineer_module_respond(obj, inbox, offset);
      }

      // Run the update() function for this Module on the current Component.
      engineer_module_update(&component);

      // Write our COMPONENT data to our module SOA.
      engineer_module_cache_write(obj, &component, index);
      index += 1;
   }
}

EOLIAN static void
_engineer_module_respond(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        Eina_Inarray *inbox, uint32_t offset)
{
   index = 0;
   EINA_INARRAY_FOREACH(inbox, target)
   {
      // The first two bytes in our inbox array tell us how many notices we have recieved.
      count  = *(char*)eina_inarray_nth(target, 0) << 8;
      count += *(char*)eina_inarray_nth(target, 1);
      offset = 2;
      for(subindex = 0; subindex < count; subindex++)
      {
         // Layout of each note string: 0: Case/Size, 1->Remainder: Type Dependant Notice Data;
         switch(*(uint64_t*)eina_inarray_nth(target, offset))
         {
            //#define RESPONSE(KEY, SIZE) \
            //  case eina_hash_murmer3(STRINGIFY(KEY), strlen(STRINGIFY(KEY))): \
            //     response(KEY, data, payload); \
            //  break;
            //#undef RESPONSE
         }
      }
      index += 1;
   }
}

/*** Module Cache Methods ***/

EOLIAN static uint32_t
_engineer_module_cache_sizeof(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED)
{
   size = 4;
   #define FIELD(KEY, TYPE) \
      size += engineer_type_TYPE_sizeof();
   #undef FIELD

   return size;
}

EOLIAN static void
_engineer_module_cache_read(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        COMPONENT *buffer, uint32_t index)
{
   // Read our COMPONENT buffer from our module SoA.
   buffer->this        = *(uint64_t*)eina_inarray_nth(pd->present->id, index);
   buffer->name        = *(const char*)eina_inarray_nth(pd->present->name, index);
   buffer->parent      = *(uint64_t*)eina_inarray_nth(pd->present->parent, index);
   buffer->nextsibling = *(uint64_t*)eina_inarray_nth(pd->present->siblingnext, index);
   buffer->prevsibling = *(uint64_t*)eina_inarray_nth(pd->present->siblingprev, index);

   #define FIELD(KEY, TYPE) \
      TYPE##READ(KEY)
   FIELDS
   #undef FIELD
}

EOLIAN static void
_engineer_module_cache_write(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd EINA_UNUSED,
        COMPONENT *buffer, uint32_t index)
{
   // Write our COMPONENT buffer to our module SoA.
   #define FIELD(KEY, TYPE) \
       TYPE##WRITE(KEY)
   FIELDS
   #undef FIELD
}

/*** Component Methods ***/

EOLIAN static uint
_engineer_module_component_create(Eo *obj, Engineer_Module_Data *pd EINA_UNUSED,
        uint64_t id, uint64_t parent, COMPONENT *input)
{
   Engineer_Module_Frame *frame;
   uint64_t               index;

   if(engineer_module_component_lookup(obj, id) == NULL)
   {
      EINA_INARRAY_FOREACH(pd->buffer, frame)
      {
         eina_inarray_push(frame->id,             &id);
         eina_inarray_push(frame->name,           eina_stringshare_printf(STRINGIFY(SYMBOL));
         eina_inarray_push(frame->parent,         &parent);
         eina_inarray_push(frame->siblingnext,    &id);
         eina_inarray_push(frame->siblingprev,    &id);

         #define FIELD(KEY, TYPE) \
            engineer_module_type_TYPE_soa_push(frame->KEY, input->KEY);
         FIELDS
         #undef FIELD
      }
      index = eina_inarray_count(pd->future->id) - 1;

      engineer_module_component_parent_set(obj, id, parent);
      eina_inarray_push(pd->history, eina_inarray_new(sizeof(uint64_t), 0));
      eina_hash_add(pd->lookup, &id, &index);

      printf("Component Create Checkpoint. CID: %ld, Parent: %ld, Name: %s\n", id, parent, name);

      return EINA_TRUE;
   }
   else return EINA_FALSE;
}
/*
EOLIAN static void
_engineer_module_component_destroy(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        uint targetid EINA_UNUSED)
{
   // Remove the component from the cache if it's currently in there.
   // Then remove the database entry.
}

EOLIAN static void
_engineer_module_component_dispose(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED)
{
}

EOLIAN static void
_engineer_module_component_archive(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED ,
        uint target EINA_UNUSED)
{
}

EOLIAN static void
_engineer_module_component_recall(Eo *obj EINA_UNUSED, Engineer_Module_Data *pd EINA_UNUSED,
        uint target EINA_UNUSED)
{
}
*/
EOLIAN static uint32_t
_engineer_module_component_lookup(Eo *obj, Engineer_Module_Data *pd,
        uint64_t componentid)
{
   return eina_hash_find(pd->lookup, &componentid);
}
/*
EOLIAN static void
_engineer_module_component_cache_swap(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
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
*/
EOLIAN static void
_engineer_module_component_parent_set(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
        uint64_t target, uint64_t parent)
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
/*
EOLIAN static void
_engineer_module_component_sibling_swap(Eo *obj EINA_UNUSED, Engineer_Scene_Data *pd,
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
*/

#include "engineer_module.eo.c"
