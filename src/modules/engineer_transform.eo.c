
Efl_Object * _engineer_transform_engineer_module_init(Eo *obj, void *pd);


void _engineer_transform_engineer_module_component_awake(const COMPONENT *com, const ulong dt);


void _engineer_transform_engineer_module_component_start(const COMPONENT *com, const ulong dt);


void _engineer_transform_engineer_module_component_update(const COMPONENT *com, const ulong dt);


static Eina_Bool
_engineer_transform_class_initializer(Efl_Class *klass)
{
   EFL_OPS_DEFINE(cops,
      EFL_OBJECT_OP_FUNC(engineer_module_init, _engineer_transform_engineer_module_init),
      EFL_OBJECT_OP_FUNC(engineer_module_component_awake, _engineer_transform_engineer_module_component_awake),
      EFL_OBJECT_OP_FUNC(engineer_module_component_start, _engineer_transform_engineer_module_component_start),
      EFL_OBJECT_OP_FUNC(engineer_module_component_update, _engineer_transform_engineer_module_component_update)
   );

   return efl_class_functions_set(klass, NULL, &cops);
}

static const Efl_Class_Description _engineer_transform_class_desc = {
     EO_VERSION,
     "Engineer_Transform",
     EFL_CLASS_TYPE_REGULAR,
     sizeof(Engineer_Transform_Data),
     _engineer_transform_class_initializer,
     NULL,
     NULL
};

EFL_DEFINE_CLASS(engineer_transform_class_get, &_engineer_transform_class_desc, ENGINEER_MODULE_CLASS, NULL);
