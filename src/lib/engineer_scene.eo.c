EWAPI const Efl_Event_Description _ENGINEER_SCENE_EVENT_SECTOR_ITERATE_CB =
   EFL_EVENT_DESCRIPTION("sector_iterate_cb");

Efl_Object *_engineer_scene_efl_object_constructor(Eo *obj, Engineer_Scene_Data *pd);


Efl_Object *_engineer_scene_efl_object_finalize(Eo *obj, Engineer_Scene_Data *pd);


void _engineer_scene_efl_object_destructor(Eo *obj, Engineer_Scene_Data *pd);


void _engineer_scene_game_set(Eo *obj, Engineer_Scene_Data *pd, const char *path);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_game_set, EFL_FUNC_CALL(path), const char *path);

const char *_engineer_scene_game_get(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(engineer_scene_game_get, const char *, NULL);

void _engineer_scene_name_set(Eo *obj, Engineer_Scene_Data *pd, const char *name);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_name_set, EFL_FUNC_CALL(name), const char *name);

const char *_engineer_scene_name_get(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(engineer_scene_name_get, const char *, NULL);

Efl_Object *_engineer_scene_efl_object_constructor(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_scene_efl_object_constructor, Efl_Object *, NULL);

void _engineer_scene_efl_object_destructor(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_scene_efl_object_destructor);

Eina_Bool _engineer_scene_iterate(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_scene_iterate, Eina_Bool, 0);

Eina_Bool _engineer_scene_iterate_entity(Eo *obj, Engineer_Scene_Data *pd, void *key, void *data);

EOAPI EFL_FUNC_BODYV(engineer_scene_iterate_entity, Eina_Bool, 0, EFL_FUNC_CALL(key, data), void *key, void *data);

Eina_Bool _engineer_scene_iterate_component(Eo *obj, Engineer_Scene_Data *pd, void *key, void *data);

EOAPI EFL_FUNC_BODYV(engineer_scene_iterate_component, Eina_Bool, 0, EFL_FUNC_CALL(key, data), void *key, void *data);

void _engineer_scene_timeline_adjust(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_scene_timeline_adjust);

void _engineer_scene_timeline_push(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_scene_timeline_push);

void _engineer_scene_timeline_pop(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_scene_timeline_pop);

unsigned int _engineer_scene_entity_create(Eo *obj, Engineer_Scene_Data *pd, unsigned int parent, const char *name);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_create, unsigned int, 0, EFL_FUNC_CALL(parent, name), unsigned int parent, const char *name);

void _engineer_scene_entity_destroy(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_destroy, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_entity_dispose(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_dispose, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_entity_load(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_load, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_entity_save(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_save, EFL_FUNC_CALL(target), unsigned int target);

Engineer_Scene_Entity *_engineer_scene_entity_lookup(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_lookup, Engineer_Scene_Entity *, NULL, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_entity_data_swap(Eo *obj, Engineer_Scene_Data *pd, unsigned int targeta, unsigned int targetb);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_data_swap, EFL_FUNC_CALL(targeta, targetb), unsigned int targeta, unsigned int targetb);

unsigned int _engineer_scene_entity_status_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_status_get, unsigned int, 0, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_entity_status_set(Eo *obj, Engineer_Scene_Data *pd, unsigned int target, char mode);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_status_set, EFL_FUNC_CALL(target, mode), unsigned int target, char mode);

unsigned int _engineer_scene_entity_parent_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_parent_get, unsigned int, 0, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_entity_parent_set(Eo *obj, Engineer_Scene_Data *pd, unsigned int target, unsigned int parent);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_parent_set, EFL_FUNC_CALL(target, parent), unsigned int target, unsigned int parent);

void _engineer_scene_entity_sibling_swap(Eo *obj, Engineer_Scene_Data *pd, unsigned int siblinga, unsigned int siblingb);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_sibling_swap, EFL_FUNC_CALL(siblinga, siblingb), unsigned int siblinga, unsigned int siblingb);

Eina_Inarray *_engineer_scene_entity_children_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_children_get, Eina_Inarray *, NULL, EFL_FUNC_CALL(target), unsigned int target);

Eina_Inarray *_engineer_scene_entity_components_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_components_get, Eina_Inarray *, NULL, EFL_FUNC_CALL(target), unsigned int target);

unsigned int _engineer_scene_entity_id_use(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_scene_entity_id_use, unsigned int, 0);

void _engineer_scene_entity_id_free(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_id_free, EFL_FUNC_CALL(target), unsigned int target);

unsigned int _engineer_scene_component_create(Eo *obj, Engineer_Scene_Data *pd, unsigned int parent, const char *type);

