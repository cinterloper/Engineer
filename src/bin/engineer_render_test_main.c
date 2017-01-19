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

   printf("Name: %s, Version: %s\n", argv[0], PACKAGE_VERSION);
   printf("UINT_NULL %d, ULONG_NULL %ld\n", UINT_NULL, ULONG_NULL);

   engineer_render_test_init();

   Evas_Object *window = elm_win_util_standard_add("main", "Engineer Render Test");
   if (!window) return -1;
   elm_win_focus_highlight_enabled_set(window, EINA_TRUE);
   //evas_object_smart_callback_add(window, "delete,request", _eng_window_del, window);
   evas_object_resize(window, 800, 800);
   evas_object_show(window);

   Eo *node = efl_add(ENGINEER_NODE_CLASS, NULL,
                 engineer_node_path_set(efl_added, "/home/brokenshakles/Projects/SoftwareEngines/Engineer/build"),
                 engineer_node_title_set(efl_added, "Engineer_Render_Test"));

   // Load our component modules here.

   Eo *scene = engineer_node_scene_create(node, "engrendertest");

   uint root, camera, sphere;
   root = engineer_scene_entity_create(scene, (uint)0, "Root");

   //camera = engineer_scene_entity_create(scene, root, "Camera");

   //sphere = engineer_scene_entity_create(scene, root, "Sphere");

   //engineer_node_file_save(node);

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
