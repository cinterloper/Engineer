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

EOAPI void engineer_game_file_load(Eo *obj);

EOAPI void engineer_game_file_save(Eo *obj);

EOAPI void engineer_game_file_close(Eo *obj);

EOAPI void engineer_game_module_load(Eo *obj, char *file);

EOAPI void engineer_game_module_close(Eo *obj, Efl_Object *target);

EOAPI void engineer_game_module_lookup(Eo *obj, unsigned int target);


#endif