EOAPI EFL_FUNC_BODYV(engineer_scene_component_create, unsigned int, 0, EFL_FUNC_CALL(parent, type), unsigned int parent, const char *type);

void _engineer_scene_component_destroy(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_destroy, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_dispose(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_dispose, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_load(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_load, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_save(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_save, EFL_FUNC_CALL(target), unsigned int target);

Engineer_Scene_Component *_engineer_scene_component_lookup(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_scene_component_lookup, Engineer_Scene_Component *, NULL, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_data_swap(Eo *obj, Engineer_Scene_Data *pd, unsigned int targeta, unsigned int targetb);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_data_swap, EFL_FUNC_CALL(targeta, targetb), unsigned int targeta, unsigned int targetb);

unsigned int _engineer_scene_component_status_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_scene_component_status_get, unsigned int, 0, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_status_set(Eo *obj, Engineer_Scene_Data *pd, unsigned int target, char mode);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_status_set, EFL_FUNC_CALL(target, mode), unsigned int target, char mode);

unsigned int _engineer_scene_component_parent_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_scene_component_parent_get, unsigned int, 0, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_parent_set(Eo *obj, Engineer_Scene_Data *pd, unsigned int target, unsigned int parent);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_parent_set, EFL_FUNC_CALL(target, parent), unsigned int target, unsigned int parent);

void _engineer_scene_component_sibling_swap(Eo *obj, Engineer_Scene_Data *pd, unsigned int siblinga, unsigned int siblingb);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_sibling_swap, EFL_FUNC_CALL(siblinga, siblingb), unsigned int siblinga, unsigned int siblingb);

unsigned int _engineer_scene_component_id_use(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_scene_component_id_use, unsigned int, 0);

void _engineer_scene_component_id_free(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_id_free, EFL_FUNC_CALL(target), unsigned int target);

static Eina_Bool
_engineer_scene_class_initializer(Efl_Class *klass)
{
   EFL_OPS_DEFINE(ops,
      EFL_OBJECT_OP_FUNC(efl_constructor, _engineer_scene_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(efl_finalize, _engineer_scene_efl_object_finalize),
      EFL_OBJECT_OP_FUNC(efl_destructor, _engineer_scene_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_scene_game_set, _engineer_scene_game_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_game_get, _engineer_scene_game_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_name_set, _engineer_scene_name_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_name_get, _engineer_scene_name_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_efl_object_constructor, _engineer_scene_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(engineer_scene_efl_object_destructor, _engineer_scene_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_scene_iterate, _engineer_scene_iterate),
      EFL_OBJECT_OP_FUNC(engineer_scene_iterate_entity, _engineer_scene_iterate_entity),
      EFL_OBJECT_OP_FUNC(engineer_scene_iterate_component, _engineer_scene_iterate_component),
      EFL_OBJECT_OP_FUNC(engineer_scene_timeline_adjust, _engineer_scene_timeline_adjust),
      EFL_OBJECT_OP_FUNC(engineer_scene_timeline_push, _engineer_scene_timeline_push),
      EFL_OBJECT_OP_FUNC(engineer_scene_timeline_pop, _engineer_scene_timeline_pop),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_create, _engineer_scene_entity_create),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_destroy, _engineer_scene_entity_destroy),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_dispose, _engineer_scene_entity_dispose),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_load, _engineer_scene_entity_load),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_save, _engineer_scene_entity_save),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_lookup, _engineer_scene_entity_lookup),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_data_swap, _engineer_scene_entity_data_swap),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_status_get, _engineer_scene_entity_status_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_status_set, _engineer_scene_entity_status_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_parent_get, _engineer_scene_entity_parent_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_parent_set, _engineer_scene_entity_parent_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_sibling_swap, _engineer_scene_entity_sibling_swap),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_children_get, _engineer_scene_entity_children_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_components_get, _engineer_scene_entity_components_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_id_use, _engineer_scene_entity_id_use),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_id_free, _engineer_scene_entity_id_free),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_create, _engineer_scene_component_create),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_destroy, _engineer_scene_component_destroy),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_dispose, _engineer_scene_component_dispose),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_load, _engineer_scene_component_load),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_save, _engineer_scene_component_save),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_lookup, _engineer_scene_component_lookup),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_data_swap, _engineer_scene_component_data_swap),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_status_get, _engineer_scene_component_status_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_status_set, _engineer_scene_component_status_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_parent_get, _engineer_scene_component_parent_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_parent_set, _engineer_scene_component_parent_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_sibling_swap, _engineer_scene_component_sibling_swap),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_id_use, _engineer_scene_component_id_use),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_id_free, _engineer_scene_component_id_free)
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
