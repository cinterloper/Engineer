
Efl_Object *_engineer_module_efl_object_constructor(Eo *obj, Engineer_Module_Data *pd);


Efl_Object *_engineer_module_efl_object_finalize(Eo *obj, Engineer_Module_Data *pd);


void _engineer_module_efl_object_destructor(Eo *obj, Engineer_Module_Data *pd);


Efl_Object *_engineer_module_efl_object_constructor(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_module_efl_object_constructor, Efl_Object *, NULL);

void _engineer_module_efl_object_destructor(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_efl_object_destructor);
EOAPI EFL_FUNC_BODY_CONST(engineer_module_factory, Efl_Object *, NULL);

void _engineer_module_iterate(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_iterate);

void _engineer_module_timeline_adjust(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_timeline_adjust);

void _engineer_module_timeline_push(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_timeline_push);

void _engineer_module_timeline_pop(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_timeline_pop);

void _engineer_module_timeline_copy(Eo *obj, Engineer_Module_Data *pd, unsigned int cacheid, Engineer_Module_Frame *origin, Engineer_Module_Frame *destination);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_timeline_copy, EFL_FUNC_CALL(cacheid, origin, destination), unsigned int cacheid, Engineer_Module_Frame *origin, Engineer_Module_Frame *destination);

void _engineer_module_buffer_alloc(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_buffer_alloc);

void _engineer_module_buffer_free(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_module_buffer_free);

void _engineer_module_cache_add(Eo *obj, Engineer_Module_Data *pd, unsigned int componentid, HANDLE *data);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_cache_add, EFL_FUNC_CALL(componentid, data), unsigned int componentid, HANDLE *data);

void _engineer_module_cache_set(Eo *obj, Engineer_Module_Data *pd, Engineer_Module_Frame *frame, unsigned int cacheid, HANDLE *component);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_cache_set, EFL_FUNC_CALL(frame, cacheid, component), Engineer_Module_Frame *frame, unsigned int cacheid, HANDLE *component);

void _engineer_module_cache_lookup(Eo *obj, Engineer_Module_Data *pd, Engineer_Module_Frame *frame, unsigned int cacheid, HANDLE *component);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_cache_lookup, EFL_FUNC_CALL(frame, cacheid, component), Engineer_Module_Frame *frame, unsigned int cacheid, HANDLE *component);

void _engineer_module_cache_swap(Eo *obj, Engineer_Module_Data *pd, unsigned int componenta, unsigned int componentb);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_cache_swap, EFL_FUNC_CALL(componenta, componentb), unsigned int componenta, unsigned int componentb);

HANDLE *_engineer_module_handle_alloc(Eo *obj, Engineer_Module_Data *pd);

EOAPI EFL_FUNC_BODY(engineer_module_handle_alloc, HANDLE *, NULL);

void _engineer_module_handle_free(Eo *obj, Engineer_Module_Data *pd, HANDLE *target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_handle_free, EFL_FUNC_CALL(target), HANDLE *target);

unsigned int _engineer_module_component_create(Eo *obj, Engineer_Module_Data *pd, unsigned int parent);

EOAPI EFL_FUNC_BODYV(engineer_module_component_create, unsigned int, 0, EFL_FUNC_CALL(parent), unsigned int parent);

void _engineer_module_component_load(Eo *obj, Engineer_Module_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_component_load, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_module_component_save(Eo *obj, Engineer_Module_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_component_save, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_module_component_destroy(Eo *obj, Engineer_Module_Data *pd, unsigned int targetid);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_component_destroy, EFL_FUNC_CALL(targetid), unsigned int targetid);

void _engineer_module_component_dispose(Eo *obj, Engineer_Module_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_component_dispose, EFL_FUNC_CALL(target), unsigned int target);

void _engineer_module_component_lookup(Eo *obj, Engineer_Module_Data *pd, unsigned int timeoffset, unsigned int componentid, HANDLE *target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_module_component_lookup, EFL_FUNC_CALL(timeoffset, componentid, target), unsigned int timeoffset, unsigned int componentid, HANDLE *target);
EOAPI EFL_VOID_FUNC_BODYV_CONST(engineer_module_component_awake, EFL_FUNC_CALL(dt), unsigned long dt);
EOAPI EFL_VOID_FUNC_BODYV_CONST(engineer_module_component_start, EFL_FUNC_CALL(next, dt), HANDLE *next, unsigned long dt);
EOAPI EFL_VOID_FUNC_BODYV_CONST(engineer_module_component_update, EFL_FUNC_CALL(last, next, dt), HANDLE *last, HANDLE *next, unsigned long dt);

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
      EFL_OBJECT_OP_FUNC(engineer_module_timeline_adjust, _engineer_module_timeline_adjust),
      EFL_OBJECT_OP_FUNC(engineer_module_timeline_push, _engineer_module_timeline_push),
      EFL_OBJECT_OP_FUNC(engineer_module_timeline_pop, _engineer_module_timeline_pop),
      EFL_OBJECT_OP_FUNC(engineer_module_timeline_copy, _engineer_module_timeline_copy),
      EFL_OBJECT_OP_FUNC(engineer_module_buffer_alloc, _engineer_module_buffer_alloc),
      EFL_OBJECT_OP_FUNC(engineer_module_buffer_free, _engineer_module_buffer_free),
      EFL_OBJECT_OP_FUNC(engineer_module_cache_add, _engineer_module_cache_add),
      EFL_OBJECT_OP_FUNC(engineer_module_cache_set, _engineer_module_cache_set),
      EFL_OBJECT_OP_FUNC(engineer_module_cache_lookup, _engineer_module_cache_lookup),
      EFL_OBJECT_OP_FUNC(engineer_module_cache_swap, _engineer_module_cache_swap),
      EFL_OBJECT_OP_FUNC(engineer_module_handle_alloc, _engineer_module_handle_alloc),
      EFL_OBJECT_OP_FUNC(engineer_module_handle_free, _engineer_module_handle_free),
      EFL_OBJECT_OP_FUNC(engineer_module_component_create, _engineer_module_component_create),
      EFL_OBJECT_OP_FUNC(engineer_module_component_load, _engineer_module_component_load),
      EFL_OBJECT_OP_FUNC(engineer_module_component_save, _engineer_module_component_save),
      EFL_OBJECT_OP_FUNC(engineer_module_component_destroy, _engineer_module_component_destroy),
      EFL_OBJECT_OP_FUNC(engineer_module_component_dispose, _engineer_module_component_dispose),
      EFL_OBJECT_OP_FUNC(engineer_module_component_lookup, _engineer_module_component_lookup)
   );
   EFL_OPS_DEFINE(cops,
      EFL_OBJECT_OP_FUNC(engineer_module_factory, NULL),
      EFL_OBJECT_OP_FUNC(engineer_module_component_awake, NULL),
      EFL_OBJECT_OP_FUNC(engineer_module_component_start, NULL),
      EFL_OBJECT_OP_FUNC(engineer_module_component_update, NULL)
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
