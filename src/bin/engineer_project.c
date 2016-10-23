#include "engineer_project.h"

Eng_Project_State_DD *_eng_project_state_edd = NULL;

Eina_Bool
_eng_project_state_init(void)
{
   _eng_project_state_edd = ENG_STATE_DD_NEW("Project_State", Eng_Project_State);
   #undef T
   #undef D
   #define T Eng_Project_State
   #define D _eng_project_state_edd
   ENG_STATE_VAL(D, T, version, EET_T_INT);
   ENG_STATE_VAL(D, T, open,    EET_T_INT);
   ENG_STATE_VAL(D, T, path,    EET_T_STRING);
   ENG_STATE_VAL(D, T, name,    EET_T_STRING);

   return EINA_TRUE;
}

Eina_Bool
_eng_project_state_shutdown(void)
{
   ENG_STATE_DD_FREE(_eng_project_state_edd);

   return EINA_TRUE;
}

Eng_Project_State *
_eng_project_state_add(const char *path)
{
   Eng_Project_State *project;
   Eina_List *list, *next;

   // If the project already exists in the list, return NULL.
   EINA_LIST_FOREACH_SAFE(_eng_user_state->projects, list, next, project)
   {
       if (!strncmp(project->path, path, strlen(project->path))) return NULL;
   }

   project = malloc(sizeof(*project));
   project->open = EINA_FALSE;
   project->path = eina_stringshare_add(path);
   project->name = eina_stringshare_add(basename((char*) path));
   _eng_user_state->projects = eina_list_prepend(_eng_user_state->projects, project);
   _eng_user_state_save();
   return project;
}

void
_eng_project_state_del(const char *path)
{
   Eng_Project_State *project;
   Eina_List *list, *next;

   // If the project already exists in the list, remove it.
   EINA_LIST_FOREACH_SAFE(_eng_user_state->projects, list, next, project)
   {
       if (!strncmp(project->path, path, strlen(project->path)))
       _eng_user_state->projects = eina_list_remove_list(_eng_user_state->projects, list);
   }
   free(project);
   _eng_user_state_save();
}

void
_eng_project_create_cb(void *data, const Efl_Event *event)
{
   _eng_project_create(data);
}

static Eina_Bool
_eng_project_create(Eng_Project_Creator_State *input)
{
   char path[PATH_MAX], name[PATH_MAX], url[PATH_MAX], creator[PATH_MAX], email[PATH_MAX];

   snprintf(path,    sizeof(path),    "%s", elm_fileselector_selected_get(input->path));
   snprintf(name,    sizeof(name),    "%s", elm_object_text_get(input->name));
   snprintf(url,     sizeof(url),     "%s", elm_object_text_get(input->url));
   snprintf(creator, sizeof(creator), "%s", elm_object_text_get(input->creator));
   snprintf(email,   sizeof(email),   "%s", elm_object_text_get(input->email));

   if (name    && name[0]    &&
       url     && url[0]     &&
       creator && creator[0] &&
       email   && email[0]
      )
   {
      edi_create_efl_project(path, name, url, creator, email, _donothing_cb);
      if (input->window->popup) _eng_window_popup_cancel(input->window);

      char loadpath[PATH_MAX];
      snprintf(loadpath, sizeof(loadpath), "%s/%s", path, name);
      printf("_eng_project_create() Checkpoint, loadpath == %s \n", loadpath);
      _eng_project_load(loadpath, input->window);

      free(input);
      return EINA_TRUE;
   }
   else return EINA_FALSE;
}

void
_eng_project_load_cb(void *data, const Efl_Event *event)
{
   Eng_Project_Loader_State *loader = data;
   char *path = elm_fileselector_selected_get(loader->path);

   _eng_project_load(path, loader->target);
   _eng_window_popup_cancel(loader->window);
   free(loader);
}

static Eng_Project_State *
_eng_project_load(const char *path, Eng_Window_State *target)
{
   printf("_eng_project_load() checkpoint, path == %s \n", path);
   Eng_Project_State *project;
   Eng_Window_State *window;
   Eina_List *list, *next;

   // If the project dir path is not valid, return null.
   if (!ecore_file_is_dir(path)) return NULL;

   // If the project doesn't exist in the user project_state list, create it.
   EINA_LIST_FOREACH_SAFE(_eng_user_state->projects, list, next, project)
   {
      if (!strncmp(project->path, path, strlen(path))) break;
      project = NULL;
   }
   if (!project) project = _eng_project_state_add(path);

   // Add the loaded project path to the target window.
   if (target != NULL) _eng_window_project_set(target, path);

   // Now we need to show any listed project windows, or create one if there is not any.
   Eina_Bool headless = EINA_TRUE;
   EINA_LIST_FOREACH_SAFE(_eng_user_state->windows, list, next, window)
   {
      if (window->project == path)
      {
         evas_object_show(window->widget);
         headless = EINA_FALSE;
      }
   }
   if (headless && target == NULL) _eng_window_add(path);

   project->open = EINA_TRUE;
   return project;
}

