#include "engineer_project_tab.h"

static Evas_Object *
_eng_project_editor_tab_add(Eng_Window_State *window)
{
   Engineer_Tab *tab = engineer_tab_add(window->tabber, "Project Editor");
   Evas_Object *oldpayload = _eng_project_editor_payload_add(tab);
   evas_object_del(oldpayload);
}

static Evas_Object *
_eng_project_editor_payload_add(Engineer_Tab *tab)
{
   Evas_Object *oldpayload = engineer_tab_payload_get(tab);

   Evas_Object *projecteditortab = elm_box_add(tab->widget);
   elm_box_horizontal_set(projecteditortab, EINA_TRUE);
   evas_object_size_hint_weight_set(projecteditortab, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(projecteditortab, EVAS_HINT_FILL, EVAS_HINT_FILL);

   Evas_Object *projectbrowserlabel = elm_label_add(projecteditortab);
   elm_object_text_set(projectbrowserlabel, "Project Editor");
   elm_box_pack_end(projecteditortab, projectbrowserlabel);
   evas_object_show(projectbrowserlabel);

   engineer_tab_payload_set(tab, projecteditortab);
   return oldpayload;
}
