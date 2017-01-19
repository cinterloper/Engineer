#include "quat.h"

QuatBuffer
engineer_math_quat_multiply(Quat *q1, Quat *q2)
{
   QuatBuffer output;

   output.w = MULT(q1->w, q2->w) - MULT(q1->x, q2->x) - MULT(q1->y, q2->y) - MULT(q1->z, q2->z);
   output.x = MULT(q1->w, q2->x) + MULT(q1->x, q2->w) + MULT(q1->y, q2->z) - MULT(q1->z, q2->y);
   output.y = MULT(q1->w, q2->y) + MULT(q1->y, q2->w) + MULT(q1->z, q2->x) - MULT(q1->x, q2->z); // x<>z Switched!
   output.z = MULT(q1->w, q2->z) + MULT(q1->z, q2->w) + MULT(q1->x, q2->y) - MULT(q1->y, q2->x);

   return output;
}

MtrxBuffer
engineer_math_quat_matrixify(Quat *q)
{
   MtrxBuffer output;
   SclrBuffer factor, twoW, twoX, twoY;
   SclrBuffer wSq, xSq, ySq, zSq;
   SclrBuffer xy, xz, yz, wx, wy, wz;

   // Helper quantities, we calculate these up front to avoid redundancies.
   factor = BASIS << 1;
   twoW = MULT(q->w, &factor);
   twoX = MULT(q->x, &factor);
   twoY = MULT(q->y, &factor);
   wSq  = MULT(q->w, q->w);
   xSq  = MULT(q->x, q->x);
   ySq  = MULT(q->y, q->y);
   zSq  = MULT(q->z, q->z);
   xy   = MULT(&twoX, q->y);
   xz   = MULT(&twoX, q->z);
   yz   = MULT(&twoY, q->z);
   wx   = MULT(&twoW, q->x);
   wy   = MULT(&twoW, q->y);
   wz   = MULT(&twoW, q->z);

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

QuatBuffer
engineer_math_quat_normalize(Quat *q)
{
   QuatBuffer output;
   SclrBuffer basis, square, sqrt, inverse;

   basis    = BASIS;
   square   = MULT(q->x, q->x) + MULT(q->y, q->y) + MULT(q->z, q->z) + MULT(q->w, q->w);
   sqrt     = SQRT(&square);
   inverse  = DIVD(&basis, &sqrt);
   output.x = MULT(q->x, &inverse);
   output.y = MULT(q->y, &inverse);
   output.z = MULT(q->z, &inverse);
   output.w = MULT(q->w, &inverse);

   //detect badness
   //assert(square > 0.1f);

   return output;
}

