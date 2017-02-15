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

EOAPI Efl_Object *engineer_module_add(const Eo *obj);

EOAPI Efl_Object *engineer_module_efl_object_constructor(Eo *obj);

EOAPI void engineer_module_efl_object_destructor(Eo *obj);

EOAPI void engineer_module_iterate(Eo *obj);

EOAPI void engineer_module_respond(Eo *obj, Eina_Inarray *inbox, uint32_t offset);

EOAPI uint32_t engineer_module_cache_sizeof(Eo *obj);

EOAPI void engineer_module_cache_read(Eo *obj, COMPONENT *buffer, uint32_t index);

EOAPI void engineer_module_cache_write(Eo *obj, COMPONENT *buffer, uint32_t index);

EOAPI unsigned int engineer_module_component_create(Eo *obj, uint64_t id, uint64_t parent, COMPONENT *input);

EOAPI uint32_t engineer_module_component_lookup(Eo *obj, uint64_t componentid);

EOAPI void engineer_module_component_parent_set(Eo *obj, uint64_t target, uint64_t parent);

#endif
