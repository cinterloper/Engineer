#ifndef _ENGINEER_SCENE_EO_H_
#define _ENGINEER_SCENE_EO_H_

#ifndef _ENGINEER_SCENE_EO_CLASS_TYPE
#define _ENGINEER_SCENE_EO_CLASS_TYPE

typedef Eo Engineer_Scene;

#endif

#ifndef _ENGINEER_SCENE_EO_TYPES
#define _ENGINEER_SCENE_EO_TYPES


#endif
#define ENGINEER_SCENE_CLASS engineer_scene_class_get()

EWAPI const Efl_Class *engineer_scene_class_get(void);

EOAPI Efl_Object *engineer_scene_efl_object_constructor(Eo *obj);

EOAPI Efl_Object *engineer_scene_efl_object_finalize(Eo *obj);

EOAPI void engineer_scene_efl_object_destructor(Eo *obj);

EOAPI void engineer_scene_name_set(Eo *obj, const char *name);

EOAPI const char *engineer_scene_name_get(const Eo *obj);

EOAPI Efl_Object *engineer_scene_module_get(const Eo *obj, uint64_t *classid);

EOAPI Eina_Bool engineer_scene_iterate(Eo *obj);

EOAPI void engineer_scene_respond(Eo *obj, Eina_Inarray *inboxs, uint32_t offset);

EOAPI Eina_Bool engineer_scene_entity_create(Eo *obj, uint64_t id, uint64_t parent, const char *name);

EOAPI uint32_t engineer_scene_entity_lookup(Eo *obj, uint64_t target);

EOAPI void engineer_scene_entity_parent_set(Eo *obj, uint64_t target, uint64_t parent);

EOAPI Eina_Inarray *engineer_scene_entity_inbox_get(Eo *obj, uint64_t entityid);

EOAPI Eina_Inarray *engineer_scene_entity_outbox_get(Eo *obj, uint64_t entityid);

EOAPI void engineer_scene_notice_push_response_request(Eo *obj, uint64_t sender, uint64_t response, uint64_t entityid, void *payload, uint32_t size);

EOAPI void engineer_scene_notice_push_entity_create(Eo *obj, uint64_t sender, uint64_t entityid, uint64_t parent);

EOAPI void engineer_scene_notice_push_component_create(Eo *obj, uint64_t sender, uint64_t classid, uint64_t componentid, uint64_t parent, uint64_t *payload);

EWAPI extern const Efl_Event_Description _ENGINEER_SCENE_EVENT_ITERATE_CB;

/**
 * No description
 */
#define ENGINEER_SCENE_EVENT_ITERATE_CB (&(_ENGINEER_SCENE_EVENT_ITERATE_CB))

#endif
