#include "quat.h"

Quat
engineer_math_quat_multiply(Quat multiplicand, Quat multiplier)
{
   #define q1 multiplicand
   #define q2 multiplier
   Quat output;
   Sclr A, B, C, D, E, F, G, H;

   A = MULT((q1.w + q1.x), (q2.w + q2.x));
   B = MULT((q1.z - q1.y), (q2.y - q2.z));
   C = MULT((q1.w - q1.x), (q2.y + q2.z));
   D = MULT((q1.y + q1.z), (q2.w - q2.x));
   E = MULT((q1.x + q1.z), (q2.x + q2.y));
   F = MULT((q1.x - q1.z), (q2.x - q2.y));
   G = MULT((q1.w + q1.y), (q2.w - q2.z));
   H = MULT((q1.w - q1.y), (q2.w + q2.z));

   output.w = B + DIVD(-E - F + G + H, 2);
   output.x = A - DIVD( E + F + G + H, 2);
   output.y = C + DIVD( E - F + G - H, 2);
   output.z = D + DIVD( E - F - G + H, 2);

   return output;
   #undef mb
   #undef ma
}

Quat
engineer_math_quat_normalize(Quat input)
{
   Quat output;
   Sclr basis, square, sqrt, inverse;

   basis    = BASIS;
   square   = MULT(input.x, input.x)
            + MULT(input.y, input.y)
            + MULT(input.z, input.z)
            + MULT(input.w, input.w);
   sqrt     = SQRT(square);
   inverse  = DIVD(basis, sqrt);
   output.x = MULT(input.x, inverse);
   output.y = MULT(input.y, inverse);
   output.z = MULT(input.z, inverse);
   output.w = MULT(input.w, inverse);

   //detect badness
   //assert(square > 0.1f);

   return output;
}

