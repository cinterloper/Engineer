#include "vec2.h"

/*** 2D Vector Algebra Functions ***/
/*
Vec2
engineer_math_vec2_mult(Vec2 va, Vec2 vb)
{
   Vec2 output;

   output.x = MULT(va.x, vb.x);
   output.y = MULT(va.y, vb.y);

   return output;
}

Vec2
engineer_math_vec2_divd(Vec2 va, Vec2 vb)
{
   Vec2 output;

   output.x = DIVD(va.x, vb.x);
   output.y = DIVD(va.y, vb.y);

   return output;
}
*/
Vec2
engineer_math_vec2_scale(Vec2 input, Sclr factor)
{
   Vec2 output;

   output.x = MULT(input.x, factor);
   output.y = MULT(input.y, factor);

   return output;
}

Sclr
engineer_math_vec2_dot(Vec2 inputa, Vec2 inputb)
{
   Sclr output;

   output = MULT(inputa.x, inputb.x)
          + MULT(inputa.y, inputb.y);

   return output;
}

Vec2
engineer_math_vec2_normalize(Vec2 input)
{
   Vec2 output;
   Sclr basis, dot, sqrt, inverse;

   basis    = BASIS;
   dot      = VEC2DOT(input, input);
   sqrt     = SQRT(dot);
   inverse  = DIVD(basis, sqrt);
   output   = VEC2SCLE(input, inverse);

   return output;
}

