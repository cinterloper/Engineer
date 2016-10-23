#include "engineer_scene_tab.h"

Elm_Genlist_Item_Class *_itc = NULL;

#define N_ITEMS 300

static char *
_item_label_get(void *data, Evas_Object *obj, const char *part)
{
   char buf[256];
   snprintf(buf, sizeof(buf), "Item # %i", (int)(long)data);
   return strdup(buf);
}

static void
_item_sel_cb(void *data, Evas_Object *obj, void *event_info)
{
   printf("sel item data [%p] on genlist obj [%p], item pointer [%p]\n",
          data, obj, event_info);
}

static void
_genlist_fill(Evas_Object *list)
{
   int i;

   for (i = 0; i < N_ITEMS; i++)
   {
      elm_genlist_item_append(list, _itc, (void *)(long)i, NULL,
                              ELM_GENLIST_ITEM_NONE, _item_sel_cb, NULL);
   }
}

static Evas_Object *
_item_content_get(void *data, Evas_Object *obj, const char *part)
{
   Evas_Object *ic = elm_icon_add(obj);

   if (!strcmp(part, "elm.swallow.icon"))
     elm_icon_standard_set(ic, "clock");

   evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
   return ic;
}

_eng_scene_creator_popup_add_cb(void *data, const Efl_Event *event)
{
}

_eng_scene_creator_popup_add(Eng_Window_State *window)
{
   // Use the Engineer library to create a scene berkeley db file.
}

_eng_scene_loader_popup_add_cb(void *data, const Efl_Event *event)
{
}

_eng_scene_loader_popup_add(Eng_Window_State *window)
{
}

_eng_scene_saver_popup_add_cb(void *data, const Efl_Event *event)
{
}

_eng_scene_saver_popup_add(Eng_Window_State *window)
{
}

_eng_scene_closer_popup_add_cb(void *data, const Efl_Event *event)
{
}

_eng_scene_closer_popup_add(Eng_Window_State *window)
{
}

static Evas_Object *
_eng_scene_tab_add(Eng_Window_State *parent)
{

/* // We need to refactor this for the tabber update.
   Evas_Object *scenetab = elm_box_add(parent);
   evas_object_size_hint_weight_set(scenetab, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(scenetab, EVAS_HINT_FILL, EVAS_HINT_FILL);

   Evas_Object *paneleft = elm_panes_add(scenetab);
   evas_object_size_hint_weight_set(paneleft, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(paneleft, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_panes_content_left_size_set(paneleft, 0.15);
   elm_box_pack_end(scenetab, paneleft);
   evas_object_show(paneleft);

   Evas_Object *paneright = elm_panes_add(paneleft);
   evas_object_size_hint_weight_set(paneright, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_part_content_set(paneleft, "right", paneright);
   elm_panes_content_left_size_set(paneright, 0.7/0.85);
   evas_object_show(paneright);

   Evas_Object *panecenter = elm_panes_add(paneright);
   elm_panes_horizontal_set(panecenter, EINA_TRUE);
   evas_object_size_hint_weight_set(panecenter, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_part_content_set(paneright, "left", panecenter);
   elm_panes_content_left_size_set(panecenter, 0.99);
   evas_object_show(panecenter);

   Evas_Object *entitylist = elm_genlist_add(paneleft);
   evas_object_size_hint_weight_set(entitylist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(entitylist, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_part_content_set(paneleft, "left", entitylist);
   evas_object_show(entitylist);

   _genlist_fill(entitylist);

   Evas_Object *viewport = elm_box_add(panecenter);
   evas_object_size_hint_weight_set(viewport, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(viewport, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_part_content_set(panecenter, "left", viewport);
   evas_object_show(entitylist);

   Elm_Code *code = elm_code_create();
   Elm_Code_Widget *console = elm_code_widget_add(panecenter, code);
   //elm_obj_code_widget_font_set(widget, _edi_project_config->font.name, _edi_project_config->font.size);
   elm_obj_code_widget_gravity_set(console, 0.0, 1.0);
   //efl_event_callback_add(widget, &ELM_CODE_EVENT_LINE_LOAD_DONE, _edi_consolepanel_line_cb, NULL);
   //efl_event_callback_add(widget, ELM_OBJ_CODE_WIDGET_EVENT_LINE_CLICKED, _edi_consolepanel_clicked_cb, code);
   evas_object_size_hint_weight_set(console, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(console, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_part_content_set(panecenter, "right", console);
   evas_object_show(console);

   Evas_Object *componentlist = elm_genlist_add(paneright);
   evas_object_size_hint_weight_set(componentlist, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(componentlist, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_part_content_set(paneright, "right", componentlist);
   evas_object_show(componentlist);

   _genlist_fill(componentlist);

   return scenetab;*/
}

static void
_eng_scene_tab_del(Eng_Scene_Tab_State *target)
{
}

static void
_eng_scene_new_cb(void *data, const Efl_Event *event)
{
   Eng_Window_State *window = data;
   Engineer_Tabber *tabber = window->tabber;
   Engineer_Tab *newtab = engineer_tab_add(tabber, "Test Tab");
   Evas_Object *oldpayload = _eng_scene_tab_add(newtab);
   tabber->current = newtab;
   engineer_tabber_current_set(newtab);
   evas_object_del(oldpayload);

   if (!_itc)
   {
      _itc = elm_genlist_item_class_new();
      _itc->item_style = "default";
      _itc->func.text_get = _item_label_get;
      _itc->func.content_get = _item_content_get;
      _itc->func.state_get = NULL;
      _itc->func.del = NULL;
   }
}

static void
_eng_scene_new(Eng_Window_State *window)
{
}

