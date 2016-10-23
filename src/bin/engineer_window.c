#include "engineer_window.h"

Eng_Window_State_DD *_eng_window_state_edd       = NULL;
Eng_Window_State_DD *_eng_project_tab_state_edd  = NULL;
Eng_Window_State_DD *_eng_scene_tab_state_edd    = NULL;
Eng_Window_State_DD *_eng_material_tab_state_edd = NULL;
Eng_Window_State_DD *_eng_model_tab_state_edd    = NULL;

Eina_Bool
_eng_window_state_init(void)
{
   _eng_window_state_edd = ENG_STATE_DD_NEW("Window_State", Eng_Window_State);
   #undef T
   #undef D
   #define T Eng_Window_State
   #define D _eng_window_state_edd
   ENG_STATE_VAL( D, T, project, EET_T_STRING); // This contains the project path.
   //ENG_STATE_LIST(D, T, tabs,    EET_T_INT);    // Contains a list of paths for all open tabs.
/*
   _eng_project_tab_state_edd = ENG_STATE_DD_NEW("Project_Tab_State", Eng_Project_Tab_State);
   #undef T
   #undef D
   #define T Eng_Project_Tab_State
   #define D _eng_project_tab_state_edd
   ENG_STATE_VAL(D, T, gitserver, EET_T_STRING);

   _eng_scene_tab_state_edd = ENG_STATE_DD_NEW("Scene_Tab_State", Eng_Scene_Tab_State);
   #undef T
   #undef D
   #define T Eng_Scene_Tab_State
   #define D _eng_scene_tab_state_edd
   ENG_STATE_VAL(D, T, version, EET_T_INT);
   ENG_STATE_VAL(D, T, path, EET_T_STRING);
   ENG_STATE_VAL(D, T, name, EET_T_STRING);
*/
   return EINA_TRUE;
}

Eina_Bool
_eng_window_state_shutdown(void)
{
   ENG_STATE_DD_FREE(_eng_window_state_edd);
   //ENG_STATE_DD_FREE(_eng_scene_tab_state_edd);
   //ENG_STATE_DD_FREE(_eng_project_tab_state_edd);

   return EINA_TRUE;
}

