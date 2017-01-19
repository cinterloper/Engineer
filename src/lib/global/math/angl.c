#include "angl.h"

extern Sclr cordic_gain_c;
extern Sclr cordic_gain_h;

/*** Elementary Arithmatic Functions ***/

AnglBuffer
engineer_math_mult_angl(Angl *a, Angl *b)
{
   #ifndef CORDIC_LINEAR
   AnglBuffer output = *a * *b;
   output += ((output & ((Angl)1 << (ANGLRADIX - 1)) ) << 1);
   output >>= ANGLRADIX;

   return output;
   #else
   Sclr x = *a;
   Sclr y =  0;
   Sclr z = *b;
   cordic_linear_zmode(&x, &y, &z);

   return y;
   #endif
}

AnglBuffer
engineer_math_divd_angl(Angl *a, Angl *b)
{
   #ifndef CORDIC_LINEAR
   AnglBuffer output = (*a << ANGLRADIX)/ *b;

   return output;
   #else
   Sclr x = *b;
   Sclr y = *a;
   Sclr z =  0;
   cordic_linear_ymode(&x, &y, &z);

   return z;
   #endif
}

/*** Elementary Trigonomic Functions ***/

Vec2Buffer
engineer_math_sincos(Angl *a)
{
   // Domain: |a| < 1.74
   Vec2Buffer output;
   SclrBuffer sin, cos;

   sin = 0;
   cos = cordic_gain_c;
   cordic_circular_zmode(&cos, &sin, a);
   output.x = ANGL2SCLR(cos);
   output.y = ANGL2SCLR(sin);

   return output;
}

SclrBuffer
engineer_math_tan(Angl *a)
{
   // Domain: |a| < 1.74
   SclrBuffer output, sin, cos;

   sin = 0;
   cos = cordic_gain_c;
   cordic_circular_zmode(&cos, &sin, a);
   output = DIVDANGL(&sin, &cos);
   output = ANGL2SCLR(output);

   return output;
}

SclrBuffer
engineer_math_atan(Angl *a)
{
   // Domain: all a
   SclrBuffer output, x, z;

   x = ANGLBASIS;
   z = 0;
   cordic_circular_ymode(&x, a, &z);
   output = ANGL2SCLR(z);

   return output;
}

SclrBuffer
engineer_math_asin(Angl *a) // Fixme //
{
   // Domain: |a| < 0.98
   // We use the trig identity for this, as there really isnt a good way to vectorize it directly.
   SclrBuffer output;

   //output = ANGL2SCLR(ATAN(DIVD(a, SQRT(1 - MULT(a, a)))));

   SclrBuffer x, z;

   x = cordic_gain_c;
   z = 0;
   cordic_circular_aymode(&x, a, &z);
   output = ANGL2SCLR(z);

   return output;
}


/*** Hyperbolic Functions ***/

Vec2Buffer
engineer_math_sincosh(Angl *a)
{
   // Domain: |a| < 1.13 OR |a| <= 1.125, after scaling,
   Vec2Buffer output;
   SclrBuffer cosh, sinh;

   sinh  = 0;
   cosh  = cordic_gain_h;
   cordic_hyperbolic_zmode(&cosh, &sinh, a);
   output.x = cosh;
   output.y = sinh;

   return output;
}

SclrBuffer
engineer_math_tanh(Angl *a)
{
   // Domain: |a| < 1.13 units.
   SclrBuffer output, sinh, cosh;

   cosh = cordic_gain_h;
   sinh = 0;
   cordic_hyperbolic_zmode(&cosh, &sinh, a);
   output = DIVDANGL(&sinh, &cosh);

   return output;
}

SclrBuffer
engineer_math_atanh(Angl *a)
{
   // Domain: |a| < 1.13 units.
   SclrBuffer output, x, z;

   x = ANGLBASIS;
   z = 0;
   cordic_hyperbolic_ymode(&x, a, &z);
   output = z;

   return output;
}

