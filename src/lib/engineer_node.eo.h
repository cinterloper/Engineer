#ifndef _ENGINEER_NODE_EO_H_
#define _ENGINEER_NODE_EO_H_

#ifndef _ENGINEER_NODE_EO_CLASS_TYPE
#define _ENGINEER_NODE_EO_CLASS_TYPE

typedef Eo Engineer_Node;

#endif

#ifndef _ENGINEER_NODE_EO_TYPES
#define _ENGINEER_NODE_EO_TYPES

typedef struct _Engineer_Node_Peer
{
  unsigned int ipaddress;
  const char *mode;
} Engineer_Node_Peer;

typedef struct _Engineer_Node_Module
{
  unsigned int id;
  void *class;
  void *create;
  void *load;
  void *save;
  void *destroy;
  void *lookup;
  void *factory;
  void *awake;
  void *start;
  void *update;
} Engineer_Node_Module;


#endif
#define ENGINEER_NODE_CLASS engineer_node_class_get()

EWAPI const Efl_Class *engineer_node_class_get(void);

EOAPI void engineer_node_path_set(Eo *obj, const char *path);

EOAPI const char *engineer_node_path_get(const Eo *obj);

EOAPI void engineer_node_title_set(Eo *obj, const char *title);

EOAPI const char *engineer_node_title_get(const Eo *obj);

EOAPI void engineer_node_file_load(Eo *obj);

EOAPI void engineer_node_file_save(Eo *obj);

EOAPI void engineer_node_file_close(Eo *obj);

EOAPI Efl_Object *engineer_node_scene_create(Eo *obj, Eina_Stringshare *name);

EOAPI Efl_Object *engineer_node_scene_load(Eo *obj, Eina_Stringshare *name);

EOAPI void engineer_node_scene_save(Eo *obj, Eina_Stringshare *name);

EOAPI void engineer_node_scene_unload(Eo *obj, Eina_Stringshare *name);

EOAPI unsigned int engineer_node_module_register(Eo *obj, Eina_Stringshare *name);

EOAPI void engineer_node_module_load(Eo *obj, Eina_Stringshare *file);

EOAPI void engineer_node_module_unload(Eo *obj, Efl_Object *target);

EOAPI void engineer_node_module_unregister(Eo *obj, const char *name);

EOAPI Engineer_Node_Module *engineer_node_module_lookup(Eo *obj, unsigned int target);

EOAPI Engineer_Node_Module *engineer_node_module_lookup_by_type(Eo *obj, const char *target);

EOAPI unsigned int engineer_node_module_id_use(Eo *obj);

EOAPI void engineer_node_module_id_free(Eo *obj, unsigned int target);

EOAPI unsigned int engineer_node_entity_id_use(Eo *obj);

EOAPI void engineer_node_entity_id_free(Eo *obj, unsigned int target);

EOAPI unsigned int engineer_node_entity_location_get(Eo *obj, unsigned int target);

EOAPI void engineer_node_entity_location_set(Eo *obj, unsigned int target, unsigned int location);

EOAPI unsigned int engineer_node_entity_status_get(Eo *obj, unsigned int target);

EOAPI void engineer_node_entity_status_set(Eo *obj, unsigned int target, char mode);

EOAPI unsigned int engineer_node_component_id_use(Eo *obj);

EOAPI void engineer_node_component_id_free(Eo *obj, unsigned int target);

EOAPI unsigned int engineer_node_component_location_get(Eo *obj, unsigned int target);

EOAPI void engineer_node_component_location_set(Eo *obj, unsigned int target, unsigned int location);

EOAPI unsigned int engineer_node_component_status_get(Eo *obj, unsigned int target);

EOAPI void engineer_node_component_status_set(Eo *obj, unsigned int target, char mode);

#endif
