#include "engineer_tabber.h"

/*** Tabber Functions ***/

Engineer_Tabber *
engineer_tabber_add(Efl_Object *parent)
{
   Engineer_Tabber *tabber = malloc(sizeof(Engineer_Tabber));
   tabber->widget = elm_box_add(parent);
   tabber->first = NULL;
   tabber->current = NULL;

   tabber->tabs = elm_box_add(tabber->widget);
   elm_box_horizontal_set(tabber->tabs, EINA_TRUE);
 //elm_scroller_policy_set(tabber->tabs, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   evas_object_size_hint_weight_set(tabber->tabs, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(tabber->tabs, 0.0, EVAS_HINT_FILL);
   elm_box_pack_end(tabber->widget, tabber->tabs);
   evas_object_show(tabber->tabs);

   return tabber;
}

void
engineer_tabber_current_set(Engineer_Tab *target)
{
   Engineer_Tabber *tabber = target->tabber;

   if (target != tabber->current || tabber->current == NULL)
   {
      evas_object_hide(tabber->current->payload);
      elm_box_unpack(tabber->widget, tabber->current->payload);
      tabber->current = target;
      elm_box_pack_end(tabber->widget,  tabber->current->payload);
      evas_object_show(tabber->current->payload);
   }
}

/*** Tab Callbacks ***/

void
engineer_tab_select_cb(void *data, Evas_Object *obj EINA_UNUSED,
         const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{ engineer_tabber_current_set(data); }

void
engineer_tab_close_cb(void *data, Evas_Object *obj EINA_UNUSED,
          const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{ Evas_Object *payload = engineer_tab_remove(data); evas_object_del(payload); }

/*** Tab Functions ***/

Engineer_Tab *
engineer_tab_add(Engineer_Tabber *tabber, const char *label)
{
   Engineer_Tab *tab = malloc(sizeof(Engineer_Tab));

   tab->tabber = tabber;
   tab->widget = elm_button_add(tabber->tabs);

   elm_layout_theme_set(tab->widget, "multibuttonentry", "btn", "default");
   elm_object_part_text_set(tab->widget, "elm.btn.text", label);
   evas_object_size_hint_weight_set(tab->widget, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(tab->widget, 0.0, EVAS_HINT_FILL);
   elm_layout_signal_callback_add(tab->widget, "mouse,clicked,1", "*", engineer_tab_select_cb, tab);
   elm_layout_signal_callback_add(tab->widget, "elm,deleted", "elm", engineer_tab_close_cb, tab);
   elm_box_pack_end(tabber->tabs, tab->widget);
   evas_object_show(tab->widget);
/*
   icon = elm_icon_add(tab);
   elm_icon_standard_set(icon, provider->icon);
   elm_object_part_content_set(tab, "icon", icon);
*/
   tab->payload = elm_box_add(tab->widget);
   evas_object_size_hint_weight_set(tab->payload, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(tab->payload, EVAS_HINT_FILL, EVAS_HINT_FILL);

   if (tabber->first == NULL || tabber->current == NULL)
   {
      tabber->first = tab;
      tabber->current = tab;
      tab->left = tab;
      tab->right = tab;
   }
   else
   {
      Engineer_Tab *buffer = tabber->first->left;
      tabber->first->left = tab;
      buffer->right = tab;
      tab->left = buffer;
      tab->right = tabber->first;
   }

   return tab;
}

void
engineer_tab_payload_set(Engineer_Tab *tab, Evas_Object *payload)
{
   Engineer_Tabber *tabber = tab->tabber;

   if (tab == tabber->current)
   {
      evas_object_hide(tab->payload);
      elm_box_unpack(tabber->widget, tab->payload);
      tab->payload = payload;
      elm_box_pack_end(tabber->widget, tab->payload);
      evas_object_show(tab->payload);
   }
   else tab->payload = payload;
}

Evas_Object *
engineer_tab_payload_get(Engineer_Tab *tab)
{
   return tab->payload;
}

Evas_Object *
engineer_tab_remove(Engineer_Tab *target)
{
   Engineer_Tabber *tabber = target->tabber;

  if (target != target->right)
  {
     if (target == tabber->first)   tabber->first = tabber->first->right;
     if (target == tabber->current) engineer_tabber_current_set(tabber->current->right);

     Engineer_Tab *bufferleft  = target->left;
     Engineer_Tab *bufferright = target->right;
     bufferleft->right = bufferright;
     bufferright->left = bufferleft;
  }
  else
  {
     tabber->first   = NULL;
     tabber->current = NULL;
  }

   Evas_Object *payload = target->payload;
   evas_object_del(target->widget);
   free(target);

   return payload;
}

