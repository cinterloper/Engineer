#include "engineer_viewport.h"

// eolian_gen `pkg-config --variable=eolian_flags ecore eo evas efl` -I .
//    -I "/home/brokenshakles/.efler/efl/src/lib/" -g h engineer_viewport.eo

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

   file = fopen("../shaders/test.vert", "r");
   fseek(file, 0, SEEK_END);
   size = ftell(file);
   fseek(file, 0, SEEK_SET);
   GLbyte vertbuffer[size + 1];
   vertbuffer[size] = 0;
   fread(vertbuffer, 1, size, file);
   fclose(file);

   file = fopen("../shaders/test.frag", "r");
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

   gl->glBindAttribLocation(gld->program, 0, "position"); // ??
   gl->glLinkProgram(gld->program);
   gl->glGetProgramiv(gld->program, GL_LINK_STATUS, &linked);

   gl->glUseProgram(gld->program);

   //gld->objects_location    = gl->glGetUniformLocation(gld->program, "shader_data");
   gld->resolution_location = gl->glGetUniformLocation(gld->program, "resolution");
   gld->count_location      = gl->glGetUniformLocation(gld->program, "count");

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

struct shader_data_t objects[4];

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

   gl->glGenBuffers(1, &gld->ssbo);
   gl->glBindBuffer(GL_SHADER_STORAGE_BUFFER, gld->ssbo);
   gl->glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(objects), objects, GL_DYNAMIC_COPY);
   gl->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, gld->ssbo);
   gl->glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

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

   // Lets set up some test objects to render...
   // 585 = 512 + 64 + 8 + 1
   gld->count = 4;

   objects[0].type        =     1;
   objects[0].location[0] =   0.0 + 8.0 * cos(gld->time);
   objects[0].location[1] =   0.0;
   objects[0].location[2] = -12.0 + 8.0 * sin(gld->time);
   objects[0].size        =   1.0;
   objects[0].color[0]    =   0.0;
   objects[0].color[1]    =   1.0;
   objects[0].color[2]    =   1.0;

   objects[1].type        =     1;
   objects[1].location[0] =   0.0;
   objects[1].location[1] =   4.0;
   objects[1].location[2] = -12.0;
   objects[1].size        =   1.0;
   objects[1].color[0]    =   0.0;
   objects[1].color[1]    =   0.0;
   objects[1].color[2]    =   1.0;

   objects[2].type        =     2;
   objects[2].location[0] =   0.0;
   objects[2].location[1] =   0.0;
   objects[2].location[2] = -12.0;
   objects[2].size        =   1.0;
   objects[2].color[0]    =   0.0;
   objects[2].color[1]    =   1.0;
   objects[2].color[2]    =   0.0;

   objects[3].type        =     3;
   objects[3].location[0] =   0.0;
   objects[3].location[1] = - 4.0;
   objects[3].location[2] = -12.0;
   objects[3].size        =   1.0;
   objects[3].color[0]    =   1.0;
   objects[3].color[1]    =   0.8;
   objects[3].color[2]    =   0.6;

   // Draw a Triangle
   gl->glEnable(GL_BLEND);

   gl->glUseProgram(gld->program);

   gl->glUniform2fv(gld->resolution_location, 1,  gld->resolution);
   gl->glUniform1ui(gld->count_location,          gld->count);

   gl->glBindBuffer(GL_SHADER_STORAGE_BUFFER, gld->ssbo);
   gl->glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(objects), objects);
   gl->glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

   gl->glBindBuffer(GL_ARRAY_BUFFER, gld->vbo);

   gl->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

   // Optional - Flush the GL pipeline
   gl->glFinish();
}

static Eina_Bool
_anim(void *data)
{
   // If the game loop has updated the appropriate camera when this animator goes off...
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

/*** Begin Efl_Object Section ***/

EOLIAN Eo *
engineer_viewport_add(Eo *obj)
{
   return efl_add(ENGINEER_VIEWPORT_CLASS, obj);
}

EOLIAN static Efl_Object *
_engineer_viewport_efl_object_constructor(Eo *obj, Engineer_Viewport_Data *pd EINA_UNUSED)
{
   return efl_constructor(efl_super(obj, ENGINEER_VIEWPORT_CLASS));
}

Efl_Object *
_engineer_viewport_efl_object_finalize(Eo *obj, Engineer_Viewport_Data *pd EINA_UNUSED)
{
   obj = efl_finalize(efl_super(obj, ENGINEER_VIEWPORT_CLASS));

   Evas_Object *bx, *gl, *lb;
   Ecore_Animator *ani;
   GL_Data *gld = NULL;

   if (!(gld = calloc(1, sizeof(GL_Data)))) return NULL;

   gld->time = 0;

   evas_object_event_callback_add(efl_parent_get(obj), EVAS_CALLBACK_FREE, _win_free_cb, gld);

   bx = elm_box_add(efl_parent_get(obj));
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(efl_parent_get(obj), bx);
   //elm_box_pack_end(efl_parent_get(obj), bx);
   evas_object_show(bx);

   gl = elm_glview_version_add(efl_parent_get(obj), EVAS_GL_GLES_3_X);
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

      gld->glapi = elm_glview_gl_api_get(gl);
      evas_object_data_set(gl, "gld", gld);
      evas_object_event_callback_add(gl, EVAS_CALLBACK_DEL, _gl_del_cb, ani);
   }
   else
   {
      lb = elm_label_add(bx);
      elm_object_text_set(lb,
         "<align=left> GL backend engine is not supported.<br/>"
         " 1. Check your back-end engine or<br/>"
         " 2. Run elementary_test with engine option or<br/>"
         "    ex) $ <b>ELM_ACCEL=gl</b> elementary_test<br/>"
         " 3. Change your back-end engine from elementary_config.<br/></align>");
      evas_object_size_hint_weight_set(lb, 0.0, 0.0);
      evas_object_size_hint_align_set(lb, EVAS_HINT_FILL, EVAS_HINT_FILL);
      elm_box_pack_end(bx, lb);
      evas_object_show(lb);
   }

   return obj;
}

EOLIAN static void
_engineer_viewport_efl_object_destructor(Eo *obj EINA_UNUSED, Engineer_Viewport_Data *pd EINA_UNUSED)
{
   efl_destructor(efl_super(obj, ENGINEER_VIEWPORT_CLASS));
}

EOLIAN static void
_engineer_viewport_alpha_set(Eo *obj EINA_UNUSED, Engineer_Viewport_Data *pd,
        char alpha)
{
   pd->alpha = alpha;
}

EOLIAN static char
_engineer_viewport_alpha_get(Eo *obj EINA_UNUSED, Engineer_Viewport_Data *pd)
{
   return pd->alpha;
}

EOLIAN static void
_engineer_viewport_camera_set(Eo *obj EINA_UNUSED, Engineer_Viewport_Data *pd,
        unsigned int camera)
{
   pd->camera = camera;
}

EOLIAN static uint
_engineer_viewport_camera_get(Eo *obj EINA_UNUSED, Engineer_Viewport_Data *pd)
{
   return pd->camera;
}

#include "engineer_viewport.eo.c"
