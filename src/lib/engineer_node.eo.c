
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

void _engineer_node_file_load(Eo *obj, Engineer_Node_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_node_file_load);

void _engineer_node_file_save(Eo *obj, Engineer_Node_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_node_file_save);

void _engineer_node_file_close(Eo *obj, Engineer_Node_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_node_file_close);

Efl_Object *_engineer_node_scene_create(Eo *obj, Engineer_Node_Data *pd, const char *name);

EOAPI EFL_FUNC_BODYV(engineer_node_scene_create, Efl_Object *, NULL, EFL_FUNC_CALL(name), const char *name);

Efl_Object *_engineer_node_scene_load(Eo *obj, Engineer_Node_Data *pd, const char *name);

EOAPI EFL_FUNC_BODYV(engineer_node_scene_load, Efl_Object *, NULL, EFL_FUNC_CALL(name), const char *name);

void _engineer_node_scene_save(Eo *obj, Engineer_Node_Data *pd, const char *name);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_scene_save, EFL_FUNC_CALL(name), const char *name);

void _engineer_node_scene_unload(Eo *obj, Engineer_Node_Data *pd, const char *name);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_scene_unload, EFL_FUNC_CALL(name), const char *name);

unsigned int _engineer_node_module_register(Eo *obj, Engineer_Node_Data *pd, const char *name);

EOAPI EFL_FUNC_BODYV(engineer_node_module_register, unsigned int, 0, EFL_FUNC_CALL(name), const char *name);

void _engineer_node_module_load(Eo *obj, Engineer_Node_Data *pd, const char *file);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_module_load, EFL_FUNC_CALL(file), const char *file);

void _engineer_node_module_unload(Eo *obj, Engineer_Node_Data *pd, Efl_Object *target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_module_unload, EFL_FUNC_CALL(target), Efl_Object *target);

void _engineer_node_module_unregister(Eo *obj, Engineer_Node_Data *pd, const char *name);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_module_unregister, EFL_FUNC_CALL(name), const char *name);

Engineer_Node_Module *_engineer_node_module_lookup(Eo *obj, Engineer_Node_Data *pd, unsigned int target);

EOAPI EFL_FUNC_BODYV(engineer_node_module_lookup, Engineer_Node_Module *, NULL, EFL_FUNC_CALL(target), unsigned int target);

Engineer_Node_Module *_engineer_node_module_lookup_by_type(Eo *obj, Engineer_Node_Data *pd, const char *target);

EOAPI EFL_FUNC_BODYV(engineer_node_module_lookup_by_type, Engineer_Node_Module *, NULL, EFL_FUNC_CALL(target), const char *target);

unsigned int _engineer_node_module_id_use(Eo *obj, Engineer_Node_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_node_module_id_use, unsigned int, 0);

void _engineer_node_module_id_free(Eo *obj, Engineer_Node_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_node_module_id_free, EFL_FUNC_CALL(target), unsigned int target);

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
      EFL_OBJECT_OP_FUNC(engineer_node_file_load, _engineer_node_file_load),
      EFL_OBJECT_OP_FUNC(engineer_node_file_save, _engineer_node_file_save),
      EFL_OBJECT_OP_FUNC(engineer_node_file_close, _engineer_node_file_close),
      EFL_OBJECT_OP_FUNC(engineer_node_scene_create, _engineer_node_scene_create),
      EFL_OBJECT_OP_FUNC(engineer_node_scene_load, _engineer_node_scene_load),
      EFL_OBJECT_OP_FUNC(engineer_node_scene_save, _engineer_node_scene_save),
      EFL_OBJECT_OP_FUNC(engineer_node_scene_unload, _engineer_node_scene_unload),
      EFL_OBJECT_OP_FUNC(engineer_node_module_register, _engineer_node_module_register),
      EFL_OBJECT_OP_FUNC(engineer_node_module_load, _engineer_node_module_load),
      EFL_OBJECT_OP_FUNC(engineer_node_module_unload, _engineer_node_module_unload),
      EFL_OBJECT_OP_FUNC(engineer_node_module_unregister, _engineer_node_module_unregister),
      EFL_OBJECT_OP_FUNC(engineer_node_module_lookup, _engineer_node_module_lookup),
      EFL_OBJECT_OP_FUNC(engineer_node_module_lookup_by_type, _engineer_node_module_lookup_by_type),
      EFL_OBJECT_OP_FUNC(engineer_node_module_id_use, _engineer_node_module_id_use),
      EFL_OBJECT_OP_FUNC(engineer_node_module_id_free, _engineer_node_module_id_free)
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
