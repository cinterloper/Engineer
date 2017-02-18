EWAPI const Efl_Event_Description _ENGINEER_SCENE_EVENT_ITERATE_CB =
   EFL_EVENT_DESCRIPTION("iterate_cb");

Efl_Object *_engineer_scene_efl_object_constructor(Eo *obj, Engineer_Scene_Data *pd);


Efl_Object *_engineer_scene_efl_object_finalize(Eo *obj, Engineer_Scene_Data *pd);


void _engineer_scene_efl_object_destructor(Eo *obj, Engineer_Scene_Data *pd);


Efl_Object *_engineer_scene_efl_object_constructor(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_scene_efl_object_constructor, Efl_Object *, NULL);

Efl_Object *_engineer_scene_efl_object_finalize(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_scene_efl_object_finalize, Efl_Object *, NULL);

void _engineer_scene_efl_object_destructor(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_scene_efl_object_destructor);

void _engineer_scene_name_set(Eo *obj, Engineer_Scene_Data *pd, const char *name);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_name_set, EFL_FUNC_CALL(name), const char *name);

const char *_engineer_scene_name_get(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(engineer_scene_name_get, const char *, NULL);

Efl_Object *_engineer_scene_module_get(Eo *obj, Engineer_Scene_Data *pd, uint64_t *classid);

EOAPI EFL_FUNC_BODYV_CONST(engineer_scene_module_get, Efl_Object *, NULL, EFL_FUNC_CALL(classid), uint64_t *classid);

Eina_Bool _engineer_scene_iterate(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_scene_iterate, Eina_Bool, 0);

void _engineer_scene_respond(Eo *obj, Engineer_Scene_Data *pd, Eina_Inarray *inboxs);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_respond, EFL_FUNC_CALL(inboxs), Eina_Inarray *inboxs);

Eina_Bool _engineer_scene_entity_create(Eo *obj, Engineer_Scene_Data *pd, uint64_t id, uint64_t parent, const char *name);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_create, Eina_Bool, 0, EFL_FUNC_CALL(id, parent, name), uint64_t id, uint64_t parent, const char *name);

uint64_t _engineer_scene_entity_lookup(Eo *obj, Engineer_Scene_Data *pd, uint64_t target);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_lookup, uint64_t, 0, EFL_FUNC_CALL(target), uint64_t target);

void _engineer_scene_entity_parent_set(Eo *obj, Engineer_Scene_Data *pd, uint64_t target, uint64_t parent);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_parent_set, EFL_FUNC_CALL(target, parent), uint64_t target, uint64_t parent);

void _engineer_scene_entity_siblingnext_set(Eo *obj, Engineer_Scene_Data *pd, uint64_t target, uint64_t component);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_siblingnext_set, EFL_FUNC_CALL(target, component), uint64_t target, uint64_t component);

uint64_t _engineer_scene_entity_siblingnext_get(Eo *obj, Engineer_Scene_Data *pd, uint64_t target);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_siblingnext_get, uint64_t, 0, EFL_FUNC_CALL(target), uint64_t target);

void _engineer_scene_entity_siblingprev_set(Eo *obj, Engineer_Scene_Data *pd, uint64_t target, uint64_t component);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_siblingprev_set, EFL_FUNC_CALL(target, component), uint64_t target, uint64_t component);

uint64_t _engineer_scene_entity_siblingprev_get(Eo *obj, Engineer_Scene_Data *pd, uint64_t target);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_siblingprev_get, uint64_t, 0, EFL_FUNC_CALL(target), uint64_t target);

void _engineer_scene_entity_firstentity_set(Eo *obj, Engineer_Scene_Data *pd, uint64_t target, uint64_t component);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_firstentity_set, EFL_FUNC_CALL(target, component), uint64_t target, uint64_t component);

uint64_t _engineer_scene_entity_firstentity_get(Eo *obj, Engineer_Scene_Data *pd, uint64_t target);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_firstentity_get, uint64_t, 0, EFL_FUNC_CALL(target), uint64_t target);

void _engineer_scene_entity_firstcomponent_set(Eo *obj, Engineer_Scene_Data *pd, uint64_t target, uint64_t component);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_firstcomponent_set, EFL_FUNC_CALL(target, component), uint64_t target, uint64_t component);

