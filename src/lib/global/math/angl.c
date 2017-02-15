#include "angl.h"

extern Sclr cordic_gain_c;
extern Sclr cordic_gain_h;

/*** Elementary Arithmatic Functions ***/

Angl
engineer_math_angl_mult(Angl multiplicand, Angl multiplier)
{
   Angl output;

   output   = multiplicand * multiplier;
   output  += (output & ((Angl)1 << (ANGLRADIX - 1)) ) << 1;
   output >>= ANGLRADIX;

   return output;
}

Angl
engineer_math_angl_divd(Angl dividend, Angl divisor)
{
   Angl output;

   output = (dividend << ANGLRADIX) / divisor;

   return output;
}

/*** Elementary Trigonomic Functions ***/

Vec2
engineer_math_sincos(Angl input)
{
   // Domain: |a| < 1.74
   Vec3 buffer;
   Vec2 output;

   buffer.x = cordic_gain_c; // Cos()
   buffer.y = 0;             // Sin()
   buffer.z = input;

   buffer   = cordic_circular_zmode(buffer);
   output.x = ANGL2SCLR(buffer.x);
   output.y = ANGL2SCLR(buffer.y);

   return output;
}

Sclr
engineer_math_tan(Angl input)
{
   // Domain: |a| < 1.74
   Vec3 buffer;
   Sclr output;

   buffer.x = cordic_gain_c; // Cos()
   buffer.y = 0;             // Sin()
   buffer.z = input;

   buffer = cordic_circular_zmode(buffer);
   output = ANGLDIVD(buffer.y, buffer.x);
   output = ANGL2SCLR(output);

   return output;
}

Sclr
engineer_math_atan(Angl input)
{
   // Domain: all a
   Vec3 buffer;
   Sclr output;

   buffer.x = ANGLBASIS;
   buffer.y = input;
   buffer.z = 0;

   buffer = cordic_circular_ymode(buffer);
   output = ANGL2SCLR(buffer.z);

   return output;
}

Sclr
engineer_math_asin(Angl input) // Fixme //
{
   // Domain: |a| < 0.98

   Vec3 buffer;
   Sclr output;

   buffer.x = cordic_gain_c;
   buffer.y = input;
   buffer.z = 0;

   buffer = cordic_circular_aymode(buffer);
   output = ANGL2SCLR(buffer.z);

   //We will use the trig identity for this if there isn't a good way to vectorize it directly.
   //output = ANGL2SCLR(ATAN(DIVD(a, SQRT(1 - MULT(a, a)))));

   return output;
}


/*** Hyperbolic Functions ***/

Vec2
engineer_math_sincosh(Angl input)
{
   // Domain: |a| < 1.13 OR |a| <= 1.125, after scaling,
   Vec3 buffer;
   Vec2 output;

   buffer.x = cordic_gain_h; // Cosh()
   buffer.y = 0;             // Sinh()
   buffer.z = input;

   buffer   = cordic_hyperbolic_zmode(buffer);
   output.x = buffer.x;
   output.y = buffer.y;

   return output;
}

Sclr
engineer_math_tanh(Angl input)
{
   // Domain: |a| < 1.13 units.
   Vec3 buffer;
   Sclr output;

   buffer.x = cordic_gain_h; // Cosh()
   buffer.y = 0;             // Sinh()
   buffer.z = input;

   buffer = cordic_hyperbolic_zmode(buffer);
   output = ANGLDIVD(buffer.y, buffer.x);

   return output;
}

Sclr
engineer_math_atanh(Angl input)
{
   // Domain: |a| < 1.13 units.
   Vec3 buffer;
   Sclr output;

   buffer.x = ANGLBASIS;
   buffer.y = input;
   buffer.z = 0;         // Atanh()

   buffer = cordic_hyperbolic_ymode(buffer);
   output = buffer.z;

   return output;
}

