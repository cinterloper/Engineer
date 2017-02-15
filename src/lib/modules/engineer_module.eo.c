
Efl_Object *_engineer_module_efl_object_constructor(Eo *obj, Engineer_Module_Data *pd);


Efl_Object *_engineer_module_efl_object_finalize(Eo *obj, Engineer_Module_Data *pd);


void _engineer_module_efl_object_destructor(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(engineer_module_add, Efl_Object *, NULL);

Efl_Object *_engineer_module_efl_object_constructor(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_module_efl_object_constructor, Efl_Object *, NULL);

void _engineer_module_efl_object_destructor(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_efl_object_destructor);

void _engineer_module_iterate(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_iterate);

void _engineer_module_respond(Eo *obj, Engineer_Module_Data *pd, Eina_Inarray *inbox, uint32_t offset);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_respond, EFL_FUNC_CALL(inbox, offset), Eina_Inarray *inbox, uint32_t offset);

uint32_t _engineer_module_cache_sizeof(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_module_cache_sizeof, uint32_t, 0);

void _engineer_module_cache_read(Eo *obj, Engineer_Module_Data *pd, COMPONENT *buffer, uint32_t index);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_cache_read, EFL_FUNC_CALL(buffer, index), COMPONENT *buffer, uint32_t index);

void _engineer_module_cache_write(Eo *obj, Engineer_Module_Data *pd, COMPONENT *buffer, uint32_t index);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_cache_write, EFL_FUNC_CALL(buffer, index), COMPONENT *buffer, uint32_t index);

unsigned int _engineer_module_component_create(Eo *obj, Engineer_Module_Data *pd, uint64_t id, uint64_t parent, COMPONENT *input);

EOAPI EFL_FUNC_BODYV(engineer_module_component_create, unsigned int, 0, EFL_FUNC_CALL(id, parent, input), uint64_t id, uint64_t parent, COMPONENT *input);

uint32_t _engineer_module_component_lookup(Eo *obj, Engineer_Module_Data *pd, uint64_t componentid);

EOAPI EFL_FUNC_BODYV(engineer_module_component_lookup, uint32_t, 0, EFL_FUNC_CALL(componentid), uint64_t componentid);

void _engineer_module_component_parent_set(Eo *obj, Engineer_Module_Data *pd, uint64_t target, uint64_t parent);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_component_parent_set, EFL_FUNC_CALL(target, parent), uint64_t target, uint64_t parent);

static Eina_Bool
_engineer_module_class_initializer(Efl_Class *klass)
{
   EFL_OPS_DEFINE(ops,
      EFL_OBJECT_OP_FUNC(efl_constructor, _engineer_module_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(efl_finalize, _engineer_module_efl_object_finalize),
      EFL_OBJECT_OP_FUNC(efl_destructor, _engineer_module_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_module_efl_object_constructor, _engineer_module_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(engineer_module_efl_object_destructor, _engineer_module_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_module_iterate, _engineer_module_iterate),
      EFL_OBJECT_OP_FUNC(engineer_module_respond, _engineer_module_respond),
      EFL_OBJECT_OP_FUNC(engineer_module_cache_sizeof, _engineer_module_cache_sizeof),
      EFL_OBJECT_OP_FUNC(engineer_module_cache_read, _engineer_module_cache_read),
      EFL_OBJECT_OP_FUNC(engineer_module_cache_write, _engineer_module_cache_write),
      EFL_OBJECT_OP_FUNC(engineer_module_component_create, _engineer_module_component_create),
      EFL_OBJECT_OP_FUNC(engineer_module_component_lookup, _engineer_module_component_lookup),
      EFL_OBJECT_OP_FUNC(engineer_module_component_parent_set, _engineer_module_component_parent_set)
   );
   EFL_OPS_DEFINE(cops,
      EFL_OBJECT_OP_FUNC(engineer_module_add, NULL)
   );
   return efl_class_functions_set(klass, &ops, &cops);
}

static const Efl_Class_Description _engineer_module_class_desc = {
   EO_VERSION,
   "Engineer.Module",
   EFL_CLASS_TYPE_REGULAR_NO_INSTANT,
   sizeof(Engineer_Module_Data),
   _engineer_module_class_initializer,
   NULL,
   NULL
};

EFL_DEFINE_CLASS(engineer_module_class_get, &_engineer_module_class_desc, EFL_OBJECT_CLASS, NULL);
