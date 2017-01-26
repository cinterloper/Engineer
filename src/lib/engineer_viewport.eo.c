
Efl_Object *_engineer_viewport_efl_object_constructor(Eo *obj, Engineer_Viewport_Data *pd);


Efl_Object *_engineer_viewport_efl_object_finalize(Eo *obj, Engineer_Viewport_Data *pd);


void _engineer_viewport_efl_object_destructor(Eo *obj, Engineer_Viewport_Data *pd);


void _engineer_viewport_alpha_set(Eo *obj, Engineer_Viewport_Data *pd, char alpha);

EOAPI EFL_VOID_FUNC_BODYV(engineer_viewport_alpha_set, EFL_FUNC_CALL(alpha), char alpha);

char _engineer_viewport_alpha_get(Eo *obj, Engineer_Viewport_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(engineer_viewport_alpha_get, char, 0);

void _engineer_viewport_camera_set(Eo *obj, Engineer_Viewport_Data *pd, unsigned int camera);

EOAPI EFL_VOID_FUNC_BODYV(engineer_viewport_camera_set, EFL_FUNC_CALL(camera), unsigned int camera);

unsigned int _engineer_viewport_camera_get(Eo *obj, Engineer_Viewport_Data *pd);

EOAPI EFL_FUNC_BODY_CONST(engineer_viewport_camera_get, unsigned int, 0);

static Eina_Bool
_engineer_viewport_class_initializer(Efl_Class *klass)
{
   EFL_OPS_DEFINE(ops,
      EFL_OBJECT_OP_FUNC(efl_constructor, _engineer_viewport_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(efl_finalize, _engineer_viewport_efl_object_finalize),
      EFL_OBJECT_OP_FUNC(efl_destructor, _engineer_viewport_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_viewport_alpha_set, _engineer_viewport_alpha_set),
      EFL_OBJECT_OP_FUNC(engineer_viewport_alpha_get, _engineer_viewport_alpha_get),
      EFL_OBJECT_OP_FUNC(engineer_viewport_camera_set, _engineer_viewport_camera_set),
      EFL_OBJECT_OP_FUNC(engineer_viewport_camera_get, _engineer_viewport_camera_get)
   );
   return efl_class_functions_set(klass, &ops, NULL);
}

static const Efl_Class_Description _engineer_viewport_class_desc = {
   EO_VERSION,
   "Engineer.Viewport",
   EFL_CLASS_TYPE_REGULAR,
   sizeof(Engineer_Viewport_Data),
   _engineer_viewport_class_initializer,
   NULL,
   NULL
};

EFL_DEFINE_CLASS(engineer_viewport_class_get, &_engineer_viewport_class_desc, EFL_UI_IMAGE_CLASS, NULL);
