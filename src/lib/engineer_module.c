#include "engineer_module.h"

Eo *
engineer_module_new(Eo *parent)
{
   Eo *module = efl_add(ENGINEER_MODULE_CLASS, parent);
                  //engineer_scene_name_set(efl_added, name));

   return module;
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

   // Create and initialize the space (3 frames) needed to iterate our timeline.
   pd->buffer = eina_inarray_new(sizeof(Engineer_Module_Frame), 3);
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

      #define FIELD(key, type) \
         type##NEW(&frame->key)
      STATE
      #undef FIELD
   }

   // We need to set up our timeline pointers for the first time here.
   pd->future  = eina_inarray_nth(pd->buffer, 0);
   pd->present = eina_inarray_nth(pd->buffer, 1);
   pd->past    = eina_inarray_nth(pd->buffer, 2);

   pd->id       = eina_inarray_new(sizeof(uint64_t), 0);
   pd->lookup   = eina_hash_int64_new(NULL);

   return obj;
}

EOLIAN static void
_engineer_module_efl_object_destructor(Eo *obj, Engineer_Module_Data *pd EINA_UNUSED)
{
   efl_destructor(efl_super(obj, ENGINEER_MODULE_CLASS));
}

EOLIAN static Eina_Bool
_engineer_module_iterate(Eo *obj, Engineer_Module_Data *pd)
{
   uint64_t index;

   Engineer_Component *buffer;
   Engineer_Module_Frame *frame;
   //Engineer_Module_Class *class;

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
         type##COPY(&pd->present->key, &pd->future->key, index)
      STATE
      #undef FIELD

      #undef METADATA
   }

   // Set up our buffer here.

   // Alter the Scenegraph according to the present Entities' outboxen.
   index = 0;
   uint64_t *outbox;
   EINA_INARRAY_FOREACH(pd->id, outbox)
   {
      printf("Scene Iterator Response Checkpoint.\n");
      engineer_module_respond(obj, *outbox);
      index += 1;
   }

   // Invoke engineer_module_update() here.

   // Flush our buffer here

   return ECORE_CALLBACK_RENEW;
}

EOLIAN static void
_engineer_module_respond(Eo *obj, Engineer_Scene_Data *pd,
        Eina_Inarray *inbox)
{
   uint64_t count, offset, current, type, size, target, parent;

   //Engineer_Module_Class *class;
   Eo                    *module;
   Eina_Inarray          *input;

   count  = *(uint64_t*)eina_inarray_nth(inbox, 0);
   offset = 1;
   for(current = 0; current < count; current++)
   {
      type = (*(uint64_t*)eina_inarray_nth(inbox, offset + 1));
      switch(type)
      {
         #define FIELD(key, size)
         case 0: // Respond by creating an Entity and attaching it to a parent Entity.
         size  = 4;
         target = *(uint64_t*)eina_inarray_nth(outbox, offset + 2);
         parent = *(uint64_t*)eina_inarray_nth(outbox, offset + 3);

         engineer_scene_entity_create(obj, target, parent, NULL);
         break;

         #undef FIELD
      }
      offset += size;
   }
}

