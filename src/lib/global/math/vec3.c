#include "vec3.h"

SclrBuffer
engineer_math_vec3_dot(Vec3 *va, Vec3 *vb)
{
   SclrBuffer output;

   output = MULT(va->x, vb->x) + MULT(va->y, vb->y) + MULT(va->z, vb->z);

   return output;
}

Vec3Buffer
engineer_math_vec3_cross(Vec3 *va, Vec3 *vb)
{
   Vec3Buffer output;

   output.x = MULT(va->y, vb->z) - MULT(va->z, vb->y);
   output.y = MULT(va->z, vb->x) - MULT(va->x, vb->z);
   output.z = MULT(va->x, vb->y) - MULT(va->y, vb->x);

   return output;
}

Vec3Buffer
engineer_math_vec3_normalize(Vec3 *v)
{
   Vec3Buffer output;
   SclrBuffer basis, square, sqrt, inverse;

   basis    = BASIS;
   square   = MULT(v->x, v->x) + MULT(v->y, v->y) + MULT(v->z, v->z);
   sqrt     = SQRT(&square);
   inverse  = DIVD(&basis, &sqrt);
   output.x = MULT(v->x, &inverse);
   output.y = MULT(v->y, &inverse);
   output.z = MULT(v->z, &inverse);

   return output;
}

