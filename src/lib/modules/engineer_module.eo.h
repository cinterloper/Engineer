#ifndef _ENGINEER_MODULE_EO_H_
#define _ENGINEER_MODULE_EO_H_

#ifndef _ENGINEER_MODULE_EO_CLASS_TYPE
#define _ENGINEER_MODULE_EO_CLASS_TYPE

typedef Eo Engineer_Module;

#endif

#ifndef _ENGINEER_MODULE_EO_TYPES
#define _ENGINEER_MODULE_EO_TYPES


#endif
#define ENGINEER_MODULE_CLASS engineer_module_class_get()

EWAPI const Efl_Class *engineer_module_class_get(void);

EOAPI Efl_Object *engineer_module_efl_object_constructor(Eo *obj);

EOAPI void engineer_module_efl_object_destructor(Eo *obj);

EOAPI void engineer_module_iterate(Eo *obj);

EOAPI void engineer_module_timeline_adjust(Eo *obj);

EOAPI void engineer_module_timeline_push(Eo *obj);

EOAPI void engineer_module_timeline_pop(Eo *obj);

EOAPI void engineer_module_timeline_copy(Eo *obj, unsigned int cacheid, Engineer_Module_Frame *origin, Engineer_Module_Frame *destination);

EOAPI void engineer_module_buffer_alloc(Eo *obj);

EOAPI void engineer_module_buffer_free(Eo *obj);

EOAPI void engineer_module_cache_push(Eo *obj, unsigned int componentid, HANDLE *data);

EOAPI void engineer_module_cache_copy(Eo *obj, Engineer_Module_Frame *frame, unsigned int cacheid, HANDLE *component);

EOAPI void engineer_module_cache_lookup(Eo *obj, Engineer_Module_Frame *frame, unsigned int cacheid, HANDLE *component);

EOAPI void engineer_module_cache_swap(Eo *obj, unsigned int componenta, unsigned int componentb);

EOAPI HANDLE *engineer_module_handle_alloc(Eo *obj);

EOAPI void engineer_module_handle_free(Eo *obj, HANDLE *target);

EOAPI unsigned int engineer_module_component_create(Eo *obj, unsigned int parent);

EOAPI void engineer_module_component_load(Eo *obj, unsigned int target);

EOAPI void engineer_module_component_save(Eo *obj, unsigned int target);

EOAPI void engineer_module_component_destroy(Eo *obj, unsigned int targetid);

EOAPI void engineer_module_component_dispose(Eo *obj, unsigned int target);

EOAPI void engineer_module_component_lookup(Eo *obj, unsigned int timeoffset, unsigned int componentid, HANDLE *target);

EOAPI Efl_Object *engineer_module_factory(const Eo *obj);

EOAPI void engineer_module_awake(const Eo *obj, unsigned long dt);

EOAPI void engineer_module_start(const Eo *obj, HANDLE *next, unsigned long dt);

EOAPI void engineer_module_update(const Eo *obj, HANDLE *last, HANDLE *next, unsigned long dt);

#endif
