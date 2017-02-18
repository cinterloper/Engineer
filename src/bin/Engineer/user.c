#include "engineer_user.h"

/*** Global Variables ***/
Eng_User_State_DD    *_eng_user_state_edd    = NULL;
Eng_User_State_DD    *_eng_mime_state_edd    = NULL;
//Eng_Window_State_DD  *_eng_window_state_edd  = NULL;
//Eng_Project_State_DD *_eng_project_state_edd = NULL;

Eng_User_State *_eng_user_state;
int             ENG_EVENT_STATE_CHANGED;

/* local functions */
Eet_Data_Descriptor *
_eng_state_descriptor_new(const char *name, int size)
{
   Eet_Data_Descriptor_Class eddc;

   if (!eet_eina_stream_data_descriptor_class_set(&eddc, sizeof(eddc),
                                                  name, size))
     return NULL;

   return (Eet_Data_Descriptor *)eet_data_descriptor_stream_new(&eddc);
}

/* external functions */
Eina_Bool
_eng_user_state_init(void)
{
   _eng_mime_state_edd = ENG_STATE_DD_NEW("Mime_State", Eng_Mime_State);
   #undef T
   #undef D
   #define T Eng_Mime_State
   #define D _eng_mime_state_edd
   ENG_STATE_VAL(D, T, id, EET_T_STRING);
   ENG_STATE_VAL(D, T, mime, EET_T_STRING);

   _eng_user_state_edd = ENG_STATE_DD_NEW("User_State", Eng_User_State);
   #undef T
   #undef D
   #define T Eng_User_State
   #define D _eng_user_state_edd
   ENG_STATE_VAL(D, T, version,      EET_T_INT);
   ENG_STATE_LIST(D, T, mime_assocs, _eng_mime_state_edd);
   ENG_STATE_LIST(D, T, windows,     _eng_window_state_edd);
   ENG_STATE_LIST(D, T, projects,    _eng_project_state_edd);

   return EINA_TRUE;
}

Eina_Bool
_eng_user_state_shutdown(void)
{
   ENG_STATE_DD_FREE(_eng_user_state_edd);
   ENG_STATE_DD_FREE(_eng_mime_state_edd);

   return EINA_TRUE;
}

void
_eng_user_state_load()
{
   Eina_Bool save = EINA_FALSE;

   char path[PATH_MAX];
   Eet_File *file;

   // The efreet_config_home_get() func will return "~/.config/".
   snprintf(path, sizeof(path), "%s/engineer/user.state", efreet_config_home_get());
   file = eet_open(path, EET_FILE_MODE_READ);
   if (file)
   {
      _eng_user_state = eet_data_read(file, _eng_user_state_edd, "user.state");
      eet_close(file);
   }

   if (_eng_user_state)
   {
      Eina_Bool reload = EINA_FALSE;

      if ((_eng_user_state->version >> 16) < ENG_STATE_FILE_EPOCH)
      {
         // config too old.
         reload = EINA_TRUE;
      }
      else if (_eng_user_state->version > ENG_STATE_FILE_VERSION)
      {
         // config too new?
         reload = EINA_TRUE;
      }

      /* if too old or too new, clear it so we can create new */
      if (reload) _eng_user_state_free();
   }
   else // if (!_eng_user_state)
   {
      _eng_user_state = calloc(1, sizeof(Eng_User_State));
      save = EINA_TRUE;

      /* define some convenient macros */
      #define IFCFG(v) if ((_eng_user_state->version & 0xffff) < (v)) {
      #define IFCFGELSE } else {
      #define IFCFGEND }

      /* setup defaults */
      IFCFG(0x000c);

      //_eng_global_state->autosave = EINA_TRUE;
      //_eng_global_state->trim_whitespace = EINA_TRUE;
      _eng_user_state->version = ENG_STATE_FILE_VERSION;
      _eng_user_state->mime_assocs = NULL;
      _eng_user_state->windows = NULL;
      _eng_user_state->projects = NULL;

      IFCFGEND;
   }

   if (save) _eng_user_state_save();
}

Eina_Bool
_eng_user_state_save(void)
{
   Eet_File *file = NULL;
   char path[PATH_MAX];
   char tmp[PATH_MAX];

   // The efreet_config_home_get() func will return "~/.config/".
   snprintf(path, sizeof(path), "%s/engineer", efreet_config_home_get());
   if (!ecore_file_is_dir(path)) ecore_file_mkpath(path);

   snprintf(tmp, sizeof(tmp), "%s/user.state.tmp", path);

   file = eet_open(tmp, EET_FILE_MODE_WRITE);
   if (file)
   {
      char state[PATH_MAX];
      snprintf(state, sizeof(state), "%s/user.state", path);
      if (!eet_data_write(file, _eng_user_state_edd, "user.state", _eng_user_state, 1))
      {
         eet_close(file);
         return EINA_FALSE;
      }
      if (eet_close(file) > 0) return EINA_FALSE;
      if (!ecore_file_mv(tmp, state)) return EINA_FALSE;

      ecore_event_add(ENG_EVENT_STATE_CHANGED, NULL, NULL, NULL);
      return EINA_TRUE;
   }
   return EINA_FALSE;
}

void
_eng_user_state_free(void)
{
   Eng_Project_State *project;
   Eng_Mime_State    *mime;

   EINA_LIST_FREE(_eng_user_state->projects, project)
   {
      if (project->name) eina_stringshare_del(project->name);
      if (project->path) eina_stringshare_del(project->path);
      free(project);
   }

   EINA_LIST_FREE(_eng_user_state->mime_assocs, mime)
   {
      if (mime->id)   eina_stringshare_del(mime->id);
      if (mime->mime) eina_stringshare_del(mime->mime);
      free(mime);
   }

   free(_eng_user_state);
   _eng_user_state = NULL;
}

void
_eng_user_state_mime_add(const char *mime, const char *id)
{
   Eng_Mime_State *mime_assoc;

   mime_assoc = malloc(sizeof(*mime_assoc));
   mime_assoc->id = eina_stringshare_add(id);
   mime_assoc->mime = eina_stringshare_add(mime);
   _eng_user_state->mime_assocs = eina_list_prepend(_eng_user_state->mime_assocs, mime_assoc);
   _eng_user_state_save();
}

const char *
_eng_user_state_mime_search(const char *mime)
{
   Eng_Mime_State *mime_assoc;
   Eina_List *list, *next;

   EINA_LIST_FOREACH_SAFE(_eng_user_state->mime_assocs, list, next, mime_assoc)
   {
      if (!strncmp(mime_assoc->mime, mime, strlen(mime_assoc->mime)))
      {
         return mime_assoc->id;
      }
   }
   return NULL;
}


