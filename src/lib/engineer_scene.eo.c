EOAPI const Efl_Event_Description _ENGINEER_SCENE_EVENT_SECTOR_ITERATE_CB =
   EFL_EVENT_DESCRIPTION("sector_iterate_cb");

void _engineer_scene_game_set(Eo *obj, Engineer_Scene_Data *pd, const char *path);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_game_set, EFL_FUNC_CALL(path), const char *path);

const char * _engineer_scene_game_get(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(engineer_scene_game_get, const char *, 0);

void _engineer_scene_name_set(Eo *obj, Engineer_Scene_Data *pd, const char *name);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_name_set, EFL_FUNC_CALL(name), const char *name);

const char * _engineer_scene_name_get(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(engineer_scene_name_get, const char *, 0);

void _engineer_scene_entity_status_set(Eo *obj, Engineer_Scene_Data *pd, unsigned int target, char mode);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_status_set, EFL_FUNC_CALL(target, mode), unsigned int target, char mode);

unsigned int _engineer_scene_entity_status_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV_CONST(engineer_scene_entity_status_get, unsigned int, 0, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_entity_parent_set(Eo *obj, Engineer_Scene_Data *pd, unsigned int target, unsigned int parent);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_parent_set, EFL_FUNC_CALL(target, parent), unsigned int target, unsigned int parent);

unsigned int _engineer_scene_entity_parent_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV_CONST(engineer_scene_entity_parent_get, unsigned int, 0, EFL_FUNC_CALL(target), unsigned int target);

Eina_Inarray * _engineer_scene_entity_children_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV_CONST(engineer_scene_entity_children_get, Eina_Inarray *, 0, EFL_FUNC_CALL(target), unsigned int target);

Eina_Inarray * _engineer_scene_entity_components_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV_CONST(engineer_scene_entity_components_get, Eina_Inarray *, 0, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_status_set(Eo *obj, Engineer_Scene_Data *pd, unsigned int target, char mode);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_status_set, EFL_FUNC_CALL(target, mode), unsigned int target, char mode);

unsigned int _engineer_scene_component_status_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV_CONST(engineer_scene_component_status_get, unsigned int, 0, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_parent_set(Eo *obj, Engineer_Scene_Data *pd, unsigned int target, unsigned int parent);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_parent_set, EFL_FUNC_CALL(target, parent), unsigned int target, unsigned int parent);

unsigned int _engineer_scene_component_parent_get(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV_CONST(engineer_scene_component_parent_get, unsigned int, 0, EFL_FUNC_CALL(target), unsigned int target);

Efl_Object * _engineer_scene_efl_object_constructor(Eo *obj, Engineer_Scene_Data *pd, char *path, char *name);

EOAPI EFL_FUNC_BODYV(engineer_scene_efl_object_constructor, Efl_Object *, 0, EFL_FUNC_CALL(path, name), char *path, char *name);

void _engineer_scene_efl_object_destructor(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_scene_efl_object_destructor);

void _engineer_scene_file_load(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_scene_file_load);

void _engineer_scene_file_save(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_scene_file_save);

void _engineer_scene_file_sync(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_scene_file_sync);

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

Engineer_Scene_Entity * _engineer_scene_entity_lookup(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_scene_entity_lookup, Engineer_Scene_Entity *, 0, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_entity_data_swap(Eo *obj, Engineer_Scene_Data *pd, unsigned int targeta, unsigned int targetb);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_data_swap, EFL_FUNC_CALL(targeta, targetb), unsigned int targeta, unsigned int targetb);

void _engineer_scene_entity_sibling_swap(Eo *obj, Engineer_Scene_Data *pd, unsigned int siblinga, unsigned int siblingb);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_sibling_swap, EFL_FUNC_CALL(siblinga, siblingb), unsigned int siblinga, unsigned int siblingb);

unsigned int _engineer_scene_entity_id_use(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_scene_entity_id_use, unsigned int, 0);

void _engineer_scene_entity_id_free(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_entity_id_free, EFL_FUNC_CALL(target), unsigned int target);

unsigned int _engineer_scene_component_create(Eo *obj, Engineer_Scene_Data *pd, unsigned int parent);

EOAPI EFL_FUNC_BODYV(engineer_scene_component_create, unsigned int, 0, EFL_FUNC_CALL(parent), unsigned int parent);

