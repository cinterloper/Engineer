
Efl_Object *_engineer_module_efl_object_constructor(Eo *obj, Engineer_Module_Data *pd);


void _engineer_module_efl_object_destructor(Eo *obj, Engineer_Module_Data *pd);


Efl_Object *_engineer_module_efl_object_constructor(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_module_efl_object_constructor, Efl_Object *, 0);

void _engineer_module_efl_object_destructor(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_efl_object_destructor);

void _engineer_module_iterate(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_iterate);

void _engineer_module_data_add(Eo *obj, Engineer_Module_Data *pd, unsigned int componentid, void *data);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_data_add, EFL_FUNC_CALL(componentid, data), unsigned int componentid, void *data);

void _engineer_module_data_set(Eo *obj, Engineer_Module_Data *pd, unsigned int cacheid, void *target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_data_set, EFL_FUNC_CALL(cacheid, target), unsigned int cacheid, void *target);

void _engineer_module_data_get(Eo *obj, Engineer_Module_Data *pd, unsigned int cacheid, void *target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_data_get, EFL_FUNC_CALL(cacheid, target), unsigned int cacheid, void *target);

void _engineer_module_data_swap(Eo *obj, Engineer_Module_Data *pd, unsigned int componenta, unsigned int componentb);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_data_swap, EFL_FUNC_CALL(componenta, componentb), unsigned int componenta, unsigned int componentb);

unsigned int _engineer_module_component_create(Eo *obj, Engineer_Module_Data *pd, unsigned int parent);

EOAPI EFL_FUNC_BODYV(engineer_module_component_create, unsigned int, 0, EFL_FUNC_CALL(parent), unsigned int parent);

void _engineer_module_component_destroy(Eo *obj, Engineer_Module_Data *pd, unsigned int targetid);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_component_destroy, EFL_FUNC_CALL(targetid), unsigned int targetid);

void _engineer_module_component_load(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_component_load);

void _engineer_module_component_save(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_component_save);
EOAPI EFL_FUNC_BODY_CONST(engineer_module_add, Efl_Object *, 0);
EOAPI EFL_VOID_FUNC_BODYV_CONST(engineer_module_component_awake, EFL_FUNC_CALL(dt), unsigned long dt);
EOAPI EFL_VOID_FUNC_BODYV_CONST(engineer_module_component_start, EFL_FUNC_CALL(com, dt), void *com, unsigned long dt);
EOAPI EFL_VOID_FUNC_BODYV_CONST(engineer_module_component_update, EFL_FUNC_CALL(com, dt), void *com, unsigned long dt);

static Eina_Bool
_engineer_module_class_initializer(Efl_Class *klass)
{
   EFL_OPS_DEFINE(ops,
      EFL_OBJECT_OP_FUNC(efl_constructor, _engineer_module_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(efl_destructor, _engineer_module_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_module_efl_object_constructor, _engineer_module_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(engineer_module_efl_object_destructor, _engineer_module_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_module_iterate, _engineer_module_iterate),
      EFL_OBJECT_OP_FUNC(engineer_module_data_add, _engineer_module_data_add),
      EFL_OBJECT_OP_FUNC(engineer_module_data_set, _engineer_module_data_set),
      EFL_OBJECT_OP_FUNC(engineer_module_data_get, _engineer_module_data_get),
      EFL_OBJECT_OP_FUNC(engineer_module_data_swap, _engineer_module_data_swap),
      EFL_OBJECT_OP_FUNC(engineer_module_component_create, _engineer_module_component_create),
      EFL_OBJECT_OP_FUNC(engineer_module_component_destroy, _engineer_module_component_destroy),
      EFL_OBJECT_OP_FUNC(engineer_module_component_load, _engineer_module_component_load),
      EFL_OBJECT_OP_FUNC(engineer_module_component_save, _engineer_module_component_save)
   );
   EFL_OPS_DEFINE(cops,
      EFL_OBJECT_OP_FUNC(engineer_module_add, NULL),
      EFL_OBJECT_OP_FUNC(engineer_module_component_awake, NULL),
      EFL_OBJECT_OP_FUNC(engineer_module_component_start, NULL),
      EFL_OBJECT_OP_FUNC(engineer_module_component_update, NULL)
   );
   return efl_class_functions_set(klass, &ops, &cops);
}

static const Efl_Class_Description _engineer_module_class_desc = {
   EO_VERSION,
   "Engineer_Module",
   EFL_CLASS_TYPE_REGULAR_NO_INSTANT,
   sizeof(Engineer_Module_Data),
   _engineer_module_class_initializer,
   NULL,
   NULL
};

EFL_DEFINE_CLASS(engineer_module_class_get, &_engineer_module_class_desc, EFL_OBJECT_CLASS, NULL);
