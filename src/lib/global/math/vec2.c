#include "vec2.h"

/*** 2D Vector Algebra Functions ***/

Vec2Buffer
engineer_math_vec2_scle(Vec2 *v, Sclr *s)
{
   Vec2Buffer output;

   output.x = MULT(v->x, s);
   output.y = MULT(v->y, s);

   return output;
}

Vec2Buffer
engineer_math_vec2_mult(Vec2 *va, Vec2 *vb)
{
   Vec2Buffer output;

   output.x = MULT(va->x, vb->x);
   output.y = MULT(va->y, vb->y);

   return output;
}

Vec2Buffer
engineer_math_vec2_divd(Vec2 *va, Vec2 *vb)
{
   Vec2Buffer output;

   output.x = DIVD(va->x, vb->x);
   output.y = DIVD(va->y, vb->y);

   return output;
}

SclrBuffer
engineer_math_vec2_dot(Vec2 *va, Vec2 *vb)
{
   SclrBuffer output;

   output = MULT(va->x, vb->x) + MULT(va->y, vb->y);

   return output;
}

Vec2Buffer
engineer_math_vec2_normalize(Vec2 *v)
{
   Vec2Buffer output;
   SclrBuffer basis, dot, sqrt, inverse;

   basis    = BASIS;
   dot      = VEC2DOT(v, v);
   sqrt     = SQRT(&dot);
   inverse  = DIVD(&basis, &sqrt);

   output   = VEC2SCLE(v, &inverse);

   return output;
}

