
void _engineer_game_file_load(Eo *obj, Engineer_Game_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_game_file_load);

void _engineer_game_file_save(Eo *obj, Engineer_Game_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_game_file_save);

void _engineer_game_file_close(Eo *obj, Engineer_Game_Data *pd);

EOAPI EFL_VOID_FUNC_BODY(engineer_game_file_close);

void _engineer_game_module_load(Eo *obj, Engineer_Game_Data *pd, char *file);

EOAPI EFL_VOID_FUNC_BODYV(engineer_game_module_load, EFL_FUNC_CALL(file), char *file);

void _engineer_game_module_close(Eo *obj, Engineer_Game_Data *pd, Efl_Object *target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_game_module_close, EFL_FUNC_CALL(target), Efl_Object *target);

void _engineer_game_module_lookup(Eo *obj, Engineer_Game_Data *pd, unsigned int target);

EOAPI EFL_VOID_FUNC_BODYV(engineer_game_module_lookup, EFL_FUNC_CALL(target), unsigned int target);

Efl_Object * _engineer_game_efl_object_constructor(Eo *obj, Engineer_Game_Data *pd);


Efl_Object * _engineer_game_efl_object_finalize(Eo *obj, Engineer_Game_Data *pd);


void _engineer_game_efl_object_destructor(Eo *obj, Engineer_Game_Data *pd);


static Eina_Bool
_engineer_game_class_initializer(Efl_Class *klass)
{
   EFL_OPS_DEFINE(ops,
      EFL_OBJECT_OP_FUNC(efl_constructor, _engineer_game_efl_object_constructor),
      EFL_OBJECT_OP_FUNC(efl_finalize, _engineer_game_efl_object_finalize),
      EFL_OBJECT_OP_FUNC(efl_destructor, _engineer_game_efl_object_destructor),
      EFL_OBJECT_OP_FUNC(engineer_game_file_load, _engineer_game_file_load),
      EFL_OBJECT_OP_FUNC(engineer_game_file_save, _engineer_game_file_save),
      EFL_OBJECT_OP_FUNC(engineer_game_file_close, _engineer_game_file_close),
      EFL_OBJECT_OP_FUNC(engineer_game_module_load, _engineer_game_module_load),
      EFL_OBJECT_OP_FUNC(engineer_game_module_close, _engineer_game_module_close),
      EFL_OBJECT_OP_FUNC(engineer_game_module_lookup, _engineer_game_module_lookup)
   );

   return efl_class_functions_set(klass, &ops, NULL);
}

static const Efl_Class_Description _engineer_game_class_desc = {
     EO_VERSION,
     "Engineer_Game",
     EFL_CLASS_TYPE_REGULAR,
     sizeof(Engineer_Game_Data),
     _engineer_game_class_initializer,
     NULL,
     NULL
};

EFL_DEFINE_CLASS(engineer_game_class_get, &_engineer_game_class_desc, EFL_OBJECT_CLASS, NULL);