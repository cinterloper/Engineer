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
   Eo *viewport EINA_UNUSED = engineer_render_test_viewport_init(window);
   engineer_render_test_game_init(window);

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
engineer_render_test_game_init(Eo *root)
{
   Eo *node = engineer_node_new(root,
                 "/home/brokenshakles/Projects/SoftwareEngines/Engineer/build",
                 "Engineer_Render_Test");

   // Load our component modules here.
   engineer_node_module_load(node, "Transform");
   // engineer_node_module_load(node, "Collider");
   // engineer_node_module_load(node, "Actor");
   // engineer_node_module_load(node, "Camera");

   Eo *scene EINA_UNUSED = engineer_scene_new(node, "engrendertest");

   //uint root, camera, sphere;
   //root = engineer_scene_entity_create(scene, (uint)0, "Root");

   //camera = engineer_scene_entity_create(scene, root, "Camera");
   // After the camera is made, attach it to the viewport Eo.

   //sphere = engineer_scene_entity_create(scene, root, "Sphere");

   //engineer_node_file_save(node);
}


typedef struct _GL_Data GL_Data;

// GL related data here..
struct _GL_Data
{
   Evas_GL_API *glapi;
   GLuint       program;
   GLuint       vtx_shader;
   GLuint       fgmt_shader;
   GLuint       vbo;

   GLuint       resolution_location;
   GLuint       time_location;

   GLfloat      resolution[2];
   GLfloat      time;
};

static void
_win_free_cb(void *data, Evas *e EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   free(data);
}

static GLuint
load_shader(GL_Data *gld, GLenum type, const char *shader_src)
{
   Evas_GL_API *gl = gld->glapi;
   GLuint shader;
   GLint compiled;

   // Create the shader object
   shader = gl->glCreateShader(type);
   if (shader==0)
      return 0;

   // Load/Compile shader source
   gl->glShaderSource(shader, 1, &shader_src, NULL);
   gl->glCompileShader(shader);
   gl->glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

   if (!compiled)
     {
        GLint info_len = 0;
        gl->glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
        if (info_len > 1)
          {
             char* info_log = malloc(sizeof(char) * info_len);

             gl->glGetShaderInfoLog(shader, info_len, NULL, info_log);
             printf("Error compiling shader:\n%s\n======\n%s\n======\n", info_log, shader_src );
             free(info_log);
          }
        gl->glDeleteShader(shader);
        return 0;
     }

   return shader;
}

// Initialize the shader and program object
static int
init_shaders(GL_Data *gld)
{
   Evas_GL_API *gl = gld->glapi;

   // Get our shader source for use from target file.
   FILE *file;
   uint64_t size;

   file = fopen("../../shaders/test.vert", "r");
   fseek(file, 0, SEEK_END);
   size = ftell(file);
   fseek(file, 0, SEEK_SET);
   GLbyte vertbuffer[size + 1];
   vertbuffer[size] = 0;
   fread(vertbuffer, 1, size, file);
   fclose(file);

   file = fopen("../../shaders/test.frag", "r");
   fseek(file, 0, SEEK_END);
   size = ftell(file);
   fseek(file, 0, SEEK_SET);
   GLbyte fragbuffer[size + 1];
   fragbuffer[size] = 0;
   fread(fragbuffer, 1, size, file);
   fclose(file);

   GLint linked;

   // Load the vertex/fragment shaders
   gld->vtx_shader  = load_shader(gld, GL_VERTEX_SHADER,   (const char*)vertbuffer);
   gld->fgmt_shader = load_shader(gld, GL_FRAGMENT_SHADER, (const char*)fragbuffer);

   // Create the program object
   gld->program = gl->glCreateProgram();
   if (gld->program==0)
      return 0;

   gl->glAttachShader(gld->program, gld->vtx_shader);
   gl->glAttachShader(gld->program, gld->fgmt_shader);

   gl->glBindAttribLocation(gld->program, 0, "position");
   gl->glLinkProgram(gld->program);
   gl->glGetProgramiv(gld->program, GL_LINK_STATUS, &linked);

   gl->glUseProgram(gld->program);
   gld->resolution_location = gl->glGetUniformLocation(gld->program, "resolution");
   gld->time_location       = gl->glGetUniformLocation(gld->program, "time");

   if (!linked)
     {
        GLint info_len = 0;
        gl->glGetProgramiv(gld->program, GL_INFO_LOG_LENGTH, &info_len);
        if (info_len > 1)
          {
             char* info_log = malloc(sizeof(char) * info_len);

             gl->glGetProgramInfoLog(gld->program, info_len, NULL, info_log);
             printf("Error linking program:\n%s\n", info_log);
             free(info_log);
          }
        gl->glDeleteProgram(gld->program);
        return 0;
     }
   return 1;
}

// Callbacks
static void
_init_gl(Evas_Object *obj)
{
   GL_Data *gld = evas_object_data_get(obj, "gld");
   Evas_GL_API *gl = gld->glapi;
   GLfloat vVertices[] = { -1.0f,  1.0f, 0.0f,
                           -1.0f, -1.0f, 0.0f,
                            1.0f,  1.0f, 0.0f,
                            1.0f, -1.0f, 0.0f };

   if (!init_shaders(gld))
     {
        printf("Error Initializing Shaders\n");
        return;
     }

   gl->glGenBuffers(1, &gld->vbo);
   gl->glBindBuffer(GL_ARRAY_BUFFER, gld->vbo);
   gl->glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);
   gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                             0, 0);
   gl->glEnableVertexAttribArray(0);
}

