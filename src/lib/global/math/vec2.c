#include "vec2.h"

/*** 2D Vector Algebra Functions ***/

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

