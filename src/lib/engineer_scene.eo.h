#ifndef _ENGINEER_SCENE_EO_H_
#define _ENGINEER_SCENE_EO_H_

#ifndef _ENGINEER_SCENE_EO_CLASS_TYPE
#define _ENGINEER_SCENE_EO_CLASS_TYPE

typedef Eo Engineer_Scene;

#endif

#ifndef _ENGINEER_SCENE_EO_TYPES
#define _ENGINEER_SCENE_EO_TYPES

typedef struct _Engineer_Scene_Entity
{
  unsigned int id;
  Eina_Stringshare *name;
  unsigned int parent;
  unsigned int siblingnext;
  unsigned int siblingprev;
  unsigned int firstcomponent;
  unsigned int firstentity;
} Engineer_Scene_Entity;

typedef struct _Engineer_Scene_Component
{
  unsigned int id;
  Eina_Stringshare *name;
  unsigned int type;
  unsigned int parent;
  unsigned int siblingnext;
  unsigned int siblingprev;
} Engineer_Scene_Component;


#endif
#define ENGINEER_SCENE_CLASS engineer_scene_class_get()

EWAPI const Efl_Class *engineer_scene_class_get(void);

EOAPI void engineer_scene_name_set(Eo *obj, const char *name);

EOAPI const char *engineer_scene_name_get(const Eo *obj);

EOAPI Efl_Object *engineer_scene_efl_object_constructor(Eo *obj);

EOAPI void engineer_scene_efl_object_destructor(Eo *obj);

EOAPI Eina_Bool engineer_scene_iterate(Eo *obj);

EOAPI Eina_Bool engineer_scene_iterate_module(Eo *obj, unsigned int *key);

EOAPI Eina_Bool engineer_scene_iterate_entity(Eo *obj, void *key, void *data);

EOAPI Eina_Bool engineer_scene_iterate_component(Eo *obj, void *key, void *data);

EOAPI void engineer_scene_timeline_adjust(Eo *obj);

EOAPI void engineer_scene_timeline_push(Eo *obj);

EOAPI void engineer_scene_timeline_pop(Eo *obj);

EOAPI unsigned int engineer_scene_entity_create(Eo *obj, unsigned int parent, const char *name);

EOAPI void engineer_scene_entity_destroy(Eo *obj, unsigned int target);

EOAPI void engineer_scene_entity_dispose(Eo *obj, unsigned int target);

EOAPI void engineer_scene_entity_load(Eo *obj, unsigned int target);

EOAPI void engineer_scene_entity_save(Eo *obj, unsigned int target);

EOAPI Engineer_Scene_Entity *engineer_scene_entity_lookup(Eo *obj, unsigned int target);

EOAPI void engineer_scene_entity_data_swap(Eo *obj, unsigned int targeta, unsigned int targetb);

EOAPI unsigned int engineer_scene_entity_parent_get(Eo *obj, unsigned int target);

EOAPI void engineer_scene_entity_parent_set(Eo *obj, unsigned int target, unsigned int parent);

EOAPI void engineer_scene_entity_sibling_swap(Eo *obj, unsigned int siblinga, unsigned int siblingb);

EOAPI Eina_Inarray *engineer_scene_entity_children_get(Eo *obj, unsigned int target);

EOAPI Eina_Inarray *engineer_scene_entity_components_get(Eo *obj, unsigned int target);

EOAPI unsigned int engineer_scene_component_create(Eo *obj, Eina_Stringshare *type, unsigned int parent);

EOAPI void engineer_scene_component_destroy(Eo *obj, unsigned int target);

EOAPI void engineer_scene_component_dispose(Eo *obj, unsigned int target);

EOAPI void engineer_scene_component_load(Eo *obj, unsigned int target);

EOAPI void engineer_scene_component_save(Eo *obj, unsigned int target);

EOAPI Engineer_Scene_Component *engineer_scene_component_lookup(Eo *obj, unsigned int target);

EOAPI void engineer_scene_component_data_swap(Eo *obj, unsigned int targeta, unsigned int targetb);

EOAPI unsigned int engineer_scene_component_parent_get(Eo *obj, unsigned int target);

EOAPI void engineer_scene_component_parent_set(Eo *obj, unsigned int target, unsigned int parent);

EOAPI void engineer_scene_component_sibling_swap(Eo *obj, unsigned int siblinga, unsigned int siblingb);

EWAPI extern const Efl_Event_Description _ENGINEER_SCENE_EVENT_SECTOR_ITERATE_CB;

/**
 * No description
 */
#define ENGINEER_SCENE_EVENT_SECTOR_ITERATE_CB (&(_ENGINEER_SCENE_EVENT_SECTOR_ITERATE_CB))

#endif