static void
_del_gl(Evas_Object *obj)
{
   GL_Data *gld = evas_object_data_get(obj, "gld");
   if (!gld)
     {
        printf("Unable to get GL_Data. \n");
        return;
     }
   Evas_GL_API *gl = gld->glapi;

   gl->glDeleteShader(gld->vtx_shader);
   gl->glDeleteShader(gld->fgmt_shader);
   gl->glDeleteProgram(gld->program);
   gl->glDeleteBuffers(1, &gld->vbo);

   evas_object_data_del(obj, "gld");
}

static void
_resize_gl(Evas_Object *obj)
{
   int w, h;
   GL_Data *gld = evas_object_data_get(obj, "gld");
   Evas_GL_API *gl = gld->glapi;

   elm_glview_size_get(obj, &w, &h);

   // GL Viewport stuff. you can avoid doing this if viewport is all the
   // same as last frame if you want
   gl->glViewport(0, 0, w, h);
}

static void
_draw_gl(Evas_Object *obj)
{
   Evas_GL_API *gl = elm_glview_gl_api_get(obj);
   GL_Data *gld = evas_object_data_get(obj, "gld");
   if (!gld) return;
   int w, h;

   elm_glview_size_get(obj, &w, &h);

   gl->glViewport(0, 0, w, h);
   gl->glClear(GL_COLOR_BUFFER_BIT);

   gld->resolution[0] = w;
   gld->resolution[1] = h;
   if(gld->time > (2 * 3.141592653589793238462643383)) gld->time = 0;
   gld->time += (float)1/30;

   // Draw a Triangle
   gl->glEnable(GL_BLEND);

   gl->glUseProgram(gld->program);

   gl->glUniform2fv(gld->resolution_location, 1,  gld->resolution);
   gl->glUniform1fv(gld->time_location,       1, &gld->time);

   gl->glBindBuffer(GL_ARRAY_BUFFER, gld->vbo);

   gl->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   // Optional - Flush the GL pipeline
   gl->glFinish();
}

static Eina_Bool
_anim(void *data)
{
   elm_glview_changed_set(data);
   return ECORE_CALLBACK_RENEW;
}
/*
static void
_close_cb(void *data, Evas_Object *obj EINA_UNUSED,
          void *event_info EINA_UNUSED)
{
   evas_object_del(data);
}
*/
static void
_gl_del_cb(void *data, Evas *evas EINA_UNUSED, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   ecore_animator_del(data);
}

Eo *
engineer_render_test_viewport_init(Eo *window)
{
   //Evas_Object *viewport = engineer_viewport_add(window);
   //evas_object_size_hint_weight_set(viewport, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   //evas_object_size_hint_align_set(viewport, EVAS_HINT_FILL, EVAS_HINT_FILL);
   //evas_object_show(viewport);

   Evas_Object *bx, *gl, *lb;
   Ecore_Animator *ani;
   GL_Data *gld = NULL;

   if (!(gld = calloc(1, sizeof(GL_Data)))) return NULL;

   gld->time = 0;

   evas_object_event_callback_add(window, EVAS_CALLBACK_FREE, _win_free_cb, gld);

   bx = elm_box_add(window);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(window, bx);
   evas_object_show(bx);

   gl = elm_glview_add(window);
   if (gl)
     {
        evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
        evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        elm_glview_mode_set(gl, ELM_GLVIEW_ALPHA | ELM_GLVIEW_DEPTH);
        elm_glview_resize_policy_set(gl, ELM_GLVIEW_RESIZE_POLICY_RECREATE);
        elm_glview_render_policy_set(gl, ELM_GLVIEW_RENDER_POLICY_ON_DEMAND);
        elm_glview_mode_set(gl, 0
           | ELM_GLVIEW_ALPHA
           | ELM_GLVIEW_DEPTH
           | ELM_GLVIEW_DIRECT
        );
        elm_glview_init_func_set(gl, _init_gl);
        elm_glview_del_func_set(gl, _del_gl);
        elm_glview_resize_func_set(gl, _resize_gl);
        elm_glview_render_func_set(gl, _draw_gl);
        elm_box_pack_end(bx, gl);
        evas_object_show(gl);

        elm_object_focus_set(gl, EINA_TRUE);

        ani = ecore_animator_add(_anim, gl);

        printf("Animator Frametime Checkpoint: %f\n", ecore_animator_frametime_get());

        gld->glapi = elm_glview_gl_api_get(gl);
        evas_object_data_set(gl, "gld", gld);
        evas_object_event_callback_add(gl, EVAS_CALLBACK_DEL, _gl_del_cb, ani);
     }
   else
     {
        lb = elm_label_add(bx);
        elm_object_text_set(lb, "<align=left> GL backend engine is not supported.<br/>"
                            " 1. Check your back-end engine or<br/>"
                            " 2. Run elementary_test with engine option or<br/>"
                            "    ex) $ <b>ELM_ACCEL=gl</b> elementary_test<br/>"
                            " 3. Change your back-end engine from elementary_config.<br/></align>");
        evas_object_size_hint_weight_set(lb, 0.0, 0.0);
        evas_object_size_hint_align_set(lb, EVAS_HINT_FILL, EVAS_HINT_FILL);
        elm_box_pack_end(bx, lb);
        evas_object_show(lb);
     }

   return gl;

}

