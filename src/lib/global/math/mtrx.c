#include "mtrx.h"

Quat
engineer_math_mtrx_mult_by_quat(Mtrx multiplicand, Quat multiplier)
{
   Quat output;

   output.x = MULT(multiplicand.r0c0, multiplier.x) +
              MULT(multiplicand.r0c1, multiplier.y) +
              MULT(multiplicand.r0c2, multiplier.z) +
              MULT(multiplicand.r0c3, multiplier.w);

   output.y = MULT(multiplicand.r1c0, multiplier.x) +
              MULT(multiplicand.r1c1, multiplier.y) +
              MULT(multiplicand.r1c2, multiplier.z) +
              MULT(multiplicand.r1c3, multiplier.w);

   output.z = MULT(multiplicand.r2c0, multiplier.x) +
              MULT(multiplicand.r2c1, multiplier.y) +
              MULT(multiplicand.r2c2, multiplier.z) +
              MULT(multiplicand.r2c3, multiplier.w);

   output.w = MULT(multiplicand.r3c0, multiplier.x) +
              MULT(multiplicand.r3c1, multiplier.y) +
              MULT(multiplicand.r3c2, multiplier.z) +
              MULT(multiplicand.r3c3, multiplier.w);

   return output;
}

Mtrx
engineer_mtrx_rotation_setup(Quat input)
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
   output.r0c3 = 0;

   // Fill in the second row.
   output.r1c0 = xy  + wz;
   output.r1c1 = wSq - xSq + ySq - zSq;
   output.r1c2 = yz  - wx;
   output.r1c3 = 0;

   // Fill in the third row.
   output.r2c0 = xz  - wy;
   output.r2c1 = yz  + wx;
   output.r2c2 = wSq - xSq - ySq + zSq;
   output.r2c3 = 0;

   output.r3c0 = 0;
   output.r3c1 = 0;
   output.r3c2 = 0;
   output.r3c3 = BASIS;

   return output;
}
