#include "engineer_render_test_main.h"

static const Ecore_Getopt optdesc = {
  "engineer_render_test", "%prog [options]",
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

   args = ecore_getopt_parse(&optdesc, values, argc, argv);

   if (args < 0)
   {
      EINA_LOG_CRIT("Could not parse arguments.");
      goto engineer_render_test_error;
   }
   else if (quit_option)
   {
      goto engineer_render_test_error;
   }
   elm_app_info_set(elm_main, "engineer_render_test", "images/engineer_render_test.png");

   printf("Name: %s", argv[0]);

   engineer_render_test_init();

   Evas_Object *window = elm_win_util_standard_add("main", "Engineer Render Test");
   if (!window) return NULL;
   elm_win_focus_highlight_enabled_set(window, EINA_TRUE);
   //evas_object_smart_callback_add(window, "delete,request", _eng_window_del, window);
   evas_object_resize(window, 800, 800);
   evas_object_show(window);

   Eo *game = efl_add(ENGINEER_GAME_CLASS, NULL);

   elm_run();
   //engineer_run();

   config_error:
      //engineer_render_test_shutdown();

   engineer_render_test_error:
      //engineer_render_test_shutdown();

   elm_shutdown();

   return 0;
}
ELM_MAIN()

void
engineer_render_test_init()
{
}