void
_eng_project_save_cb(void *data, const Efl_Event *event)
{
}

static Eina_Bool
_eng_project_save(const char *path)
{
   return EINA_FALSE;
}

void
_eng_project_close_cb(void *data, const Efl_Event *event)
{
   _eng_project_close(data);
}

static Eina_Bool
_eng_project_close(const char *path)
{
   Eng_Project_State *project;
   Eng_Window_State *window;
   Eina_List *list, *next;

   // Find the project in the user project_state list, and hide it's windows.
   EINA_LIST_FOREACH_SAFE(_eng_user_state->projects, list, next, project)
   {
      if (!strncmp(project->path, path, strlen(project->path))) break;
      project = NULL;
   }
   if (!project) return EINA_FALSE;

   // Now we need to hide any listed project windows.
   EINA_LIST_FOREACH_SAFE(_eng_user_state->windows, list, next, window)
   {
      if (window->project == project) evas_object_hide(window->widget);
   }

   project->open = EINA_FALSE;
   return EINA_TRUE;
}

static void
_eng_project_save_close_cb(void *data, const Efl_Event *event)
{
   evas_object_del(data);
}

void
_eng_project_resolve_popup_add_cb(void *data, const Efl_Event *event)
{
   _eng_project_resolve_popup_add(data);
}

void
_eng_project_resolve_popup_add(Eng_Window_State *window)
{
   if (window->popup == NULL && window->project != NULL)
   {
      Evas_Object *content, *label, *button;
      window->popup = elm_popup_add(window->content);
      content = elm_box_add(window->popup);
      elm_object_content_set(window->popup, content);

      label = elm_label_add(window->popup);
      elm_object_text_set(label, "<align=center>There is already an open project in this window!");
      evas_object_size_hint_padding_set(label, 8, 8, 4, 4);
      evas_object_size_hint_align_set(label, EVAS_HINT_FILL, 0.0);
      elm_box_pack_end(content, label);
      evas_object_show(label);

      button = elm_button_add(window->popup);
      elm_object_text_set(button, "Open project in a new window.");
      evas_object_smart_callback_add(button, "clicked", _donothing_cb, window);
      evas_object_size_hint_padding_set(button, 4, 4, 4, 2);
      evas_object_size_hint_align_set(button, EVAS_HINT_FILL, 0.0);
      elm_box_pack_end(content, button);
      evas_object_show(button);

      button = elm_button_add(window->popup);
      elm_object_text_set(button, "Save and close the current project.");
      evas_object_smart_callback_add(button, "clicked", _eng_project_save_close_cb, window->popup);
      evas_object_size_hint_padding_set(button, 4, 4, 2, 2);
      evas_object_size_hint_align_set(button, EVAS_HINT_FILL, 0.0);
      elm_box_pack_end(content, button);
      evas_object_show(button);

      button = elm_button_add(window->popup);
      elm_object_text_set(button, "Cancel.");
      evas_object_smart_callback_add(button, "clicked", _eng_window_popup_cancel_cb, window->popup);
      evas_object_size_hint_padding_set(button, 4, 4, 2, 4);
      evas_object_size_hint_align_set(button, EVAS_HINT_FILL, 0.0);
      elm_box_pack_end(content, button);
      evas_object_show(button);

      evas_object_show(window->popup);
   }
}

void
_eng_project_creator_popup_add_cb(void *data, const Efl_Event *event)
{
   _eng_project_creator_popup_add(data);
}

