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

   printf("Name: %s, Version: %s\n", argv[0], PACKAGE_VERSION);
   printf("UINT_NULL %d, ULONG_NULL %ld\n", UINT_NULL, ULONG_NULL);

   Eo *window   = engineer_render_test_window_init();
   Eo *viewport = engineer_render_test_viewport_init(window);
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
   elm_config_accel_preference_set("opengl");
   Evas_Object *window = elm_win_util_standard_add("main", "Engineer Render Test");
   elm_win_focus_highlight_enabled_set(window, EINA_TRUE);
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   //evas_object_smart_callback_add(window, "delete,request", _eng_window_del, window);
   evas_object_resize(window, 800, 800);
   evas_object_show(window);

   return window;
}

const float unit_matrix[] =
{
   1.0f, 0.0f, 0.0f, 0.0f,
   0.0f, 1.0f, 0.0f, 0.0f,
   0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 1.0f
};

   static const float vertices[] =
   {
     1.0f,  1.0f, -0.5f,
     1.0f, -1.0f, -0.5f,
    -1.0f,  1.0f, -0.5f,
    -1.0f,  1.0f, -0.5f,
     1.0f, -1.0f, -0.5f,
    -1.0f, -1.0f, -0.5f,
   };

   typedef struct
   {
      Evas_GL_API *glapi;
      GLuint program;
      GLuint vtx_shader;
      GLuint fgmt_shader;
      GLuint vbo;
      GLuint vertexID;
      //GLuint colorID;
      GLuint mvpLoc;
      GLuint positionLoc;
      GLuint resolutionLoc;
      GLuint timeLoc;
      //GLuint colorLoc;
      GLfloat   model[16], mvp[16];
      GLfloat   view[16];
      Eina_Bool mouse_down : 1;
      Eina_Bool initialized : 1;
   }
   GLData;

static void
customLoadIdentity(float matrix[16])
{
   for (int i = 0; i < 16; i++)
        matrix[i] = unit_matrix[i];
}

static void
customMutlMatrix(float matrix[16], const float matrix0[16], const float matrix1[16])
{
   int i, row, column;
   float temp[16];
   for (column = 0; column < 4; column++)
     {
        for (row = 0; row < 4; row++)
          {
             temp[column * 4 + row] = 0.0f;
             for (i = 0; i < 4; i++)
                  temp[column * 4 + row] += matrix0[i * 4 + row] * matrix1[column * 4 + i];
          }
     }
   for (i = 0; i < 16; i++)
        matrix[i] = temp[i];
}

static void
customScale(float matrix[16], const float sx, const float sy, const float sz)
{
   matrix[0]  *= sx;
   matrix[1]  *= sx;
   matrix[2]  *= sx;
   matrix[3]  *= sx;

   matrix[4]  *= sy;
   matrix[5]  *= sy;
   matrix[6]  *= sy;
   matrix[7]  *= sy;

   matrix[8]  *= sz;
   matrix[9]  *= sz;
   matrix[10] *= sz;
   matrix[11] *= sz;
}

static void
customRotate(float matrix[16], const float anglex, const float angley, const float anglez)
{
   const float pi = 3.141592f;
   float temp[16];
   float rz = 2.0f * pi * anglez / 360.0f;
   float rx = 2.0f * pi * anglex / 360.0f;
   float ry = 2.0f * pi * angley / 360.0f;
   float sy = sinf(ry);
   float cy = cosf(ry);
   float sx = sinf(rx);
   float cx = cosf(rx);
   float sz = sinf(rz);
   float cz = cosf(rz);

   customLoadIdentity(temp);

   temp[0] = cy * cz - sx * sy * sz;
   temp[1] = cz * sx * sy + cy * sz;
   temp[2] = -cx * sy;

   temp[4] = -cx * sz;
   temp[5] = cx * cz;
   temp[6] = sx;

   temp[8] = cz * sy + cy * sx * sz;
   temp[9] = -cy * cz * sx + sy * sz;
   temp[10] = cx * cy;

   customMutlMatrix(matrix, matrix, temp);
}

