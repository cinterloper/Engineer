#ifndef ENGINEER_PROJECT_H_
#define ENGINEER_PROJECT_H_

#define EFL_BETA_API_SUPPORT
#include <Elementary.h>

#include "engineer_user.h"

typedef struct
{
  Eng_Window_State *window;
  Evas_Object      *path;
  Evas_Object      *name;
  Evas_Object      *url;
  Evas_Object      *creator;
  Evas_Object      *email;
}
Eng_Project_Creator_State;

typedef struct
{
   Eng_Window_State *window;
   Eng_Window_State *target;
   Evas_Object      *path;
}
Eng_Project_Loader_State;

typedef struct
{
   Eng_Window_State *window;
   Evas_Object      *path;
}
Eng_Project_Saver_State;

typedef struct
{
   Eng_Window_State *window;
   Evas_Object      *path;
}
Eng_Project_Closer_State;


/*** Project State Manipulation ***/

Eina_Bool
_eng_project_state_init(void);

Eina_Bool
_eng_project_state_shutdown(void);

Eng_Project_State *
_eng_project_state_add(const char *path);

void
_eng_project_state_del(const char *path);


/*** Project Management Funcs ***/

void
_eng_project_create_cb(void *data, const Efl_Event *event);

static Eina_Bool
_eng_project_create(Eng_Project_Creator_State *input);

void
_eng_project_load_cb(void *data, const Efl_Event *event);

static Eng_Project_State *
_eng_project_load(const char *path, Eng_Window_State *target);

void
_eng_project_save_cb(void *data, const Efl_Event *event);

static Eina_Bool
_eng_project_save(const char *path);

void
_eng_project_close_cb(void *data, const Efl_Event *event);

static Eina_Bool
_eng_project_close(const char *path);


/*** Project Management GUI Popups ***/

void
_eng_project_creator_popup_add_cb(void *data, const Efl_Event *event);

static Evas_Object *
_eng_project_creator_popup_add(Eng_Window_State *window);

void
_eng_project_loader_popup_add_cb(void *data, const Efl_Event *event);

static Evas_Object *
_eng_project_loader_popup_add(Eng_Window_State *window);

void
_eng_project_saver_popup_add_cb(void *data, const Efl_Event *event);

static Evas_Object *
_eng_project_saver_popup_add(Eng_Window_State *window);

void
_eng_project_closer_popup_add_cb(void *data, const Efl_Event *event);

static Evas_Object *
_eng_project_closer_popup_add(Eng_Window_State *window);


/*** Other Funcs ***/

void
_eng_window_popup_cancel_cb(void *data, const Efl_Event *event);

static void
_eng_window_popup_cancel(Eng_Window_State *window);

void
_eng_window_project_set(Eng_Window_State *target, const char *path);

void
_donothing_cb(void *data, const Efl_Event *event);

#endif