static Evas_Object *
_eng_project_creator_popup_add(Eng_Window_State *window)
{
   if (window->project == NULL)
   {
      Evas_Object *popup, *content, *label, *button;
      popup = elm_popup_add(window->content);
      elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, ELM_NOTIFY_ALIGN_FILL);
      window->popup = popup;

      content = elm_box_add(popup);
      elm_box_horizontal_set(content, EINA_TRUE);
      elm_object_content_set(popup, content);

      Eng_Project_Creator_State *input = malloc(sizeof(Eng_Project_Creator_State));
      input->window = window;

      Evas_Object *projectdir = elm_box_add(content);
      evas_object_size_hint_weight_set(projectdir, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(projectdir, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_box_pack_end(content, projectdir);
      evas_object_show(projectdir);

      Evas_Object *projectdirlabel = elm_label_add(projectdir);
      elm_object_text_set(projectdirlabel, "Select Location:");
      elm_box_pack_end(projectdir, projectdirlabel);
      evas_object_show(projectdirlabel);

      Evas_Object *projectdirinput = elm_fileselector_add(projectdir);
      elm_fileselector_path_set(projectdirinput, eina_environment_home_get());
      elm_fileselector_is_save_set(projectdirinput, EINA_TRUE);
      elm_fileselector_expandable_set(projectdirinput, EINA_TRUE);
      elm_fileselector_folder_only_set(projectdirinput, EINA_TRUE);
      elm_fileselector_buttons_ok_cancel_set(projectdirinput, EINA_FALSE);
      evas_object_size_hint_padding_set(projectdirinput, 15, 10, 5, 5);
      evas_object_size_hint_weight_set(projectdirinput, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(projectdirinput, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_box_pack_end(projectdir, projectdirinput);
      evas_object_show(projectdirinput);
      input->path = projectdirinput;

      Evas_Object *projectdata = elm_box_add(content);
      evas_object_size_hint_weight_set(projectdata, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(projectdata, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_box_pack_end(content, projectdata);
      evas_object_show(projectdata);

      Evas_Object *projectdatalabel = elm_label_add(projectdata);
      elm_object_text_set(projectdatalabel, "Configure Metadata:");
      elm_box_pack_end(projectdata, projectdatalabel);
      evas_object_show(projectdatalabel);

      Evas_Object *projectinputs = elm_table_add(projectdata);
      elm_table_padding_set(projectinputs, 10, 10);
      evas_object_size_hint_padding_set(projectinputs, 10, 15, 10, 10);
      evas_object_size_hint_weight_set(projectinputs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(projectinputs, EVAS_HINT_FILL, 0.0);
      elm_box_pack_end(projectdata, projectinputs);
      evas_object_show(projectinputs);

      Evas_Object *projectnamelabel = elm_label_add(projectinputs);
      elm_object_text_set(projectnamelabel, "Project Name:");
      evas_object_size_hint_align_set(projectnamelabel, 1.0, 0.5);
      elm_table_pack(projectinputs, projectnamelabel, 0, 0, 1, 1);
      evas_object_show(projectnamelabel);

      Evas_Object *projectnameinput = elm_entry_add(projectinputs);
      elm_entry_scrollable_set(projectnameinput, EINA_TRUE);
      elm_entry_single_line_set(projectnameinput, EINA_TRUE);
      elm_object_part_text_set(projectnameinput, "elm.guide", "Enter Project Name Here.");
      evas_object_size_hint_weight_set(projectnameinput, EVAS_HINT_EXPAND, 0.0);
      evas_object_size_hint_align_set(projectnameinput, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_table_pack(projectinputs, projectnameinput, 1, 0, 4, 1);
      evas_object_show(projectnameinput);
      input->name = projectnameinput;

      Evas_Object *projecturllabel = elm_label_add(projectinputs);
      elm_object_text_set(projecturllabel, "Project URL:");
      evas_object_size_hint_align_set(projecturllabel, 1.0, 0.5);
      elm_table_pack(projectinputs, projecturllabel, 0, 1, 1, 1);
      evas_object_show(projecturllabel);

      Evas_Object *projecturlinput = elm_entry_add(projectinputs);
      elm_entry_scrollable_set(projecturlinput, EINA_TRUE);
      elm_entry_single_line_set(projecturlinput, EINA_TRUE);
      elm_object_part_text_set(projecturlinput, "elm.guide", "Enter Project URL Here.");
      evas_object_size_hint_weight_set(projecturlinput, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(projecturlinput, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_table_pack(projectinputs, projecturlinput, 1, 1, 4, 1);
      evas_object_show(projecturlinput);
      input->url = projecturlinput;

      Evas_Object *projectauthorlabel = elm_label_add(projectinputs);
      elm_object_text_set(projectauthorlabel, "Creator Name:");
      evas_object_size_hint_align_set(projectauthorlabel, 1.0, 0.5);
      elm_table_pack(projectinputs, projectauthorlabel, 0, 2, 1, 1);
      evas_object_show(projectauthorlabel);

      Evas_Object *projectauthorinput = elm_entry_add(projectinputs);
      elm_entry_scrollable_set(projectauthorinput, EINA_TRUE);
      elm_entry_single_line_set(projectauthorinput, EINA_TRUE);
      elm_object_part_text_set(projectauthorinput, "elm.guide", "Enter Project Creator's Name Here.");
      evas_object_size_hint_weight_set(projectauthorinput, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(projectauthorinput, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_table_pack(projectinputs, projectauthorinput, 1, 2, 4, 1);
      evas_object_show(projectauthorinput);
      input->creator = projectauthorinput;

      Evas_Object *projectauthoremaillabel = elm_label_add(projectinputs);
      elm_object_text_set(projectauthoremaillabel, "Creator Email:");
      evas_object_size_hint_align_set(projectauthoremaillabel, 1.0, 0.5);
      elm_table_pack(projectinputs, projectauthoremaillabel, 0, 3, 1, 1);
      evas_object_show(projectauthoremaillabel);

      Evas_Object *projectauthoremailinput = elm_entry_add(projectinputs);
      elm_entry_scrollable_set(projectauthoremailinput, EINA_TRUE);
      elm_entry_single_line_set(projectauthoremailinput, EINA_TRUE);
      elm_object_part_text_set(projectauthoremailinput, "elm.guide", "Enter Project Creator's Email Here.");
      evas_object_size_hint_weight_set(projectauthoremailinput, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(projectauthoremailinput, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_table_pack(projectinputs, projectauthoremailinput, 1, 3, 4, 1);
      evas_object_show(projectauthoremailinput);
      input->email = projectauthoremailinput;

      Evas_Object *projectbuttonbar = elm_box_add(projectdata);
      elm_box_horizontal_set(projectbuttonbar, EINA_TRUE);
      evas_object_size_hint_weight_set(projectbuttonbar, 0.0, 0.0);
      evas_object_size_hint_align_set(projectbuttonbar, 1.0, 1.0);
      elm_box_pack_end(projectdata, projectbuttonbar);
      evas_object_show(projectbuttonbar);

      Evas_Object *projectcreatebutton = elm_button_add(projectbuttonbar);
      elm_object_text_set(projectcreatebutton, "Create Project");
      evas_object_smart_callback_add(projectcreatebutton, "unpressed", _eng_project_create_cb, input);
      evas_object_size_hint_padding_set(projectcreatebutton, 15, 7, 15, 15);
      evas_object_size_hint_weight_set(projectcreatebutton, 0.0, 0.0);
      evas_object_size_hint_align_set(projectcreatebutton, 1.0, 1.0);
      elm_box_pack_end(projectbuttonbar, projectcreatebutton);
      evas_object_show(projectcreatebutton);

      Evas_Object *projectcancelbutton = elm_button_add(projectbuttonbar);
      elm_object_text_set(projectcancelbutton, "Cancel");
      evas_object_smart_callback_add(projectcancelbutton, "unpressed", _eng_window_popup_cancel_cb, window);
      evas_object_size_hint_padding_set(projectcancelbutton, 8, 15, 15, 15);
      evas_object_size_hint_weight_set(projectcancelbutton, 0.0, 0.0);
      evas_object_size_hint_align_set(projectcancelbutton, 1.0, 1.0);
      elm_box_pack_end(projectbuttonbar, projectcancelbutton);
      evas_object_show(projectcancelbutton);

      evas_object_show(popup);
      return popup;
   }
   else
   {
      _eng_project_resolve_popup_add(window);
      return NULL;
   }
}

void
_eng_project_loader_popup_add_cb(void *data, const Efl_Event *event)
{
   _eng_project_loader_popup_add(data);
}

static Evas_Object *
_eng_project_loader_popup_add(Eng_Window_State *window)
{
   Eng_Project_Loader_State *loader = malloc(sizeof(Eng_Project_Loader_State));
   if (window->popup == NULL && window->project == NULL)
   {
      Evas_Object *popup, *content, *label, *button;

      loader->window = window;
      loader->target = window;

      popup = elm_popup_add(window->content);
      elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, ELM_NOTIFY_ALIGN_FILL);
      window->popup = popup;

      content = elm_box_add(popup);
      elm_object_content_set(popup, content);

      Evas_Object *projectdir = elm_box_add(content);
      evas_object_size_hint_weight_set(projectdir, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(projectdir, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_box_pack_end(content, projectdir);
      evas_object_show(projectdir);

      Evas_Object *projectdirlabel = elm_label_add(projectdir);
      elm_object_text_set(projectdirlabel, "Select Project");
      elm_box_pack_end(projectdir, projectdirlabel);
      evas_object_show(projectdirlabel);

      Evas_Object *projectdirinput = elm_fileselector_add(projectdir);
      elm_fileselector_path_set(projectdirinput, eina_environment_home_get());
      elm_fileselector_is_save_set(projectdirinput, EINA_TRUE);
      elm_fileselector_expandable_set(projectdirinput, EINA_TRUE);
      elm_fileselector_folder_only_set(projectdirinput, EINA_TRUE);
      elm_fileselector_buttons_ok_cancel_set(projectdirinput, EINA_FALSE);
      evas_object_size_hint_padding_set(projectdirinput, 15, 10, 5, 5);
      evas_object_size_hint_weight_set(projectdirinput, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(projectdirinput, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_box_pack_end(projectdir, projectdirinput);
      evas_object_show(projectdirinput);
      loader->path = projectdirinput;

      Evas_Object *projectbuttonbar = elm_box_add(content);
      elm_box_horizontal_set(projectbuttonbar, EINA_TRUE);
      evas_object_size_hint_weight_set(projectbuttonbar, 0.0, 0.0);
      evas_object_size_hint_align_set(projectbuttonbar, 1.0, 1.0);
      elm_box_pack_end(content, projectbuttonbar);
      evas_object_show(projectbuttonbar);

      Evas_Object *projectloadbutton = elm_button_add(projectbuttonbar);
      elm_object_text_set(projectloadbutton, "Load Project");
      evas_object_smart_callback_add(projectloadbutton, "unpressed", _eng_project_load_cb, loader);
      evas_object_size_hint_padding_set(projectloadbutton, 15, 7, 15, 15);
      evas_object_size_hint_weight_set(projectloadbutton, 0.0, 0.0);
      evas_object_size_hint_align_set(projectloadbutton, 1.0, 1.0);
      elm_box_pack_end(projectbuttonbar, projectloadbutton);
      evas_object_show(projectloadbutton);

      Evas_Object *projectcancelbutton = elm_button_add(projectbuttonbar);
      elm_object_text_set(projectcancelbutton, "Cancel");
      evas_object_smart_callback_add(projectcancelbutton, "unpressed", _eng_window_popup_cancel_cb, window);
      evas_object_size_hint_padding_set(projectcancelbutton, 8, 15, 15, 15);
      evas_object_size_hint_weight_set(projectcancelbutton, 0.0, 0.0);
      evas_object_size_hint_align_set(projectcancelbutton, 1.0, 1.0);
      elm_box_pack_end(projectbuttonbar, projectcancelbutton);
      evas_object_show(projectcancelbutton);

      evas_object_show(popup);
   }
   else _eng_project_resolve_popup_add(window);

   return NULL;
}

void
_eng_project_saver_popup_add_cb(void *data, const Efl_Event *event)
{
}

static Evas_Object *
_eng_project_saver_popup_add(Eng_Window_State *window)
{
   return NULL;
}

void
_eng_window_popup_cancel_cb(void *data, const Efl_Event *event)
{
   _eng_window_popup_cancel(data);
}

static void
_eng_window_popup_cancel(Eng_Window_State *window)
{
   evas_object_del(window->popup);
   window->popup = NULL;
}

void
_eng_window_project_set(Eng_Window_State *target, const char *path)
{
   printf("_eng_window_project_set() Checkpoint, project path = %s \n", path);
   Eng_Window_State *window;
   Eng_Project_State *project;
   Eina_List *list, *next;
   Eina_Bool result = EINA_FALSE;
   // Check to see if the target window is in our window list.
   EINA_LIST_FOREACH_SAFE(_eng_user_state->windows, list, next, window)
   {
      if (target == window) result = EINA_TRUE;
   }
   if (result)
   {
      // Check to see if the project path is in our list.
      result = EINA_FALSE;
      EINA_LIST_FOREACH_SAFE(_eng_user_state->projects, list, next, project)
      {
         if (path == project->path)
         {
            printf("Iterator Checkpoint. path == %s, project->path == %s \n", path, project->path);
            result = EINA_TRUE;
            break;
         }
      }

      if (result)
      {
         printf("Checkpoint 2 \n");
         target->project = path;
         elm_object_item_disabled_set(target->scenetool,    EINA_FALSE);
         elm_object_item_disabled_set(target->materialtool, EINA_FALSE);
         elm_object_item_disabled_set(target->modeltool,    EINA_FALSE);
      }
      else
      {
         printf("Checkpoint 1 \n");
         target->project = NULL;
         elm_object_item_disabled_set(target->scenetool,    EINA_TRUE);
         elm_object_item_disabled_set(target->materialtool, EINA_TRUE);
         elm_object_item_disabled_set(target->modeltool,    EINA_TRUE);
      }
   }
}

void
_donothing_cb(void *data, const Efl_Event *event) {}