void _engineer_scene_component_destroy(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_destroy, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_dispose(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_dispose, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_load(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_load, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_save(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_save, EFL_FUNC_CALL(target), unsigned int target);

Engineer_Scene_Component * _engineer_scene_component_lookup(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_scene_component_lookup, Engineer_Scene_Component *, 0, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_component_data_swap(Eo *obj, Engineer_Scene_Data *pd, unsigned int targeta, unsigned int targetb);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_data_swap, EFL_FUNC_CALL(targeta, targetb), unsigned int targeta, unsigned int targetb);

void _engineer_scene_component_sibling_swap(Eo *obj, Engineer_Scene_Data *pd, unsigned int siblinga, unsigned int siblingb);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_sibling_swap, EFL_FUNC_CALL(siblinga, siblingb), unsigned int siblinga, unsigned int siblingb);

unsigned int _engineer_scene_component_id_use(Eo *obj, Engineer_Scene_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_scene_component_id_use, unsigned int, 0);

void _engineer_scene_component_id_free(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_component_id_free, EFL_FUNC_CALL(target), unsigned int target);

unsigned int _engineer_scene_sector_create(Eo *obj, Engineer_Scene_Data *pd, unsigned int parent);

EOAPI EFL_FUNC_BODYV(engineer_scene_sector_create, unsigned int, 0, EFL_FUNC_CALL(parent), unsigned int parent);

void _engineer_scene_sector_destroy(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_sector_destroy, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_sector_dispose(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_sector_dispose, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_sector_load(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_sector_load, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_sector_save(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_sector_save, EFL_FUNC_CALL(target), unsigned int target);

Engineer_Scene_Sector * _engineer_scene_sector_lookup(Eo *obj, Engineer_Scene_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_scene_sector_lookup, Engineer_Scene_Sector *, 0, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_scene_sector_data_swap(Eo *obj, Engineer_Scene_Data *pd, unsigned int targeta, unsigned int targetb);

EOAPI EFL_VOID_FUNC_BODYV(engineer_scene_sector_data_swap, EFL_FUNC_CALL(targeta, targetb), unsigned int targeta, unsigned int targetb);

Efl_Object * _engineer_scene_efl_object_constructor(Eo *obj, Engineer_Scene_Data *pd);


Efl_Object * _engineer_scene_efl_object_finalize(Eo *obj, Engineer_Scene_Data *pd);


void _engineer_scene_efl_object_destructor(Eo *obj, Engineer_Scene_Data *pd);


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
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_status_set, _engineer_scene_entity_status_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_status_get, _engineer_scene_entity_status_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_parent_set, _engineer_scene_entity_parent_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_parent_get, _engineer_scene_entity_parent_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_children_get, _engineer_scene_entity_children_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_components_get, _engineer_scene_entity_components_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_status_set, _engineer_scene_component_status_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_status_get, _engineer_scene_component_status_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_parent_set, _engineer_scene_component_parent_set),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_parent_get, _engineer_scene_component_parent_get),
      EFL_OBJECT_OP_FUNC(engineer_scene_efl_object_constructor, _engineer_scene_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(engineer_scene_efl_object_destructor, _engineer_scene_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_scene_file_load, _engineer_scene_file_load),
      EFL_OBJECT_OP_FUNC(engineer_scene_file_save, _engineer_scene_file_save),
      EFL_OBJECT_OP_FUNC(engineer_scene_file_sync, _engineer_scene_file_sync),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_create, _engineer_scene_entity_create),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_destroy, _engineer_scene_entity_destroy),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_dispose, _engineer_scene_entity_dispose),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_load, _engineer_scene_entity_load),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_save, _engineer_scene_entity_save),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_lookup, _engineer_scene_entity_lookup),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_data_swap, _engineer_scene_entity_data_swap),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_sibling_swap, _engineer_scene_entity_sibling_swap),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_id_use, _engineer_scene_entity_id_use),
      EFL_OBJECT_OP_FUNC(engineer_scene_entity_id_free, _engineer_scene_entity_id_free),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_create, _engineer_scene_component_create),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_destroy, _engineer_scene_component_destroy),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_dispose, _engineer_scene_component_dispose),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_load, _engineer_scene_component_load),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_save, _engineer_scene_component_save),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_lookup, _engineer_scene_component_lookup),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_data_swap, _engineer_scene_component_data_swap),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_sibling_swap, _engineer_scene_component_sibling_swap),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_id_use, _engineer_scene_component_id_use),
      EFL_OBJECT_OP_FUNC(engineer_scene_component_id_free, _engineer_scene_component_id_free),
      EFL_OBJECT_OP_FUNC(engineer_scene_sector_create, _engineer_scene_sector_create),
      EFL_OBJECT_OP_FUNC(engineer_scene_sector_destroy, _engineer_scene_sector_destroy),
      EFL_OBJECT_OP_FUNC(engineer_scene_sector_dispose, _engineer_scene_sector_dispose),
      EFL_OBJECT_OP_FUNC(engineer_scene_sector_load, _engineer_scene_sector_load),
      EFL_OBJECT_OP_FUNC(engineer_scene_sector_save, _engineer_scene_sector_save),
      EFL_OBJECT_OP_FUNC(engineer_scene_sector_lookup, _engineer_scene_sector_lookup),
      EFL_OBJECT_OP_FUNC(engineer_scene_sector_data_swap, _engineer_scene_sector_data_swap)
   );

   return efl_class_functions_set(klass, &ops, NULL);
}

static const Efl_Class_Description _engineer_scene_class_desc = {
     EO_VERSION,
     "Engineer_Scene",
     EFL_CLASS_TYPE_REGULAR,
     sizeof(Engineer_Scene_Data),
     _engineer_scene_class_initializer,
     NULL,
     NULL
};

EFL_DEFINE_CLASS(engineer_scene_class_get, &_engineer_scene_class_desc, EFL_OBJECT_CLASS, NULL);