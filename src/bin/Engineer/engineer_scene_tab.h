#ifndef ENGINEER_SCENE_H_
#define ENGINEER_SCENE_H_

#include "engineer_project.h"

typedef struct
{
   Eng_Window_State *window;
   Eng_Window_State *target;
   Evas_Object      *path;
}
Eng_Scene_Tab_Loader_State;

#endif
