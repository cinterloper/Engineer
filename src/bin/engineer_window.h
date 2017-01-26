#ifndef ENGINEER_WINDOW_H_
#define ENGINEER_WINDOW_H_

//#define EFL_BETA_API_SUPPORT
#include <Elementary.h>

#include "engineer_project.h"
//#include "engineer_scene.h"

typedef struct _Eng_Project_Tab_State Eng_Project_Tab_State;
typedef struct _Eng_Scene_Tab_State Eng_Scene_Tab_State;
typedef struct _Eng_Material_Tab_State Eng_Material_Tab_State;
typedef struct _Eng_Model_Tab_State Eng_Model_Tab_State;

struct _Eng_Project_Tab_State
{
   const char *gitserver;
};

struct _Eng_Scene_Tab_State
{
   int        *version;
   const char *path;
   const char *name;
};

struct _Eng_Material_Tab_State
{
};

struct _Eng_Model_Tab_State
{
};

extern Eng_Window_State_DD *_eng_project_tab_state_edd;
extern Eng_Window_State_DD *_eng_scene_tab_state_edd;
extern Eng_Window_State_DD *_eng_material_tab_state_edd;
extern Eng_Window_State_DD *_eng_model_tab_state_edd;

//extern Eina_Inarray *projects;

Eina_Bool
_eng_window_state_init(void);
Eina_Bool
_eng_window_state_shutdown(void);

// Window state handling.
Eina_Bool
_eng_window_add(const char *path);

void
_eng_window_del_cb(void *data, const Efl_Event *event);

void
_eng_window_del(Eng_Window_State *target);

static void
_eng_editor_filetool_setup(Eng_Window_State *window);

static void
_eng_editor_scenetool_setup(Eng_Window_State *window);

static void
_eng_editor_materialtool_setup(Eng_Window_State *window);

static void
_eng_editor_modeltool_setup(Eng_Window_State *window);

// Tooltab state handling.
void
_eng_project_tab_add(const char *path);
void
_eng_project_tab_remove(const char *path);

void
_eng_scene_tab_add(const char *path);
void
_eng_scene_tab_remove(const char *path);

void
_eng_material_tab_add(const char *path);
void
_eng_material_tab_remove(const char *path);

void
_eng_model_tab_add(const char *path);
void
_eng_model_tab_remove(const char *path);

#endif

