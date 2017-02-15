#ifndef _ENGINEER_NODE_EO_H_
#define _ENGINEER_NODE_EO_H_

#ifndef _ENGINEER_NODE_EO_CLASS_TYPE
#define _ENGINEER_NODE_EO_CLASS_TYPE

typedef Eo Engineer_Node;

#endif

#ifndef _ENGINEER_NODE_EO_TYPES
#define _ENGINEER_NODE_EO_TYPES

typedef struct _Engineer_Module_Class
{
  void *eina;
  Eina_Stringshare *id;
  uint64_t size;
  void *factory;
  void *iterate;
  void *component_create;
  void *component_destroy;
  void *component_archive;
  void *component_recall;
  void *component_sizeof;
  void *component_lookup;
} Engineer_Module_Class;

typedef struct _Engineer_Node_Peer
{
  unsigned int ipaddress;
  const char *mode;
} Engineer_Node_Peer;


#endif
#define ENGINEER_NODE_CLASS engineer_node_class_get()

EWAPI const Efl_Class *engineer_node_class_get(void);

EOAPI void engineer_node_path_set(Eo *obj, const char *path);

EOAPI const char *engineer_node_path_get(const Eo *obj);

EOAPI void engineer_node_title_set(Eo *obj, const char *title);

EOAPI const char *engineer_node_title_get(const Eo *obj);

EOAPI Eina_Stringshare *engineer_node_module_load(Eo *obj, const char *class);

EOAPI Engineer_Module_Class *engineer_node_module_class_lookup(Eo *obj, uint64_t target);

EOAPI uint64_t engineer_node_entity_id_use(Eo *obj);

EOAPI void engineer_node_entity_id_free(Eo *obj, uint64_t target);

EOAPI uint32_t engineer_node_entity_location_get(Eo *obj, uint64_t target);

EOAPI void engineer_node_entity_location_set(Eo *obj, uint64_t target, uint32_t location);

EOAPI uint32_t engineer_node_entity_status_get(Eo *obj, uint64_t target);

EOAPI void engineer_node_entity_status_set(Eo *obj, uint64_t target, char mode);

EOAPI uint64_t engineer_node_component_id_use(Eo *obj);

EOAPI void engineer_node_component_id_free(Eo *obj, uint64_t target);

EOAPI uint32_t engineer_node_component_location_get(Eo *obj, uint64_t target);

EOAPI void engineer_node_component_location_set(Eo *obj, uint64_t target, uint32_t location);

EOAPI uint32_t engineer_node_component_status_get(Eo *obj, uint64_t target);

EOAPI void engineer_node_component_status_set(Eo *obj, uint64_t target, char mode);

#endif
