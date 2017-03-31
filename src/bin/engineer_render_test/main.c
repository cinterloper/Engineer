#include "main.h"

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
   elm_config_accel_preference_set("opengl");

   printf("Name: %s, Version: %s\n", argv[0], PACKAGE_VERSION);
   printf("UINT_NULL %d, ULONG_NULL %ld\n", UINT_NULL, ULONG_NULL);

   Eo *window   = engineer_render_test_window_init();
   Eo *viewport = engineer_render_test_viewport_init(window);
   engineer_render_test_game_init(window, viewport);

   //engineer_run();

   elm_run();
   //elm_shutdown();

   //config_error:
      //engineer_render_test_shutdown();

   engineer_render_test_error:
      //engineer_render_test_shutdown();

   return 0;
}
ELM_MAIN()

Eo *
engineer_render_test_window_init()
{
   Evas_Object *window = elm_win_util_standard_add("main", "Engineer Render Test");
   elm_win_focus_highlight_enabled_set(window, EINA_TRUE);
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   //evas_object_smart_callback_add(window, "delete,request", _eng_window_del, window);
   evas_object_resize(window, 800, 800);
   evas_object_show(window);

   return window;
}

void
engineer_render_test_game_init(Eo *root, Eo *viewport)
{
   struct collidercolor_t
   {
      Sclr red:   8;
      Sclr green: 8;
      Sclr blue:  8;
      Sclr blank: 40;
   };
   struct collidercolor_t colordata, *collidercolor;

   collidercolor = &colordata;

   Eo *scene, *node = engineer_node_new(root,
                 "/home/brokenshakles/Projects/SoftwareEngines/Engineer/build",
                 "Engineer_Render_Test");

   uint64_t sceneroot, camera;
   int64_t  cameradata[6], transformdata[12], colliderdata[5];
   EntityID sphere1, sphere2, box1, plane1;

   // Load our component modules here.
   printf("\nModule Load Checkpoint.\n");
   engineer_node_module_load(node, "Transform");
   engineer_node_module_load(node, "Camera");
   engineer_node_module_load(node, "Collider");
   //engineer_node_module_load(node, "Actor");

   scene = engineer_scene_new(node, "Engineer Render Test");
   sceneroot = (EntityID)0;

   transformdata[0]  = (Sclr)(0 * BASIS);
   transformdata[1]  = (Sclr)(0 * BASIS);
   transformdata[2]  = (Sclr)(8 * BASIS);
   //transformdata[3]  = (Sclr)(0 * BASIS);
   //transformdata[4]  = (Sclr)(0 * BASIS);
   //transformdata[5]  = (Sclr)(0 * BASIS);
   //transformdata[6]  = (Sclr)(0 * BASIS);
   //transformdata[7]  = (Sclr)(0 * BASIS);
   //transformdata[8]  = (Sclr)(0 * BASIS);
   //transformdata[9]  = (Sclr)(0 * BASIS);
   //transformdata[10] = (Sclr)(0 * BASIS);
   //transformdata[11] = (Sclr)(0 * BASIS);
   cameradata[0] = (Sclr)viewport;
   //cameradata[1] = (Sclr)(0 * BASIS);
   //cameradata[2] = (Sclr)(0 * BASIS);
   //cameradata[3] = (Sclr)(0 * BASIS);
   //cameradata[4] = (Sclr)(0 * BASIS);
   //cameradata[5] = (Sclr)(0 * BASIS);

   camera = engineer_scene_entity_create(scene, sceneroot, sceneroot);
   engineer_scene_component_create(scene, sceneroot, "Transform", camera, (Data*)transformdata);
   engineer_scene_component_create(scene, sceneroot, "Camera",    camera, (Data*)cameradata);

   colliderdata[3]  = (uint64_t)1; // Shape/Type.
   transformdata[0] = (Sclr)(4 * BASIS);
   transformdata[1] = (Sclr)(0 * BASIS);
   transformdata[2] = (Sclr)(0 * BASIS);
   colliderdata[0]  = (uint64_t)1; // Size.
   colliderdata[1]  = (uint64_t)0;
   colliderdata[2]  = (uint64_t)0;
   collidercolor->red   = (unsigned char)0;
   collidercolor->green = (unsigned char)255;
   collidercolor->blue  = (unsigned char)255;
   colliderdata[4]  = *(uint64_t*)collidercolor;

   sphere1 = engineer_scene_entity_create(scene, sceneroot, sceneroot);
   engineer_scene_component_create(scene, sceneroot, "Transform", sphere1, (Data*)transformdata);
   engineer_scene_component_create(scene, sceneroot, "Collider",  sphere1, (Data*)colliderdata);

   colliderdata[3]  = (uint64_t)1; // Shape/Type.
   transformdata[0] = (Sclr)(0 * BASIS);
   transformdata[1] = (Sclr)(4 * BASIS);
   transformdata[2] = (Sclr)(0 * BASIS);
   colliderdata[0]  = (uint64_t)1; // Size.
   collidercolor->red   = (unsigned char)0;
   collidercolor->green = (unsigned char)0;
   collidercolor->blue  = (unsigned char)255;
   colliderdata[4]  = *(uint64_t*)collidercolor;

   sphere2 = engineer_scene_entity_create(scene, sceneroot, sceneroot);
   engineer_scene_component_create(scene, sceneroot, "Transform", sphere2, (Data*)transformdata);
   engineer_scene_component_create(scene, sceneroot, "Collider",  sphere2, (Data*)colliderdata);

   colliderdata[3]  = (uint64_t)2; // Shape/Type.
   transformdata[0] = (Sclr)(0 * BASIS);
   transformdata[1] = (Sclr)(0 * BASIS);
   transformdata[2] = (Sclr)(0 * BASIS);
   colliderdata[0]  = (uint64_t)1; // Size.
   collidercolor->red   = (unsigned char)0;
   collidercolor->green = (unsigned char)255;
   collidercolor->blue  = (unsigned char)0;
   colliderdata[4]  = *(uint64_t*)collidercolor;

   box1 = engineer_scene_entity_create(scene, sceneroot, sceneroot);
   engineer_scene_component_create(scene, sceneroot, "Transform", box1, (Data*)transformdata);
   engineer_scene_component_create(scene, sceneroot, "Collider",  box1, (Data*)colliderdata);

   colliderdata[3]  = (uint64_t)3; // Shape/Type.
   transformdata[0] = (Sclr)( 0 * BASIS);
   transformdata[1] = (Sclr)(-2 * BASIS);
   transformdata[2] = (Sclr)( 0 * BASIS);
   colliderdata[0]  = (uint64_t)1; // Size.
   collidercolor->red   = (unsigned char)255;
   collidercolor->green = (unsigned char)(255 * 0.8);
   collidercolor->blue  = (unsigned char)(255 * 0.6);
   colliderdata[4]  = *(uint64_t*)collidercolor;

   plane1 = engineer_scene_entity_create(scene, sceneroot, sceneroot);
   engineer_scene_component_create(scene, sceneroot, "Transform", plane1, (Data*)transformdata);
   engineer_scene_component_create(scene, sceneroot, "Collider",  plane1, (Data*)colliderdata);
}

Eo *
engineer_render_test_viewport_init(Eo *window)
{
   Evas_Object *viewport = engineer_viewport_add(window);
   //evas_object_size_hint_weight_set(viewport, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   //evas_object_size_hint_align_set(viewport, EVAS_HINT_FILL, EVAS_HINT_FILL);
   //evas_object_show(viewport);

   return viewport;
}

