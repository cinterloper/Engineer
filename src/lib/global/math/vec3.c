#include "vec3.h"

/*** 3D Vector Algebra Functions ***/

Vec3
engineer_math_vec3_scale(Vec3 input, Sclr factor)
{
   Vec3 output;

   output.x = MULT(input.x, factor);
   output.y = MULT(input.y, factor);
   output.z = MULT(input.z, factor);

   return output;
}

Sclr
engineer_math_vec3_dot(Vec3 inputa, Vec3 inputb)
{
   Sclr output;

   output = MULT(inputa.x, inputb.x)
          + MULT(inputa.y, inputb.y)
          + MULT(inputa.z, inputb.z);

   return output;
}

Vec3
engineer_math_vec3_cross(Vec3 inputa, Vec3 inputb)
{
   Vec3 output;

   output.x = MULT(inputa.y, inputb.z) - MULT(inputa.z, inputb.y);
   output.y = MULT(inputa.z, inputb.x) - MULT(inputa.x, inputb.z);
   output.z = MULT(inputa.x, inputb.y) - MULT(inputa.y, inputb.x);

   return output;
}

Vec3
engineer_math_vec3_normalize(Vec3 input)
{
   Vec3 output;
   Sclr basis, square, sqrt, inverse;

   basis    = BASIS;
   square   = MULT(input.x, input.x)
            + MULT(input.y, input.y)
            + MULT(input.z, input.z);
   sqrt     = SQRT(square);
   inverse  = DIVD(basis, sqrt);
   output.x = MULT(input.x, inverse);
   output.y = MULT(input.y, inverse);
   output.z = MULT(input.z, inverse);

   return output;
}

