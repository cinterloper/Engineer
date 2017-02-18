
Efl_Object *_engineer_node_efl_object_constructor(Eo *obj, Engineer_Node_Data *pd);


Efl_Object *_engineer_node_efl_object_finalize(Eo *obj, Engineer_Node_Data *pd);


void _engineer_node_efl_object_destructor(Eo *obj, Engineer_Node_Data *pd);


void _engineer_node_path_set(Eo *obj, Engineer_Node_Data *pd, const char *path);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_path_set, EFL_FUNC_CALL(path), const char *path);

const char *_engineer_node_path_get(Eo *obj, Engineer_Node_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(engineer_node_path_get, const char *, NULL);

void _engineer_node_title_set(Eo *obj, Engineer_Node_Data *pd, const char *title);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_title_set, EFL_FUNC_CALL(title), const char *title);

const char *_engineer_node_title_get(Eo *obj, Engineer_Node_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(engineer_node_title_get, const char *, NULL);

Eina_Stringshare *_engineer_node_module_load(Eo *obj, Engineer_Node_Data *pd, const char *class);

EOAPI EFL_FUNC_BODYV(engineer_node_module_load, Eina_Stringshare *, NULL, EFL_FUNC_CALL(class), const char *class);

Engineer_Module_Class *_engineer_node_module_class_lookup(Eo *obj, Engineer_Node_Data *pd, uint64_t target);

EOAPI EFL_FUNC_BODYV(engineer_node_module_class_lookup, Engineer_Module_Class *, NULL, EFL_FUNC_CALL(target), uint64_t target);

uint64_t _engineer_node_entity_id_use(Eo *obj, Engineer_Node_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_node_entity_id_use, uint64_t, 0);

void _engineer_node_entity_id_free(Eo *obj, Engineer_Node_Data *pd, uint64_t target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_entity_id_free, EFL_FUNC_CALL(target), uint64_t target);

uint64_t _engineer_node_entity_location_get(Eo *obj, Engineer_Node_Data *pd, uint64_t target);

EOAPI EFL_FUNC_BODYV(engineer_node_entity_location_get, uint64_t, 0, EFL_FUNC_CALL(target), uint64_t target);

void _engineer_node_entity_location_set(Eo *obj, Engineer_Node_Data *pd, uint64_t target, uint64_t location);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_entity_location_set, EFL_FUNC_CALL(target, location), uint64_t target, uint64_t location);

uint32_t _engineer_node_entity_status_get(Eo *obj, Engineer_Node_Data *pd, uint64_t target);

EOAPI EFL_FUNC_BODYV(engineer_node_entity_status_get, uint32_t, 0, EFL_FUNC_CALL(target), uint64_t target);

void _engineer_node_entity_status_set(Eo *obj, Engineer_Node_Data *pd, uint64_t target, char mode);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_entity_status_set, EFL_FUNC_CALL(target, mode), uint64_t target, char mode);

uint64_t _engineer_node_component_id_use(Eo *obj, Engineer_Node_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_node_component_id_use, uint64_t, 0);

void _engineer_node_component_id_free(Eo *obj, Engineer_Node_Data *pd, uint64_t target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_component_id_free, EFL_FUNC_CALL(target), uint64_t target);

uint64_t _engineer_node_component_location_get(Eo *obj, Engineer_Node_Data *pd, uint64_t target);

EOAPI EFL_FUNC_BODYV(engineer_node_component_location_get, uint64_t, 0, EFL_FUNC_CALL(target), uint64_t target);

void _engineer_node_component_location_set(Eo *obj, Engineer_Node_Data *pd, uint64_t target, uint64_t location);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_component_location_set, EFL_FUNC_CALL(target, location), uint64_t target, uint64_t location);

uint32_t _engineer_node_component_status_get(Eo *obj, Engineer_Node_Data *pd, uint64_t target);

EOAPI EFL_FUNC_BODYV(engineer_node_component_status_get, uint32_t, 0, EFL_FUNC_CALL(target), uint64_t target);

void _engineer_node_component_status_set(Eo *obj, Engineer_Node_Data *pd, uint64_t target, char mode);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_component_status_set, EFL_FUNC_CALL(target, mode), uint64_t target, char mode);

static Eina_Bool
_engineer_node_class_initializer(Efl_Class *klass)
{
   EFL_OPS_DEFINE(ops,
      EFL_OBJECT_OP_FUNC(efl_constructor, _engineer_node_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(efl_finalize, _engineer_node_efl_object_finalize),
      EFL_OBJECT_OP_FUNC(efl_destructor, _engineer_node_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_node_path_set, _engineer_node_path_set),
      EFL_OBJECT_OP_FUNC(engineer_node_path_get, _engineer_node_path_get),
      EFL_OBJECT_OP_FUNC(engineer_node_title_set, _engineer_node_title_set),
      EFL_OBJECT_OP_FUNC(engineer_node_title_get, _engineer_node_title_get),
      EFL_OBJECT_OP_FUNC(engineer_node_module_load, _engineer_node_module_load),
      EFL_OBJECT_OP_FUNC(engineer_node_module_class_lookup, _engineer_node_module_class_lookup),
      EFL_OBJECT_OP_FUNC(engineer_node_entity_id_use, _engineer_node_entity_id_use),
      EFL_OBJECT_OP_FUNC(engineer_node_entity_id_free, _engineer_node_entity_id_free),
      EFL_OBJECT_OP_FUNC(engineer_node_entity_location_get, _engineer_node_entity_location_get),
      EFL_OBJECT_OP_FUNC(engineer_node_entity_location_set, _engineer_node_entity_location_set),
      EFL_OBJECT_OP_FUNC(engineer_node_entity_status_get, _engineer_node_entity_status_get),
      EFL_OBJECT_OP_FUNC(engineer_node_entity_status_set, _engineer_node_entity_status_set),
      EFL_OBJECT_OP_FUNC(engineer_node_component_id_use, _engineer_node_component_id_use),
      EFL_OBJECT_OP_FUNC(engineer_node_component_id_free, _engineer_node_component_id_free),
      EFL_OBJECT_OP_FUNC(engineer_node_component_location_get, _engineer_node_component_location_get),
      EFL_OBJECT_OP_FUNC(engineer_node_component_location_set, _engineer_node_component_location_set),
      EFL_OBJECT_OP_FUNC(engineer_node_component_status_get, _engineer_node_component_status_get),
      EFL_OBJECT_OP_FUNC(engineer_node_component_status_set, _engineer_node_component_status_set)
   );
   return efl_class_functions_set(klass, &ops, NULL);
}

static const Efl_Class_Description _engineer_node_class_desc = {
   EO_VERSION,
   "Engineer.Node",
   EFL_CLASS_TYPE_REGULAR,
   sizeof(Engineer_Node_Data),
   _engineer_node_class_initializer,
   NULL,
   NULL
};

EFL_DEFINE_CLASS(engineer_node_class_get, &_engineer_node_class_desc, EFL_OBJECT_CLASS, NULL);