static int
customFrustum(float result[16], const float left, const float right, const float bottom, const float top, const float near, const float far)
{
   if ((right - left) == 0.0f || (top - bottom) == 0.0f || (far - near) == 0.0f) return 0;

   result[0] = 2.0f / (right - left);
   result[1] = 0.0f;
   result[2] = 0.0f;
   result[3] = 0.0f;

   result[4] = 0.0f;
   result[5] = 2.0f / (top - bottom);
   result[6] = 0.0f;
   result[7] = 0.0f;

   result[8] = 0.0f;
   result[9] = 0.0f;
   result[10] = -2.0f / (far - near);
   result[11] = 0.0f;

   result[12] = -(right + left) / (right - left);
   result[13] = -(top + bottom) / (top - bottom);
   result[14] = -(far + near) / (far - near);
   result[15] = 1.0f;

   return 1;
}

   static int
   init_shaders(GLData *gld)
   {
      Evas_GL_API *gl = gld->glapi;

      // Get our shader source for use from target file.
      FILE *file;
      uint64_t size;

      file = fopen("../shaders/test.vert", "r");
      if (file) printf("Shader Init Checkpoint, ../shaders/test.vert found.\n");
      else printf("Shader Init Checkpoint, ../shaders/test.vert NOT found.\n");
      fseek(file, 0, SEEK_END);
      size = ftell(file);
      fseek(file, 0, SEEK_SET);
      GLbyte vertbuffer[size];
      fread(vertbuffer, size, 0, file);
      fclose(file);

      file = fopen("../shaders/test.frag", "r");
      if (file) printf("Shader Init Checkpoint, ../shaders/test.frag found.\n");
      else printf("Shader Init Checkpoint, ../shaders/test.frag NOT found.\n");
      fseek(file, 0, SEEK_END);
      size = ftell(file);
      fseek(file, 0, SEEK_SET);
      GLbyte fragbuffer[size];
      fread(fragbuffer, size, 0, file);
      fclose(file);

      GLint compiled;
      const char *p = vertbuffer;

      //vertex shader
      gld->vtx_shader = gl->glCreateShader(GL_VERTEX_SHADER);
      gl->glShaderSource(gld->vtx_shader, 1, &p, NULL);
      gl->glCompileShader(gld->vtx_shader);
      gl->glGetShaderiv(gld->vtx_shader, GL_COMPILE_STATUS, &compiled);
      if (!compiled)
      {
         GLint info_len = 0;
         gl->glGetShaderiv(gld->vtx_shader, GL_INFO_LOG_LENGTH, &info_len);
         if (info_len > 1)
         {
            char* info_log = malloc(sizeof(char) * info_len);
            gl->glGetShaderInfoLog(gld->vtx_shader, info_len, NULL, info_log);
            printf("Error compiling shader:\n%s\n======\n%s\n======\n", info_log, p);
            free(info_log);
         }
         gl->glDeleteShader(gld->vtx_shader);
      }

      //fragment shader
      p = fragbuffer;
      gld->fgmt_shader = gl->glCreateShader(GL_FRAGMENT_SHADER);
      gl->glShaderSource(gld->fgmt_shader, 1, &p, NULL);
      gl->glCompileShader(gld->fgmt_shader);
      gl->glGetShaderiv(gld->fgmt_shader, GL_COMPILE_STATUS, &compiled);
      if (!compiled)
      {
         GLint info_len = 0;
         gl->glGetShaderiv(gld->fgmt_shader, GL_INFO_LOG_LENGTH, &info_len);
         if (info_len > 1)
         {
            char* info_log = malloc(sizeof(char) * info_len);
            gl->glGetShaderInfoLog(gld->fgmt_shader, info_len, NULL, info_log);
            printf("Error compiling shader:\n%s\n======\n%s\n======\n", info_log, p);
            free(info_log);
         }
         gl->glDeleteShader(gld->fgmt_shader);
      }


      gld->program = gl->glCreateProgram();

      GLint linked;
      // Load the vertex/fragment shaders
      gl->glAttachShader(gld->program, gld->vtx_shader);
      gl->glAttachShader(gld->program, gld->fgmt_shader);
      gl->glDeleteShader(gld->vtx_shader);
      gl->glDeleteShader(gld->fgmt_shader);

      gl->glBindAttribLocation(gld->program, 0, "a_position");
      gl->glLinkProgram(gld->program);
      gl->glGetProgramiv(gld->program, GL_LINK_STATUS, &linked);
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
      gld->mvpLoc      = gl->glGetUniformLocation(gld->program, "u_mvp_mat");
      gld->resolutionLoc = gl->glGetUniformLocation(gld->program, "resolution");
      gld->timeLoc     = gl->glGetUniformLocation(gld->program, "time");
      gld->positionLoc = gl->glGetAttribLocation(gld->program, "a_position");
      //gld->colorLoc    = gl->glGetAttribLocation(gld->program, "a_color");
      return 1;
   }

   // Callbacks
   // intialize callback that gets called once for intialization
   static void
   _init_viewport(Evas_Object *obj)
   {
      int w, h;
      GLData *gld = evas_object_data_get(obj, "gld");
      Evas_GL_API *gl = gld->glapi;

      elm_glview_size_get(obj, &w, &h);

      if (!gld->initialized)
      {
         if (!init_shaders(gld))
         {
            printf("Error Initializing Shaders\n");
            return;
         }

         gl->glGenBuffers(1, &gld->vertexID);
         gl->glBindBuffer(GL_ARRAY_BUFFER, gld->vertexID);
         gl->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

         //gl->glGenBuffers(1, &gld->colorID);
         //gl->glBindBuffer(GL_ARRAY_BUFFER, gld->colorID);
         //gl->glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

         gld->initialized = EINA_TRUE;
      }
   }

   // draw callback is where all the main GL rendering happens
   static void
   _draw_viewport(Evas_Object *obj)
   {
      Evas_GL_API *gl = elm_glview_gl_api_get(obj);
      GLData *gld = evas_object_data_get(obj, "gld");
      if(!gld) return;
      int w, h;
      int r, g, b, a;
      //scale
      //double scalex = elm_slider_value_get(gld->slx);
      //double scaley = elm_slider_value_get(gld->sly);
      //double scalez = elm_slider_value_get(gld->slz);

      r = 255; g = 255; b = 0; a = 0;

      elm_glview_size_get(obj, &w, &h);

      gl->glClearDepthf(1.0f);
      gl->glClearColor(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
      gl->glEnable(GL_CULL_FACE);

      gl->glViewport(0, 0, w, h);
      gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      gl->glUseProgram(gld->program);

      gl->glEnableVertexAttribArray(gld->positionLoc);
      gl->glBindBuffer(GL_ARRAY_BUFFER, gld->vertexID);
      gl->glVertexAttribPointer(gld->positionLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

      //gl->glEnableVertexAttribArray(gld->colorLoc);
      //gl->glBindBuffer(GL_ARRAY_BUFFER, gld->colorID);
      //gl->glVertexAttribPointer(gld->colorLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

      customLoadIdentity(gld->model);
      //customRotate(gld->model, gld->xangle, gld->yangle, gld->zangle++);
      //scale
      //customScale(gld->model, scalex, scaley, scalez);
      customMutlMatrix(gld->mvp, gld->view, gld->model);

      gl->glUniform2f(gld->resolutionLoc, w, h);
      gl->glUniform1f(gld->timeLoc, ecore_time_get());
      gl->glUniformMatrix4fv(gld->mvpLoc, 1, GL_FALSE, gld->mvp);
      gl->glDrawArrays(GL_TRIANGLES, 0, 36);
      gl->glFlush();
   }

   // resize callback gets called every time object is resized
   static void
   _resize_viewport(Evas_Object *obj)
   {
      int w, h;
      GLData *gld = evas_object_data_get(obj, "gld");
      Evas_GL_API *gl = gld->glapi;
      float aspect;

      elm_glview_size_get(obj, &w, &h);
      //customLoadIdentity(gld->view);

      if (w > h)
      {
         aspect = (float) w / h;
         //customFrustum(gld->view, -1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -1.0, 1.0);
      }
      else
      {
         aspect = (float) h / w;
         //customFrustum(gld->view, -1.0, 1.0, -1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
      }
   }

   // delete callback gets called when glview is deleted
   static void
   _del_viewport(Evas_Object *obj)
   {
      GLData *gld = evas_object_data_get(obj, "gld");
      if (!gld)
      {
         printf("Unable to get GLData. \n");
         return;
      }

      Evas_GL_API *gl = gld->glapi;
      gl->glDeleteShader(gld->vtx_shader);
      gl->glDeleteShader(gld->fgmt_shader);
      gl->glDeleteProgram(gld->program);
      evas_object_data_del((Evas_Object*) obj, "..gld");
   }

// just need to notify that glview has changed so it can render
static Eina_Bool
_anim(void *data)
{
   elm_glview_changed_set(data);
   return EINA_TRUE;
}

Eo *
engineer_render_test_viewport_init(Eo *window)
{
   // Attach Engineer_Viewport to the window and display it here.
   Ecore_Animator *ani;
   GLData *gld = NULL;
   if (!(gld = calloc(1, sizeof(GLData)))) return 1;

   Eo *viewport = elm_glview_add(window);
   gld->glapi = elm_glview_gl_api_get(viewport);
   evas_object_size_hint_align_set(viewport, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(viewport, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   // mode is simply for supporting alpha, depth buffering, and stencil
   // buffering.
   elm_glview_mode_set(viewport, ELM_GLVIEW_ALPHA | ELM_GLVIEW_DEPTH);
   // resize policy tells glview what to do with the surface when it
   // resizes.  ELM_GLVIEW_RESIZE_POLICY_RECREATE will tell it to
   // destroy the current surface and recreate it to the new size
   elm_glview_resize_policy_set(viewport, ELM_GLVIEW_RESIZE_POLICY_RECREATE);
   // render policy tells glview how it would like glview to render
   // gl code. ELM_GLVIEW_RENDER_POLICY_ON_DEMAND will have the gl
   // calls called in the pixel_get callback, which only gets called
   // if the object is visible, hence ON_DEMAND.  ALWAYS mode renders
   // it despite the visibility of the object.
   elm_glview_render_policy_set(viewport, ELM_GLVIEW_RENDER_POLICY_ON_DEMAND);

   elm_glview_init_func_set(viewport, _init_viewport);
   elm_glview_del_func_set(viewport, _del_viewport);
   elm_glview_resize_func_set(viewport, _resize_viewport);
   elm_glview_render_func_set(viewport, _draw_viewport);

   evas_object_show(viewport);

   ani = ecore_animator_add(_anim, viewport);
   evas_object_data_set(viewport, "ani", ani);
   evas_object_data_set(viewport, "gld", gld);

   gld->mouse_down = EINA_FALSE;
   gld->initialized = EINA_FALSE;

   //Evas_Object *viewport = engineer_viewport_add(window);
   //evas_object_size_hint_weight_set(viewport, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   //evas_object_size_hint_align_set(viewport, EVAS_HINT_FILL, EVAS_HINT_FILL);
   //evas_object_show(viewport);

   return viewport;
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