Eina_Bool
_eng_window_add(const char *path)
{
   Eng_Project_State *project;
   if (ecore_file_is_dir(path))
   {
      Eina_List *list, *next;
      EINA_LIST_FOREACH_SAFE(_eng_user_state->projects, list, next, project)
      {
         if (project->path == path) break;
         project = NULL;
      }
      if (project == NULL) project = _eng_project_state_add(path);
   }
   else path = NULL;

   Eng_Window_State *window;
   window = malloc(sizeof(*window));
   window->popup = NULL;

   window->widget = elm_win_util_standard_add("main", "Engineer Editor");
   if (!window->widget) return NULL;
   elm_win_focus_highlight_enabled_set(window->widget, EINA_TRUE);
   evas_object_smart_callback_add(window->widget, "delete,request", _eng_window_del, window);
   evas_object_resize(window->widget, 800, 800);
   evas_object_show(window->widget);

   window->content = elm_box_add(window->widget);
   if (!window->content) return NULL;
   elm_box_horizontal_set(window->content, EINA_TRUE);
   evas_object_size_hint_weight_set(window->content, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(window->content, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_win_resize_object_add(window->widget, window->content);
   evas_object_show(window->content);

   window->toolbar = elm_toolbar_add(window->widget);
   if (!window->toolbar) return NULL;
   elm_toolbar_menu_parent_set(window->toolbar, window->widget);
   elm_toolbar_horizontal_set(window->toolbar, EINA_FALSE);
   elm_toolbar_homogeneous_set(window->toolbar, EINA_FALSE);
   elm_toolbar_shrink_mode_set(window->toolbar, ELM_TOOLBAR_SHRINK_MENU);
   elm_toolbar_align_set(window->toolbar, 0.0);
   elm_object_focus_allow_set(window->toolbar, EINA_FALSE);
   evas_object_size_hint_weight_set(window->toolbar, 0.0, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(window->toolbar, EVAS_HINT_FILL, EVAS_HINT_FILL);

   _eng_editor_filetool_setup(window);
   _eng_editor_scenetool_setup(window);
   _eng_editor_materialtool_setup(window);
   _eng_editor_modeltool_setup(window);

   elm_box_pack_end(window->content, window->toolbar);
   evas_object_show(window->toolbar);

   window->tabber = engineer_tabber_add(window->content);
   if (!window->tabber) return NULL;
   evas_object_size_hint_weight_set(window->tabber->widget, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(window->tabber->widget, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(window->content, window->tabber->widget);
   evas_object_show(window->tabber->widget);

   _eng_user_state->windows = eina_list_append(_eng_user_state->windows, window);
   _eng_window_project_set(window, path);
   _eng_user_state_save();

   return EINA_TRUE;
}

void
_eng_window_del_cb(void *data, const Efl_Event *event)
{
   _eng_window_del(data);
}

void
_eng_window_del(Eng_Window_State *target)
{
   evas_object_del(target->widget);
   _eng_user_state->windows = eina_list_remove(_eng_user_state->windows, target);

   // Check to see if the window has a project, if so, check to see if that project has any other window(s) open.
   Eng_Window_State *window;
   Eina_List *list, *next;
   Eina_Bool result = EINA_FALSE;
   if (target->project != NULL)
   {
      EINA_LIST_FOREACH_SAFE(_eng_user_state->windows, list, next, window)
      {
         if (!strncmp(target->project, window->project, strlen(target->project))) result = EINA_TRUE;
      }
      // If it does not, then del that project.
      if (!result) _eng_project_state_del(window->project);
   }

   free(target);
   // If there are no more visible windows, quit.
   result = EINA_FALSE;
   EINA_LIST_FOREACH_SAFE(_eng_user_state->windows, list, next, window)
   {
      if (evas_object_visible_get(window->widget)) result = EINA_TRUE;
   }
   _eng_user_state_save();
   if (result) elm_shutdown();
}

static void
_eng_console_line_cb(void *data EINA_UNUSED, const Efl_Event *event)
{
   Elm_Code_Line *line = (Efl_Object *)event->info;

   if (line->data)
     line->status = ELM_CODE_STATUS_TYPE_ERROR;
}

static void
_eng_editor_filetool_setup(Eng_Window_State *window)
{
   Elm_Object_Item *filetool = elm_toolbar_item_append(window->toolbar, "folder", "File", NULL, NULL);
   elm_toolbar_item_menu_set(filetool, EINA_TRUE);
   elm_toolbar_item_priority_set(filetool, -9999);

   Evas_Object *filemenu = elm_toolbar_item_menu_get(filetool);

   elm_menu_item_add(filemenu, NULL, "folder-new",    "New Project",   _eng_project_creator_popup_add_cb, window);
   elm_menu_item_add(filemenu, NULL, "document-load", "Load Project",  _eng_project_loader_popup_add_cb, window);
   elm_menu_item_add(filemenu, NULL, "document-save", "Save Project",  _donothing_cb, NULL);
   elm_menu_item_add(filemenu, NULL, "document-save", "Close Project", _donothing_cb, NULL);
   elm_menu_item_add(filemenu, NULL, "document-save", "Settings",      _donothing_cb, NULL);
   elm_menu_item_add(filemenu, NULL, "document-save", "Quit",          _eng_window_del_cb, window);
}

static void
_eng_editor_scenetool_setup(Eng_Window_State *window)
{
   window->scenetool = elm_toolbar_item_append(window->toolbar, "folder", "Scene", NULL, NULL);
   elm_object_item_disabled_set(window->scenetool, EINA_TRUE);
   elm_toolbar_item_menu_set(window->scenetool, EINA_TRUE);
   elm_toolbar_item_priority_set(window->scenetool, -9999);

   Evas_Object *scenemenu = elm_toolbar_item_menu_get(window->scenetool);

   elm_menu_item_add(scenemenu, NULL, "document-new",  "New Scene",    _donothing_cb, NULL);
   elm_menu_item_add(scenemenu, NULL, "window-new",    "Load Scene",   _donothing_cb, NULL);
   elm_menu_item_add(scenemenu, NULL, "document-save", "Save Scene",   _donothing_cb, NULL);
   elm_menu_item_add(scenemenu, NULL, "document-save", "Close Scene",  _donothing_cb, NULL);
}

static void
_eng_editor_materialtool_setup(Eng_Window_State *window)
{
   window->materialtool = elm_toolbar_item_append(window->toolbar, "folder", "Material", NULL, NULL);
   elm_object_item_disabled_set(window->materialtool, EINA_TRUE);
   elm_toolbar_item_menu_set(window->materialtool, EINA_TRUE);
   elm_toolbar_item_priority_set(window->materialtool, -9999);

   Evas_Object *materialmenu = elm_toolbar_item_menu_get(window->materialtool);

   elm_menu_item_add(materialmenu, NULL, "document-new",  "New Material",    _donothing_cb, NULL);
   elm_menu_item_add(materialmenu, NULL, "window-new",    "Load Material",   _donothing_cb, NULL);
   elm_menu_item_add(materialmenu, NULL, "document-save", "Save Material",   _donothing_cb, NULL);
   elm_menu_item_add(materialmenu, NULL, "document-save", "Close Material",  _donothing_cb, NULL);
}

static void
_eng_editor_modeltool_setup(Eng_Window_State *window)
{
   window->modeltool = elm_toolbar_item_append(window->toolbar, "folder", "Model", NULL, NULL);
   elm_object_item_disabled_set(window->modeltool, EINA_TRUE);
   elm_toolbar_item_menu_set(window->modeltool, EINA_TRUE);
   elm_toolbar_item_priority_set(window->modeltool, -9999);

   Evas_Object *modelmenu = elm_toolbar_item_menu_get(window->modeltool);

   elm_menu_item_add(modelmenu, NULL, "document-new",  "New Model",    _donothing_cb, NULL);
   elm_menu_item_add(modelmenu, NULL, "window-new",    "Load Model",   _donothing_cb, NULL);
   elm_menu_item_add(modelmenu, NULL, "document-save", "Save Model",   _donothing_cb, NULL);
   elm_menu_item_add(modelmenu, NULL, "document-save", "Close Model",  _donothing_cb, NULL);
}

