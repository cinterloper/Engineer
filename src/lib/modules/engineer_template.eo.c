
Efl_Object * _engineer_module_template_engineer_module_init(Eo *obj, void *pd);


unsigned int _engineer_module_template_engineer_module_size(Eo *obj, void *pd);


void _engineer_module_template_engineer_module_component_update(Eo *obj, void *pd, void *component);


static const Efl_Op_Description _engineer_module_template_op_desc[] = {
     EFL_OBJECT_OP_CLASS_FUNC_OVERRIDE(engineer_module_init, _engineer_module_template_engineer_module_init),
     EFL_OBJECT_OP_CLASS_FUNC_OVERRIDE(engineer_module_size, _engineer_module_template_engineer_module_size),
     EFL_OBJECT_OP_CLASS_FUNC_OVERRIDE(engineer_module_component_update, _engineer_module_template_engineer_module_component_update),
};

static const Efl_Class_Description _engineer_module_template_class_desc = {
     EO_VERSION,
     "Engineer_Module_Template",
     EFL_CLASS_TYPE_REGULAR,
     EFL_CLASS_DESCRIPTION_OPS(_engineer_module_template_op_desc),
     sizeof(Engineer_Module_Template_Data),
     NULL,
     NULL
};

EFL_DEFINE_CLASS(engineer_module_template_class_get, &_engineer_module_template_class_desc, ENGINEER_MODULE_CLASS, NULL);