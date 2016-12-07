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

EOAPI void engineer_module_data_add(Eo *obj, unsigned int componentid, void *data);

EOAPI void engineer_module_data_set(Eo *obj, unsigned int cacheid, void *target);

EOAPI void engineer_module_data_get(Eo *obj, unsigned int cacheid, void *target);

EOAPI void engineer_module_data_swap(Eo *obj, unsigned int componenta, unsigned int componentb);

EOAPI unsigned int engineer_module_component_create(Eo *obj, unsigned int parent);

EOAPI void engineer_module_component_destroy(Eo *obj, unsigned int targetid);

EOAPI void engineer_module_component_load(Eo *obj);

EOAPI void engineer_module_component_save(Eo *obj);

EOAPI Efl_Object *engineer_module_add(const Eo *obj);

EOAPI void engineer_module_component_awake(const Eo *obj, unsigned long dt);

EOAPI void engineer_module_component_start(const Eo *obj, void *com, unsigned long dt);

EOAPI void engineer_module_component_update(const Eo *obj, void *com, unsigned long dt);

#endif
