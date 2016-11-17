#ifndef _ENGINEER_GAME_EO_H_
#define _ENGINEER_GAME_EO_H_

#ifndef _ENGINEER_GAME_EO_CLASS_TYPE
#define _ENGINEER_GAME_EO_CLASS_TYPE

typedef Eo Engineer_Game;

#endif

#ifndef _ENGINEER_GAME_EO_TYPES
#define _ENGINEER_GAME_EO_TYPES

typedef struct _Engineer_Game_Node
{
  void *ipaddress;
  const char *mode;
} Engineer_Game_Node;

typedef struct _Engineer_Game_Module
{
  unsigned int id;
  void *handle;
  void *add;
  void *load;
  void *save;
  void *del;
  void *awake;
  void *start;
  void *update;
} Engineer_Game_Module;


#endif
#define ENGINEER_GAME_CLASS engineer_game_class_get()

EWAPI const Efl_Class *engineer_game_class_get(void);

EOAPI void engineer_game_path_set(Eo *obj, const char *path);

EOAPI const char *engineer_game_path_get(const Eo *obj);

EOAPI void engineer_game_title_set(Eo *obj, const char *title);

EOAPI const char *engineer_game_title_get(const Eo *obj);

EOAPI void engineer_game_file_load(Eo *obj);

EOAPI void engineer_game_file_save(Eo *obj);

EOAPI void engineer_game_file_close(Eo *obj);

EOAPI void engineer_game_scene_create(Eo *obj, const char *name);

EOAPI void engineer_game_scene_load(Eo *obj, const char *name);

EOAPI void engineer_game_scene_save(Eo *obj, const char *name);

EOAPI void engineer_game_scene_unload(Eo *obj, const char *name);

EOAPI void engineer_game_module_register(Eo *obj, const char *name);

EOAPI void engineer_game_module_load(Eo *obj, const char *file);

EOAPI void engineer_game_module_unload(Eo *obj, Efl_Object *target);

EOAPI void engineer_game_module_unregister(Eo *obj, const char *name);

EOAPI char *engineer_game_module_lookup(Eo *obj, unsigned int target);

EOAPI unsigned int engineer_game_module_id_use(Eo *obj);

EOAPI void engineer_game_module_id_free(Eo *obj, unsigned int target);


#endif
