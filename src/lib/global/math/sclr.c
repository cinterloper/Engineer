#include "sclr.h"

extern Sclr cordic_gain_h;

/*** Elementary Arithmatic Functions ***/

Sclr
engineer_math_mult(Sclr multiplicand, Sclr multiplier)
{
   Sclr output;

   output   = multiplicand * multiplier;
   output  += (output & (1 << (RADIX - 1))) << 1;
   output >>= RADIX;

   return output;
}

Sclr
engineer_math_divd(Sclr dividend, Sclr divisor)
{
   Sclr output;

   output = (dividend << RADIX) / divisor;

   return output;
}

Sclr
engineer_math_abs(Sclr input)
{
   Sclr output;

   output = (input ^ (input >> (SCALE - 1))) - (input >> (SCALE - 1));

   return output;
}

Sclr
engineer_math_clamp(Sclr input, Sclr min, Sclr max)
{
   Sclr buffer, output;

   min <<= 1;
   max <<= 1;

   buffer = input - min;
   input  = ((input + min) - ABS(buffer)) >> 1;
   buffer = input - max;
   output = ((input + max) + ABS(buffer)) >> 1;

   return output;
}

Sclr
engineer_math_exp(Sclr input) // Fixme //
{
   Vec3 buffer;
   Sclr output;

   buffer.x = cordic_gain_h; // Cosh()
   buffer.y = 0;             // Sinh()
   buffer.z = input;

   buffer = cordic_hyperbolic_zmode(buffer);
   output = buffer.y + buffer.x;

   return output;
}

Sclr
engineer_math_ln(Sclr input) // Fixme //
{
   // Domain: 0.1 < a < 9.58 units.
   Vec3 buffer;
   Sclr output;

   buffer.x = input + BASIS;
   buffer.y = input - BASIS;
   buffer.z = 0;

   buffer = cordic_hyperbolic_ymode(buffer);
   output = buffer.z << 1;

   return output;
}

Sclr
engineer_math_sqrt(Sclr input)
{
   // Domain: |a| units.
   // This is a branchless variant of Christophe Meessen's shift-and-add algorithim
   //    for approximating square roots of fixed point numbers.
   Vec3 buffer;
   Sclr output, mask;

   buffer.x = ABS(input);
   buffer.y = (Sclr)1 << (RADIX + 14);
   buffer.z = 0;

   for (uint32_t i = 0; i < (SCALE - 8); i++)
   {
      output   =  buffer.z + buffer.y;
      mask     = (buffer.x - output) >> (SCALE - 1);
      buffer.x =  buffer.x         - ((           output) & ~mask);
      buffer.z = (buffer.z & mask) + ((buffer.y + output) & ~mask);
      buffer.x =  buffer.x << 1;
      buffer.y =  buffer.y >> 1;
   }
   output = buffer.z >> 8;

   return output;
}

