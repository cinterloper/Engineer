#ifndef _ENGINEER_VIEWPORT_EO_H_
#define _ENGINEER_VIEWPORT_EO_H_

#ifndef _ENGINEER_VIEWPORT_EO_CLASS_TYPE
#define _ENGINEER_VIEWPORT_EO_CLASS_TYPE

typedef Eo Engineer_Viewport;

#endif

#ifndef _ENGINEER_VIEWPORT_EO_TYPES
#define _ENGINEER_VIEWPORT_EO_TYPES


#endif
#define ENGINEER_VIEWPORT_CLASS engineer_viewport_class_get()

EWAPI const Efl_Class *engineer_viewport_class_get(void);

EOAPI void engineer_viewport_alpha_set(Eo *obj, char alpha);

EOAPI char engineer_viewport_alpha_get(const Eo *obj);

EOAPI void engineer_viewport_camera_set(Eo *obj, unsigned int camera);

EOAPI unsigned int engineer_viewport_camera_get(const Eo *obj);

#endif
