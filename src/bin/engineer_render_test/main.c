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

static uint64_t
color(double red, double green, double blue, double alpha)
{
   struct color_t
   {
      Sclr red:   8;
      Sclr green: 8;
      Sclr blue:  8;
      Sclr alpha: 8;
      Sclr blank: 32;
   };
   struct color_t colordata, *color;
   color = &colordata;

   color->red   = (unsigned char)255 * red;
   color->green = (unsigned char)255 * green;
   color->blue  = (unsigned char)255 * blue;
   color->alpha = (unsigned char)255 * alpha;

   return *(uint64_t*)color;
}

void
engineer_render_test_game_init(Eo *window, Eo *viewport)
{
   Eo *scene, *node;
   uint64_t root, camera;
   int64_t  cameradata[6], transformdata[12], colliderdata[5];
   EntityID sphere1, sphere2, box1, plane1;

   node = engineer_node_new(window,
                 "/home/brokenshakles/Projects/SoftwareEngines/Engineer/build",
                 "Engineer_Render_Test");

   // Load our component modules here.
   printf("\nModule Load Checkpoint.\n");
   engineer_node_module_load(node, "Transform");
   engineer_node_module_load(node, "Camera");
   engineer_node_module_load(node, "Collider");
   //engineer_node_module_load(node, "Actor");

   scene = engineer_scene_new(node, "Engineer Render Test");
   root = (EntityID)0;

   transformdata[0] = sclr(0.0);
   transformdata[1] = sclr(0.0);
   transformdata[2] = sclr(8.0);
   cameradata[0] = (Sclr)viewport;

   camera = engineer_scene_entity_create(scene, root, root);
   engineer_scene_component_create(scene, root, "Transform", camera, (Data*)transformdata);
   engineer_scene_component_create(scene, root, "Camera",    camera, (Data*)cameradata);

   transformdata[0] = sclr(4.0);
   transformdata[1] = sclr(0.0);
   transformdata[2] = sclr(0.0);
   colliderdata[3]  = (uint64_t)1; // Shape/Type.
   colliderdata[0]  = (uint64_t)1; // Size.
   colliderdata[1]  = (uint64_t)0;
   colliderdata[2]  = (uint64_t)0;
   colliderdata[4]  = color(0.0, 1.0, 1.0, 0.0);

   sphere1 = engineer_scene_entity_create(scene, root, root);
   engineer_scene_component_create(scene, root, "Transform", sphere1, (Data*)transformdata);
   engineer_scene_component_create(scene, root, "Collider",  sphere1, (Data*)colliderdata);

   transformdata[0] = sclr(0.0);
   transformdata[1] = sclr(4.0);
   transformdata[2] = sclr(0.0);
   colliderdata[3]  = (uint64_t)1; // Shape/Type.
   colliderdata[0]  = (uint64_t)1; // Size.
   colliderdata[4]  = color(0.0, 0.0, 1.0, 0.0);

   sphere2 = engineer_scene_entity_create(scene, root, root);
   engineer_scene_component_create(scene, root, "Transform", sphere2, (Data*)transformdata);
   engineer_scene_component_create(scene, root, "Collider",  sphere2, (Data*)colliderdata);

   transformdata[0] = sclr(0.0);
   transformdata[1] = sclr(0.0);
   transformdata[2] = sclr(0.0);
   colliderdata[3]  = (uint64_t)2; // Shape/Type.
   colliderdata[0]  = (uint64_t)1; // Size.
   colliderdata[4]  = color(0.0, 1.0, 0.0, 0.0);

   box1 = engineer_scene_entity_create(scene, root, root);
   engineer_scene_component_create(scene, root, "Transform", box1, (Data*)transformdata);
   engineer_scene_component_create(scene, root, "Collider",  box1, (Data*)colliderdata);

   transformdata[0] = sclr( 0.0);
   transformdata[1] = sclr(-4.0);
   transformdata[2] = sclr( 0.0);
   colliderdata[3]  = (uint64_t)3; // Shape/Type.
   colliderdata[0]  = (uint64_t)1; // Size.
   colliderdata[4]  = color(1.0, 0.8, 0.6, 0.0);

   plane1 = engineer_scene_entity_create(scene, root, root);
   engineer_scene_component_create(scene, root, "Transform", plane1, (Data*)transformdata);
   engineer_scene_component_create(scene, root, "Collider",  plane1, (Data*)colliderdata);
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

