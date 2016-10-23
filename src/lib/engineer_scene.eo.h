#ifndef _ENGINEER_SCENE_EO_H_
#define _ENGINEER_SCENE_EO_H_

#ifndef _ENGINEER_SCENE_EO_CLASS_TYPE
#define _ENGINEER_SCENE_EO_CLASS_TYPE

typedef Eo Engineer_Scene;

#endif

#ifndef _ENGINEER_SCENE_EO_TYPES
#define _ENGINEER_SCENE_EO_TYPES

typedef struct _Engineer_Scene_Module
{
  Efl_Object *handle;
  void *data;
} Engineer_Scene_Module;

typedef struct _Engineer_Scene_Entity
{
  unsigned int id;
  unsigned int sector;
  unsigned int status;
  unsigned int referencecount;
  const char *name;
  unsigned int parent;
  unsigned int siblingnext;
  unsigned int siblingprev;
  unsigned int firstcomponent;
  unsigned int firstentity;
} Engineer_Scene_Entity;

typedef struct _Engineer_Scene_Component
{
  unsigned int id;
  unsigned int type;
  unsigned int status;
  unsigned int referencecount;
  const char *name;
  unsigned int parent;
  unsigned int siblingnext;
  unsigned int siblingprev;
} Engineer_Scene_Component;

typedef struct _Engineer_Scene_Sector
{
  Engineer_Scene_Component *component;
  Eina_Inarray *cache;
  Eina_Hash *lookup;
  Efl_Loop_Timer *clock;
  unsigned int rate;
  unsigned int size;
} Engineer_Scene_Sector;

typedef struct _Engineer_Scene_Sector_Entry
{
  unsigned int rate;
  unsigned int size;
} Engineer_Scene_Sector_Entry;


#endif
#define ENGINEER_SCENE_CLASS engineer_scene_class_get()

EWAPI const Efl_Class *engineer_scene_class_get(void);

EOAPI void engineer_scene_game_set(Eo *obj, const char *path);

EOAPI const char *engineer_scene_game_get(const Eo *obj);

EOAPI void engineer_scene_name_set(Eo *obj, const char *name);

EOAPI const char *engineer_scene_name_get(const Eo *obj);

EOAPI void engineer_scene_entity_status_set(Eo *obj, unsigned int target, char mode);

EOAPI unsigned int engineer_scene_entity_status_get(const Eo *obj, unsigned int target);

EOAPI void engineer_scene_entity_parent_set(Eo *obj, unsigned int target, unsigned int parent);

EOAPI unsigned int engineer_scene_entity_parent_get(const Eo *obj, unsigned int target);

EOAPI Eina_Inarray *engineer_scene_entity_children_get(const Eo *obj, unsigned int target);

EOAPI Eina_Inarray *engineer_scene_entity_components_get(const Eo *obj, unsigned int target);

EOAPI void engineer_scene_component_status_set(Eo *obj, unsigned int target, char mode);

EOAPI unsigned int engineer_scene_component_status_get(const Eo *obj, unsigned int target);

EOAPI void engineer_scene_component_parent_set(Eo *obj, unsigned int target, unsigned int parent);

EOAPI unsigned int engineer_scene_component_parent_get(const Eo *obj, unsigned int target);

EOAPI Efl_Object *engineer_scene_efl_object_constructor(Eo *obj, char *path, char *name);

EOAPI void engineer_scene_efl_object_destructor(Eo *obj);

EOAPI void engineer_scene_file_load(Eo *obj);

EOAPI void engineer_scene_file_save(Eo *obj);

EOAPI void engineer_scene_file_sync(Eo *obj);

EOAPI unsigned int engineer_scene_entity_create(Eo *obj, unsigned int parent, const char *name);

EOAPI void engineer_scene_entity_destroy(Eo *obj, unsigned int target);

EOAPI void engineer_scene_entity_dispose(Eo *obj, unsigned int target);

EOAPI void engineer_scene_entity_load(Eo *obj, unsigned int target);

EOAPI void engineer_scene_entity_save(Eo *obj, unsigned int target);

EOAPI Engineer_Scene_Entity *engineer_scene_entity_lookup(Eo *obj, unsigned int target);

EOAPI void engineer_scene_entity_data_swap(Eo *obj, unsigned int targeta, unsigned int targetb);

EOAPI void engineer_scene_entity_sibling_swap(Eo *obj, unsigned int siblinga, unsigned int siblingb);

EOAPI unsigned int engineer_scene_entity_id_use(Eo *obj);

EOAPI void engineer_scene_entity_id_free(Eo *obj, unsigned int target);

EOAPI unsigned int engineer_scene_component_create(Eo *obj, unsigned int parent);

EOAPI void engineer_scene_component_destroy(Eo *obj, unsigned int target);

EOAPI void engineer_scene_component_dispose(Eo *obj, unsigned int target);

EOAPI void engineer_scene_component_load(Eo *obj, unsigned int target);

EOAPI void engineer_scene_component_save(Eo *obj, unsigned int target);

EOAPI Engineer_Scene_Component *engineer_scene_component_lookup(Eo *obj, unsigned int target);

EOAPI void engineer_scene_component_data_swap(Eo *obj, unsigned int targeta, unsigned int targetb);

EOAPI void engineer_scene_component_sibling_swap(Eo *obj, unsigned int siblinga, unsigned int siblingb);

EOAPI unsigned int engineer_scene_component_id_use(Eo *obj);

EOAPI void engineer_scene_component_id_free(Eo *obj, unsigned int target);

EOAPI unsigned int engineer_scene_sector_create(Eo *obj, unsigned int parent);

EOAPI void engineer_scene_sector_destroy(Eo *obj, unsigned int target);

EOAPI void engineer_scene_sector_dispose(Eo *obj, unsigned int target);

EOAPI void engineer_scene_sector_load(Eo *obj, unsigned int target);

EOAPI void engineer_scene_sector_save(Eo *obj, unsigned int target);

EOAPI Engineer_Scene_Sector *engineer_scene_sector_lookup(Eo *obj, unsigned int target);

EOAPI void engineer_scene_sector_data_swap(Eo *obj, unsigned int targeta, unsigned int targetb);

EOAPI extern const Efl_Event_Description _ENGINEER_SCENE_EVENT_SECTOR_ITERATE_CB;

/**
 * No description
 */
#define ENGINEER_SCENE_EVENT_SECTOR_ITERATE_CB (&(_ENGINEER_SCENE_EVENT_SECTOR_ITERATE_CB))

#endif
