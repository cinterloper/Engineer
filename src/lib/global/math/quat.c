#include "quat.h"

Quat
engineer_math_quat_multiply(Quat multiplicand, Quat multiplier)
{
   #define ma multiplicand
   #define mb multiplier
   Quat output;

   output.w = MULT(ma.w, mb.w) - MULT(ma.x, mb.x) - MULT(ma.y, mb.y) - MULT(ma.z, mb.z);
   output.x = MULT(ma.w, mb.x) + MULT(ma.x, mb.w) + MULT(ma.y, mb.z) - MULT(ma.z, mb.y);
   output.y = MULT(ma.w, mb.y) + MULT(ma.y, mb.w) + MULT(ma.z, mb.x) - MULT(ma.x, mb.z); // x<>z Switched!
   output.z = MULT(ma.w, mb.z) + MULT(ma.z, mb.w) + MULT(ma.x, mb.y) - MULT(ma.y, mb.x);

   return output;
   #undef mb
   #undef ma
}

Mtrx
engineer_math_quat_matrixify(Quat input)
{
   Mtrx output;
   Sclr factor, twoW, twoX, twoY;
   Sclr wSq, xSq, ySq, zSq;
   Sclr xy, xz, yz, wx, wy, wz;

   // Helper quantities, we calculate these up front to avoid redundancies.
   factor = BASIS << 1;
   twoW = MULT(input.w, factor);
   twoX = MULT(input.x, factor);
   twoY = MULT(input.y, factor);
   wSq  = MULT(input.w, input.w);
   xSq  = MULT(input.x, input.x);
   ySq  = MULT(input.y, input.y);
   zSq  = MULT(input.z, input.z);
   xy   = MULT(twoX, input.y);
   xz   = MULT(twoX, input.z);
   yz   = MULT(twoY, input.z);
   wx   = MULT(twoW, input.x);
   wy   = MULT(twoW, input.y);
   wz   = MULT(twoW, input.z);

   // Fill in the first row.
   output.r0c0 = wSq + xSq - ySq - zSq;
   output.r0c1 = xy  - wz;
   output.r0c2 = xz  + wy;
   // Fill in the second row.
   output.r1c0 = xy  + wz;
   output.r1c1 = wSq - xSq + ySq - zSq;
   output.r1c2 = yz  - wx;
   // Fill in the third row.
   output.r2c0 = xz  - wy;
   output.r2c1 = yz  + wx;
   output.r2c2 = wSq - xSq - ySq + zSq;

   return output;
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

