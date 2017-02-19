#include "main.h"

static const Ecore_Getopt optdesc = {
  "engineer", "%prog [options]",
  PACKAGE_VERSION,
  COPYRIGHT,
  "3 clause BSD license",
  "An EFL Engineer program",
  0,
  {
    ECORE_GETOPT_LICENSE('L', "license"),
    ECORE_GETOPT_COPYRIGHT('C', "copyright"),
    ECORE_GETOPT_VERSION('V', "version"),
    ECORE_GETOPT_HELP('h', "help"),
    ECORE_GETOPT_SENTINEL
  }
};

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   int args;
   Eina_Bool quit_option = EINA_FALSE;

   Ecore_Getopt_Value values[] = {
     ECORE_GETOPT_VALUE_BOOL(quit_option),
     ECORE_GETOPT_VALUE_BOOL(quit_option),
     ECORE_GETOPT_VALUE_BOOL(quit_option),
     ECORE_GETOPT_VALUE_BOOL(quit_option),
     ECORE_GETOPT_VALUE_NONE
   };

   #if ENABLE_NLS
   setlocale(LC_ALL, "");
   bindtextdomain(PACKAGE, LOCALEDIR);
   bind_textdomain_codeset(PACKAGE, "UTF-8");
   textdomain(PACKAGE);
   #endif

   //edi_init();
   //engineer_init();
   //engineer_editor_init();

   args = ecore_getopt_parse(&optdesc, values, argc, argv);
   if (args < 0)
   {
      EINA_LOG_CRIT("Could not parse arguments.");
      goto engineer_error;
   }
   else if (quit_option)
   {
      goto engineer_error;
   }

   elm_app_info_set(elm_main, "engineer", "images/engineer.png");

   edi_init();
   engineer_init();
   engineer_editor_init();

   elm_run();
   //engineer_run();

   config_error:
      engineer_editor_shutdown();

   engineer_error:
      engineer_shutdown();

   edi_error:
      edi_shutdown();

   elm_shutdown();

   return 0;
}
ELM_MAIN()

EAPI Eina_Bool
engineer_editor_init()
{
   elm_need_efreet();
   if (!efreet_init()) return EINA_FALSE;
   ENG_EVENT_STATE_CHANGED = ecore_event_type_new();

   _eng_window_state_init();
   _eng_project_state_init();
   _eng_user_state_init();

   _eng_user_state_load();

   Eng_Window_State *window;
   Eina_List *list, *next;

   // Check to see if there is at least one visible window.
   EINA_LIST_FOREACH_SAFE(_eng_user_state->windows, list, next, window)
   {
       if (window->widget != NULL && evas_object_visible_get(window->widget)) break;
       window = NULL;
   }
   // If not, create a new empty window and make it visible.
   if (window == NULL) _eng_window_add(NULL);

   return EINA_TRUE;
}

EAPI Eina_Bool
engineer_editor_shutdown()
{
   _eng_user_state_free();

   _eng_user_state_shutdown();
   _eng_project_state_shutdown();
   _eng_window_state_shutdown();

   efreet_shutdown();

   return EINA_TRUE;
}
