#include "vec2.h"

/*** 2D Vector Algebra Functions ***/

Vec2Buffer
engineer_math_vec2_mult(Vec2 *va, Vec2 *vb)
{
   Vec2Buffer output;

   output.x = MULT(va->x, vb->x);
   output.y = MULT(va->y, vb->y);

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
   SclrBuffer basis, square, sqrt, inverse;

   basis    = BASIS;
   square   = MULT(v->x, v->x) + MULT(v->y, v->y);
   sqrt     = SQRT(&square);
   inverse  = DIVD(&basis, &sqrt);
   output.x = MULT(v->x, &inverse);
   output.y = MULT(v->y, &inverse);

   return output;
}

