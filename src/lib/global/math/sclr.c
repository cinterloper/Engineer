#include "sclr.h"

extern Sclr cordic_gain_h;

/*** Elementary Arithmatic Functions ***/

SclrBuffer
engineer_math_mult(Sclr *a, Sclr *b)
{
   SclrBuffer output = *a * *b;
   output += ((output & (1 << (RADIX - 1)) ) << 1);
   output >>= RADIX;

   return output;
}

SclrBuffer
engineer_math_divd(Sclr *a, Sclr *b)
{
   Sclr output = (*a << RADIX)/ *b;

   return output;
}

SclrBuffer
engineer_math_abs(Sclr *a)
{
   SclrBuffer output;

   output = (*a ^ (*a >> (SCALE - 1))) - (*a >> (SCALE - 1));

   return output;
}

SclrBuffer
engineer_math_clamp(Sclr *a, Sclr *min, Sclr *max)
{
   SclrBuffer input, output;

   *min <<= 1;
   *max <<= 1;
   input  = *a - *min;
   *a     = ((*a + *min) - ABS(&input)) >> 1;
   input  = *a - *max;
   output = ((*a + *max) + ABS(&input)) >> 1;

   return output;
}

SclrBuffer
engineer_math_exp(Sclr *a) // Fixme //
{
   SclrBuffer output, sinh, cosh;

   cosh = cordic_gain_h;
   sinh = 0;
   cordic_hyperbolic_zmode(&cosh, &sinh, a);
   output = (sinh + cosh);

   return output;
}

SclrBuffer
engineer_math_ln(Sclr *a) // Fixme //
{
   // Domain: 0.1 < a < 9.58 units.
   SclrBuffer output, x, y, z;

   x = *a + BASIS;
   y = *a - BASIS;
   z = 0;
   cordic_hyperbolic_ymode(&x, &y, &z);
   output =  z << 1;

   return output;
}

SclrBuffer
engineer_math_sqrt(Sclr *a)
{
   // Domain: |a| units.
   // Christophe Meessen's shift-and-add algorithim for approximating
   //    square roots of fixed point numbers.
   SclrBuffer output, x, y, z, mask;

   x = ABS(a);
   y = (Sclr)1 << (RADIX + 14);
   z = 0;
   for (unsigned int i = 0; i < (SCALE - 8); i++)
   {
      output = z + y;
      mask = (x - output) >> (SCALE - 1);
      x =  x         - ((    output) & ~mask);
      z = (z & mask) + ((y + output) & ~mask);
      x = x << 1;
      y = y >> 1;
   }
   output = z >> 8;

   return output;
}

