#ifndef ENGINEER_SETTINGS_H_
#define ENGINEER_SETTINGS_H_

#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include <Elementary.h>
#include <Edi.h>

#include "gettext.h"
#include "Engineer.h"
#include "engineer_tabber.h"

#define PACKAGE_NAME "Engineer"

#define ENG_FONT_MIN 6
#define ENG_FONT_MAX 48

#define ENG_STATE_LIMIT(v, min, max) \
   if (v > max) v = max; else if (v < min) v = min;

#define ENG_STATE_DD_NEW(str, typ) \
   _eng_state_descriptor_new(str, sizeof(typ))

#define ENG_STATE_DD_FREE(eed) \
   if (eed) { eet_data_descriptor_free(eed); (eed) = NULL; }

#define ENG_STATE_VAL(edd, type, member, dtype) \
   EET_DATA_DESCRIPTOR_ADD_BASIC(edd, type, #member, member, dtype)

#define ENG_STATE_SUB(edd, type, member, eddtype) \
   EET_DATA_DESCRIPTOR_ADD_SUB(edd, type, #member, member, eddtype)

#define ENG_STATE_LIST(edd, type, member, eddtype) \
   EET_DATA_DESCRIPTOR_ADD_LIST(edd, type, #member, member, eddtype)

#define ENG_STATE_HASH(edd, type, member, eddtype) \
   EET_DATA_DESCRIPTOR_ADD_HASH(edd, type, #member, member, eddtype)

# define ENG_STATE_FILE_EPOCH 0x0003
# define ENG_STATE_FILE_GENERATION 0x000c
# define ENG_STATE_FILE_VERSION \
   ((ENG_STATE_FILE_EPOCH << 16) | ENG_STATE_FILE_GENERATION)

# define ENG_PROJECT_STATE_FILE_EPOCH 0x0001
# define ENG_PROJECT_STATE_FILE_GENERATION 0x0003
# define ENG_PROJECT_STATE_FILE_VERSION \
   ((ENG_PROJECT_STATE_FILE_EPOCH << 16) | ENG_PROJECT_STATE_FILE_GENERATION)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Eng_User_State        Eng_User_State;
typedef struct _Eng_Mime_State        Eng_Mime_State;
typedef struct _Eng_Project_State     Eng_Project_State;
typedef struct _Eng_Window_State      Eng_Window_State;
typedef struct _Eng_Tab_State         Eng_Tab_State;
typedef struct _Eng_Project_Tab_State Eng_Project_Tab_State;
typedef struct _Eng_Scene_Tab_State   Eng_Scene_Tab_State;


struct _Eng_User_State
{
   int        version;
   Eina_List *mime_assocs;
   Eina_List *windows;
   Eina_List *projects;
};

struct _Eng_Mime_State
{
   const char *id;
   const char *mime;
};

struct _Eng_Project_State
{
   int         version;
   Eina_Bool   open;
   const char *name;
   const char *path;
   Efl_Object *tab;
};

struct _Eng_Window_State
{
   char              *project;
   Eina_List         *tabs;

   Evas_Object       *widget;
   Efl_Object        *content;
   Efl_Object        *popup;
   Efl_Object        *toolbar;
   Elm_Object_Item   *scenetool;
   Elm_Object_Item   *materialtool;
   Elm_Object_Item   *modeltool;
   Engineer_Tabber   *tabber;
};

struct _Eng_Tab_State
{
   char *type;
   char *path;
};

typedef Eet_Data_Descriptor Eng_User_State_DD;
extern  Eng_User_State_DD *_eng_user_state_edd;
extern  Eng_User_State_DD *_eng_mime_state_edd;

typedef Eet_Data_Descriptor Eng_Project_State_DD;
extern  Eng_Project_State_DD *_eng_project_state_edd;

typedef Eet_Data_Descriptor Eng_Window_State_DD;
extern Eng_Window_State_DD *_eng_window_state_edd;

extern Eng_User_State *_eng_user_state;
extern int             ENG_EVENT_STATE_CHANGED;

Eet_Data_Descriptor *
_eng_state_descriptor_new(const char *name, int size);

// General configuration management
Eina_Bool
_eng_user_state_init(void);
Eina_Bool
_eng_user_state_shutdown(void);

// User state handling
void
_eng_user_state_load(void);
Eina_Bool
_eng_user_state_save(void);
void
_eng_user_state_free(void);

void
_eng_user_state_mime_add(const char *mime, const char* id);
const char*
_eng_user_state_mime_search(const char *mime);

#ifdef __cplusplus
}
#endif

#endif
