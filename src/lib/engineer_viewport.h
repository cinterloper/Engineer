#ifndef _ENGINEER_VIEWPORT_H_
#define _ENGINEER_VIEWPORT_H_

#include "Engineer.h"
#include <math.h>
//#include <elm_widget.h>

typedef struct _GL_Data GL_Data;

// GL related data here..
struct _GL_Data
{
   Eo          *viewport;
   Evas_GL_API *glapi;
   GLuint       program;
   GLuint       vtx_shader;
   GLuint       fgmt_shader;
   GLuint       vbo;
   GLuint       ssbo;

   GLuint       objects_location;
   GLuint       resolution_location;
   GLuint       count_location;

   GLfloat      time;
   GLfloat      resolution[2];
   GLuint       count;
};

typedef struct
{
   Evas_Object   *gl;
   uint           alpha;
   Vec3           position;
   ComponentID    camera;   // The camera that is currently registered to the viewport.
   Eina_Inarray  *objects;  // Stores the visible collider/shader_data sent in by the camera.
}
Engineer_Viewport_Data;

//Collider_Data objects[4];
void *objects;

EOLIAN Eo *
engineer_viewport_add(Eo *obj);

#include "engineer_viewport.eo.h"

#endif

