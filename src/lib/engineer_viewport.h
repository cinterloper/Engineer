#ifndef _ENGINEER_VIEWPORT_H_
#define _ENGINEER_VIEWPORT_H_

#include "../headers/Engineer.h"
//#include <OpenGL/gl.h>
//#include <elm_widget.h>

typedef struct _GL_Data GL_Data;

// GL related data here..
struct _GL_Data
{
   Evas_GL_API *glapi;
   GLuint       program;
   GLuint       vtx_shader;
   GLuint       fgmt_shader;
   GLuint       vbo;
   GLuint       ssbo;

   GLuint       resolution_location;
   GLuint       time_location;

   GLfloat      resolution[2];
   GLfloat      time;
};

struct shader_data_t
{
  uint  type;
  float location[3];
  float size;
  float color[3];
} shader_data;

typedef struct
{
   uint alpha;
   uint camera;
}
Engineer_Viewport_Data;

EOLIAN Eo *
engineer_viewport_add(Eo *obj);

#include "engineer_viewport.eo.h"

#endif

