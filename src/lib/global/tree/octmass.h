#ifndef _ENGINEER_OCTMASS_H_
#define _ENGINEER_OCTMASS_H_

#include "../../../headers/Engineer.h"

typedef struct
{
   uint          version;
   Eina_Inarray *depth[32];

   uint32_t childmask:30;
   uint32_t lock:2

   uint32_t material[512];
   uint32_t light[512];
}
Engineer_Octmass;

typedef struct
{
   uint32_t index;

   uint32_t parent;
   uint32_t childmask;

   uint32_t lock:1, leaf:1;
   uint32_t topdepth:5,  bottomdepth:5;
   uint32_t updepth:5,   downdepth:5;
   uint32_t leftdepth:5, rightdepth:5;

   uint32_t top,  bottom;
   uint32_t up,   down;
   uint32_t left, right;

   uint32_t material[512];
   uint32_t light[512];
}
Engineer_Octmass_Node_0to9;

typedef struct
{
   uint32_t index[2];

   uint32_t parent;
   uint32_t childmask;

   uint32_t lock:1, leaf:1;

   uint32_t topdepth:5,  bottomdepth:5;
   uint32_t updepth:5,   downdepth:5;
   uint32_t leftdepth:5, rightdepth:5;

   uint32_t top,  bottom;
   uint32_t up,   down;
   uint32_t left, right;

   uint32_t material[512];
   uint32_t light[512];
}
Engineer_Octmass_Node_10to20;

typedef struct
{
   uint32_t index[3];

   uint32_t parent;

   uint32_t childmask;
   uint32_t lock:2;

   uint32_t topdepth:5,  bottomdepth:5;
   uint32_t updepth:5,   downdepth:5;
   uint32_t leftdepth:5, rightdepth:5;

   uint32_t top,  bottom;
   uint32_t up,   down;
   uint32_t left, right;

   uint32_t material[512];
   uint32_t light[512];
}
Engineer_Octmass_Node_21to31;

Engineer_Octmass *
engineer_octmass_factory()
{
   Engineer_Octmass *new = calloc(1, sizeof(Engineer_Octmass));
   uint count;

   for(count =  0; count < 10; count++)
   {
      new->depth[count] = eina_inarray_new(sizeof(Engineer_Octmass_Node_0to9),   0);
   }
   for(count = 10; count < 21; count++)
   {
      new->depth[count] = eina_inarray_new(sizeof(Engineer_Octmass_Node_10to20), 0);
   }
   for(count = 21; count < 32; count++)
   {
      new->depth[count] = eina_inarray_new(sizeof(Engineer_Octmass_Node_21to31), 0);
   }

   return new;
}

#endif