uint64_t _engineer_scene_entity_firstcomponent_get(Eo *obj, Engineer_Scene_Data *pd, uint64_t target);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_firstcomponent_get, uint64_t, 0, EFL_FUNC_CALL(target), uint64_t target);

Eina_Inarray *_engineer_scene_entity_inbox_get(Eo *obj, Engineer_Scene_Data *pd, uint64_t entityid);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_inbox_get, Eina_Inarray *, NULL, EFL_FUNC_CALL(entityid), uint64_t entityid);

Eina_Inarray *_engineer_scene_entity_outbox_get(Eo *obj, Engineer_Scene_Data *pd, uint64_t entityid);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_outbox_get, Eina_Inarray *, NULL, EFL_FUNC_CALL(entityid), uint64_t entityid);

void _engineer_scene_notice_push_event(Eo *obj, Engineer_Scene_Data *pd, uint64_t sender, uint64_t type, uint64_t entityid, void *payload, uint64_t size);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_notice_push_event, EFL_FUNC_CALL(sender, type, entityid, payload, size), uint64_t sender, uint64_t type, uint64_t entityid, void *payload, uint64_t size);

void _engineer_scene_notice_push_entity_create(Eo *obj, Engineer_Scene_Data *pd, uint64_t sender, uint64_t entityid, uint64_t parent);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_notice_push_entity_create, EFL_FUNC_CALL(sender, entityid, parent), uint64_t sender, uint64_t entityid, uint64_t parent);

void _engineer_scene_notice_push_component_create(Eo *obj, Engineer_Scene_Data *pd, uint64_t sender, uint64_t classid, uint64_t componentid, uint64_t parent, uint64_t *payload);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_notice_push_component_create, EFL_FUNC_CALL(sender, classid, componentid, parent, payload), uint64_t sender, uint64_t classid, uint64_t componentid, uint64_t parent, uint64_t *payload);

static Eina_Bool
_engineer_scene_class_initializer(Efl_Class *klass)
{
   EFL_OPS_DEFINE(ops,
      EFL_OBJECT_OP_FUNC(efl_constructor, _engineer_scene_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(efl_finalize, _engineer_scene_efl_object_finalize),
      EFL_OBJECT_OP_FUNC(efl_destructor, _engineer_scene_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_scene_efl_object_constructor, _engineer_scene_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(engineer_scene_efl_object_finalize, _engineer_scene_efl_object_finalize),
      EFL_OBJECT_OP_FUNC(engineer_scene_efl_object_destructor, _engineer_scene_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_scene_name_set, _engineer_scene_name_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_name_get, _engineer_scene_name_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_module_get, _engineer_scene_module_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_iterate, _engineer_scene_iterate),
      EFL_OBJECT_OP_FUNC(engineer_scene_respond, _engineer_scene_respond),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_create, _engineer_scene_entity_create),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_lookup, _engineer_scene_entity_lookup),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_parent_set, _engineer_scene_entity_parent_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_siblingnext_set, _engineer_scene_entity_siblingnext_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_siblingnext_get, _engineer_scene_entity_siblingnext_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_siblingprev_set, _engineer_scene_entity_siblingprev_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_siblingprev_get, _engineer_scene_entity_siblingprev_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_firstentity_set, _engineer_scene_entity_firstentity_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_firstentity_get, _engineer_scene_entity_firstentity_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_firstcomponent_set, _engineer_scene_entity_firstcomponent_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_firstcomponent_get, _engineer_scene_entity_firstcomponent_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_inbox_get, _engineer_scene_entity_inbox_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_outbox_get, _engineer_scene_entity_outbox_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_notice_push_event, _engineer_scene_notice_push_event),
      EFL_OBJECT_OP_FUNC(engineer_scene_notice_push_entity_create, _engineer_scene_notice_push_entity_create),
      EFL_OBJECT_OP_FUNC(engineer_scene_notice_push_component_create, _engineer_scene_notice_push_component_create)
   );
   return efl_class_functions_set(klass, &ops, NULL);
}

static const Efl_Class_Description _engineer_scene_class_desc = {
   EO_VERSION,
   "Engineer.Scene",
   EFL_CLASS_TYPE_REGULAR,
   sizeof(Engineer_Scene_Data),
   _engineer_scene_class_initializer,
   NULL,
   NULL
};

EFL_DEFINE_CLASS(engineer_scene_class_get, &_engineer_scene_class_desc, EFL_OBJECT_CLASS, NULL);
