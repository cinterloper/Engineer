#ifndef ENGINEER_TABBER_H_
#define ENGINEER_TABBER_H_

#define EFL_BETA_API_SUPPORT
#include <Elementary.h>

typedef struct
{
   void            *tabber;  // The tabber this tab currently belongs to.
   void            *left;    // The tab that is to the left of this one in the parent tabber.
   void            *right;   // The tab that is to the right of this one in the parent tabber.
   Elm_Object_Item *widget;  // The tab widget to be inserted into the tabber->tabs.
   Elm_Object_Item *payload; // The naviframe item that contains the gui payload for this item.
}
Engineer_Tab;

typedef struct
{
   Evas_Object  *widget;  // The box widget that is used for our tabber and payload.
   Evas_Object  *tabs;    // The box widget that holds the tabs.
   Engineer_Tab *first;
   Engineer_Tab *current;
   Engineer_Tab *previous;
}
Engineer_Tabber;

Engineer_Tabber *
engineer_tabber_add(Efl_Object *parent);

void
engineer_tabber_current_set(Engineer_Tab *target);

void
engineer_tab_select_cb(void *data, Evas_Object *obj EINA_UNUSED,
         const char *emission EINA_UNUSED, const char *source EINA_UNUSED);

void
engineer_tab_close_cb(void *data, Evas_Object *obj EINA_UNUSED,
         const char *emission EINA_UNUSED, const char *source EINA_UNUSED);

Engineer_Tab *
engineer_tab_add(Engineer_Tabber *tabber, const char *label);

void
engineer_tab_payload_set(Engineer_Tab *tab, Evas_Object *payload);

Evas_Object *
engineer_tab_payload_get(Engineer_Tab *tab);

Evas_Object *
engineer_tab_remove(Engineer_Tab *target);

#endif
