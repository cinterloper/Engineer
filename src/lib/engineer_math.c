#include "engineer_math.h"

// Gains
Sclr cordic_gain_c;
Sclr cordic_gain_h;

// LUTs
Sclr cordic_lut_c[SCALE]; // Circular Lookup Table.
Sclr cordic_lut_h[SCALE]; // Hyperbolic Lookup Table.
Sclr cordic_lut_m[SCALE]; // Hyperbolic Repeat Mask Lookup Table.

void
cordic_init()
{
   #ifdef CORDIC_LINEAR
   cordic_linear_init();
   #endif
   cordic_circular_init();
   cordic_hyperbolic_init();
}

/*** Linear CORDIC ***/

#ifdef CORDIC_LINEAR
// This is mostly useless, it's included as a simplified example of a working CORDIC.
// For educational purposes only.
Sclr cordic_lut_l[SCALE]; // Linear Lookup Table.

void
cordic_linear_init()
{
   // Compute our Lookup Table for the linear CORDIC algorithims.
   Sclr t = SCLRBASE;
   uint i;
   for (i = 0; i < SCALE; ++i)
   {
      cordic_lut_l[i] = t;
      t = t >> 1;
   }
}

void
cordic_linear_ymode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x  = *x0;
   Sclr y  = *y0;
   Sclr z  = *z0;
   Sclr ds = 0;

   for (uint i = 0; i < SCALE; ++i)
   {
      ds = y >> (SCALE - 1); // Most Significant Bit

      y  = y - (((x >> i)          ^ ds) - ds);
      z  = z + (((cordic_lut_l[i]) ^ ds) - ds);
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}

void
cordic_linear_zmode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x  = *x0;
   Sclr y  = *y0;
   Sclr z  = *z0;
   Sclr ds = 0;

   for (uint i = 0; i < SCALE; ++i)
   {
      ds = z >> (SCALE - 1); // Most Significant Bit

      y  = y + (((x >> i)          ^ ds) - ds);
      z  = z - (((cordic_lut_l[i]) ^ ds) - ds);
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}
#endif


/*** Circular CORDIC ***/

void
cordic_circular_init()
{
   // Compute our Lookup Table for the circular CORDIC computers.
   double t = 1.0;
   unsigned int i;
   for (i = 0; i < SCALE; ++i)
   {
      cordic_lut_c[i] = (Sclr)(atan(t) * ANGLBASIS);
      t /= 2;
   }

   // Calculate circular gain by evaluating cos(0) without inverse gain.
   Sclr x = ANGLBASIS;
   Sclr y = 0;
   Sclr z = 0;
   cordic_circular_zmode(&x, &y, &z);
   y = ANGLBASIS;
   cordic_gain_c = DIVDANGL(&y, &x);
}

void
cordic_circular_ymode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x  = *x0;
   Sclr y  = *y0;
   Sclr z  = *z0;
   Sclr dx = 0;
   Sclr ds = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      ds = y >> (SCALE - 1); // Most Significant Bit

      dx = x + (((y >> i)          ^ ds) - ds);
      y  = y - (((x >> i)          ^ ds) - ds);
      z  = z + (((cordic_lut_c[i]) ^ ds) - ds);

      x  = dx;
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}

void
cordic_circular_aymode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x  = *x0;
   Sclr y  = 0;
   Sclr z  = *z0;
   Sclr ay = *y0;
   Sclr dx = 0;
   Sclr ds = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      ds = (y + ay) >> (SCALE - 1); // Most Significant Bit

      dx = x - (((y >> i)          ^ ds) - ds);
      y  = y + (((x >> i)          ^ ds) - ds);
      z  = z - (((cordic_lut_c[i]) ^ ds) - ds);

      x  = dx;
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}

void
cordic_circular_zmode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x  = *x0;
   Sclr y  = *y0;
   Sclr z  = *z0;
   Sclr dx = 0;
   Sclr ds = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      ds = z >> (SCALE - 1); // Most Significant Bit

      dx = x - (((y >> i)          ^ ds) - ds);
      y  = y + (((x >> i)          ^ ds) - ds);
      z  = z - (((cordic_lut_c[i]) ^ ds) - ds);

      x  = dx;
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}


/*** Hyperbolic CORDIC ***/
// The 'x' iteration has the opposite sign. Iterations 4, 7, .. 3k+1 are repeated.
// Iteration 0 is not performed.

void
cordic_hyperbolic_init() // Fixme //
{
   // Compute our Lookup Table for the hyperbolic CORDIC computers.
   Sclr t = ANGLBASIS;
   unsigned int i;
   for (i = 0; i < SCALE; ++i)
   {
      t = t >> 1;
      cordic_lut_h[i] = (Sclr)(log((ANGLBASIS + t) / (ANGLBASIS - t))) >> 1;
   }

   // Set up our usage mask for the cyclical doubled iteration of the hyperbolic cordic.
   t = 3;
   for (i = 0; i < SCALE; i++)
   {
     if(t)
     {
        cordic_lut_m[i] = 0;
        t--;
     }
     else
     {
        cordic_lut_m[i] = (Sclr)ldexp(1, SCALE);
        t = 2;
     }
   }

   // Calculate hyperbolic gain.
   Sclr x = ANGLBASIS;
   Sclr y = 0;
   Sclr z = 0;
   cordic_hyperbolic_zmode(&x, &y, &z);
   y = ANGLBASIS;
   cordic_gain_h = DIVD(&y, &x);// (ANGLBASE << ANGLMAG)/ x
}

void
cordic_hyperbolic_ymode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x = *x0;
   Sclr y = *y0;
   Sclr z = *z0;
   Sclr dx = 0;
   Sclr ds = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      ds = y >> (SCALE - 1); // Most Significant Bit

      dx = x - (((y >> i)          ^ ds) - ds);
      y  = y - (((x >> i)          ^ ds) - ds);
      z  = z + (((cordic_lut_c[i]) ^ ds) - ds);

      x  = dx;

      dx = x - ((((y >> i)          ^ ds) - ds) & cordic_lut_m[i]);
      y  = y - ((((x >> i)          ^ ds) - ds) & cordic_lut_m[i]);
      z  = z + ((((cordic_lut_c[i]) ^ ds) - ds) & cordic_lut_m[i]);

      x  = dx;
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}

void
cordic_hyperbolic_zmode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x = *x0;
   Sclr y = *y0;
   Sclr z = *z0;
   Sclr dx = 0;
   Sclr ds = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      ds = z >> (SCALE - 1); // Most Significant Bit

      dx = x + (((y >> i)          ^ ds) - ds);
      y  = y + (((x >> i)          ^ ds) - ds);
      z  = z - (((cordic_lut_c[i]) ^ ds) - ds);

      x  = dx;

      dx = x + ((((y >> i)          ^ ds) - ds) & cordic_lut_m[i]);
      y  = y + ((((x >> i)          ^ ds) - ds) & cordic_lut_m[i]);
      z  = z - ((((cordic_lut_c[i]) ^ ds) - ds) & cordic_lut_m[i]);

      x  = dx;
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}


/*** Elementary Arithmatic Functions ***/

SclrData
engineer_math_mult(Sclr *a, Sclr *b)
{
   SclrData output = *a * *b;
   output += ((output & (1 << (RADIX - 1)) ) << 1);
   output >>= RADIX;

   return output;
}

SclrData
engineer_math_divd(Sclr *a, Sclr *b)
{
   Sclr output = (*a << RADIX)/ *b;

   return output;
}

AnglData
engineer_math_mult_angl(Angl *a, Angl *b)
{
   #ifndef CORDIC_LINEAR
   AnglData output = *a * *b;
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

AnglData
engineer_math_divd_angl(Angl *a, Angl *b)
{
   #ifndef CORDIC_LINEAR
   AnglData output = (*a << ANGLRADIX)/ *b;

   return output;
   #else
   Sclr x = *b;
   Sclr y = *a;
   Sclr z =  0;
   cordic_linear_ymode(&x, &y, &z);

   return z;
   #endif
}

SclrData
engineer_math_abs(Sclr *a)
{
   SclrData output;

   output = (*a ^ (*a >> (SCALE - 1))) - (*a >> (SCALE - 1));

   return output;
}

SclrData
engineer_math_clamp(Sclr *a, Sclr *min, Sclr *max)
{
   SclrData input, output;

   *min <<= 1;
   *max <<= 1;
   input  = *a - *min;
   *a     = ((*a + *min) - ABS(&input)) >> 1;
   input  = *a - *max;
   output = ((*a + *max) + ABS(&input)) >> 1;

   return output;
}

SclrData
engineer_math_exp(Sclr *a) // Fixme //
{
   SclrData output, sinh, cosh;

   cosh = cordic_gain_h;
   sinh = 0;
   cordic_hyperbolic_zmode(&cosh, &sinh, a);
   output = (sinh + cosh);

   return output;
}

SclrData
engineer_math_ln(Sclr *a) // Fixme //
{
   // Domain: 0.1 < a < 9.58 units.
   SclrData output, x, y, z;

   x = *a + BASIS;
   y = *a - BASIS;
   z = 0;
   cordic_hyperbolic_ymode(&x, &y, &z);
   output =  z << 1;

   return output;
}

SclrData
engineer_math_sqrt(Sclr *a)
{
   // Domain: |a| units.
   // Christophe Meessen's shift-and-add algorithim for approximating
   //    square roots of fixed point numbers.
   SclrData output, x, y, z, mask;

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

/*** Elementary Trigonomic Functions ***/

Vec2Data
engineer_math_sincos(Angl *a)
{
   // Domain: |a| < 1.74
   Vec2Data output;
   SclrData sin, cos;

   sin = 0;
   cos = cordic_gain_c;
   cordic_circular_zmode(&cos, &sin, a);
   output.x = ANGL2SCLR(cos);
   output.y = ANGL2SCLR(sin);

   return output;
}

SclrData
engineer_math_tan(Angl *a)
{
   // Domain: |a| < 1.74
   SclrData output, sin, cos;

   sin = 0;
   cos = cordic_gain_c;
   cordic_circular_zmode(&cos, &sin, a);
   output = DIVDANGL(&sin, &cos);
   output = ANGL2SCLR(output);

   return output;
}

SclrData
engineer_math_atan(Angl *a)
{
   // Domain: all a
   SclrData output, x, z;

   x = ANGLBASIS;
   z = 0;
   cordic_circular_ymode(&x, a, &z);
   output = ANGL2SCLR(z);

   return output;
}

SclrData
engineer_math_asin(Angl *a) // Fixme //
{
   // Domain: |a| < 0.98
   // We use the trig identity for this, as there really isnt a good way to vectorize it directly.
   SclrData output;

   //output = ANGL2SCLR(ATAN(DIVD(a, SQRT(1 - MULT(a, a)))));

   SclrData x, z;

   x = cordic_gain_c;
   z = 0;
   cordic_circular_aymode(&x, a, &z);
   output = ANGL2SCLR(z);

   return output;
}


/*** Hyperbolic Functions ***/

Vec2Data
engineer_math_sincosh(Angl *a)
{
   // Domain: |a| < 1.13 OR |a| <= 1.125, after scaling,
   Vec2Data output;
   SclrData cosh, sinh;

   sinh  = 0;
   cosh  = cordic_gain_h;
   cordic_hyperbolic_zmode(&cosh, &sinh, a);
   output.x = cosh;
   output.y = sinh;

   return output;
}

SclrData
engineer_math_tanh(Angl *a)
{
   // Domain: |a| < 1.13 units.
   SclrData output, sinh, cosh;

   cosh = cordic_gain_h;
   sinh = 0;
   cordic_hyperbolic_zmode(&cosh, &sinh, a);
   output = DIVDANGL(&sinh, &cosh);

   return output;
}

SclrData
engineer_math_atanh(Angl *a)
{
   // Domain: |a| < 1.13 units.
   SclrData output, x, z;

   x = ANGLBASIS;
   z = 0;
   cordic_hyperbolic_ymode(&x, a, &z);
   output = z;

   return output;
}


/*** Vector Algebra Functions ***/

Vec2Data
engineer_math_vec2(Sclr xinput, Sclr yinput)
{
   Vec2Data output;

   output.x = xinput;
   output.y = yinput;

   return output;
}

SclrData
engineer_math_vec2_dot(Vec2 *va, Vec2 *vb)
{
   SclrData output;

   output = MULT(va->x, vb->x) + MULT(va->y, vb->y);

   return output;
}

Vec2Data
engineer_math_vec2_normalize(Vec2 *v)
{
   Vec2Data output;
   SclrData basis, square, sqrt, inverse;

   basis    = BASIS;
   square   = MULT(v->x, v->x) + MULT(v->y, v->y);
   sqrt     = SQRT(&square);
   inverse  = DIVD(&basis, &sqrt);
   output.x = MULT(v->x, &inverse);
   output.y = MULT(v->y, &inverse);

   return output;
}

Vec3Data
engineer_math_vec3(Sclr xinput, Sclr yinput, Sclr zinput)
{
   Vec3Data output;

   output.x = xinput;
   output.y = yinput;
   output.z = zinput;

   return output;
}

SclrData
engineer_math_vec3_dot(Vec3 *va, Vec3 *vb)
{
   SclrData output;

   output = MULT(va->x, vb->x) + MULT(va->y, vb->y) + MULT(va->z, vb->z);

   return output;
}

Vec3Data
engineer_math_vec3_cross(Vec3 *va, Vec3 *vb)
{
   Vec3Data output;

   output.x = MULT(va->y, vb->z) - MULT(va->z, vb->y);
   output.y = MULT(va->z, vb->x) - MULT(va->x, vb->z);
   output.z = MULT(va->x, vb->y) - MULT(va->y, vb->x);

   return output;
}

Vec3Data
engineer_math_vec3_normalize(Vec3 *v)
{
   Vec3Data output;
   SclrData basis, square, sqrt, inverse;

   basis    = BASIS;
   square   = MULT(v->x, v->x) + MULT(v->y, v->y) + MULT(v->z, v->z);
   sqrt     = SQRT(&square);
   inverse  = DIVD(&basis, &sqrt);
   output.x = MULT(v->x, &inverse);
   output.y = MULT(v->y, &inverse);
   output.z = MULT(v->z, &inverse);

   return output;
}

QuatData
engineer_math_quat(Sclr winput, Sclr xinput, Sclr yinput, Sclr zinput)
{
   QuatData output;

   output.w = winput;
   output.x = xinput;
   output.y = yinput;
   output.z = zinput;

   return output;
}

QuatData
engineer_math_quat_multiply(Quat *q1, Quat *q2)
{
   QuatData output;

   output.w = MULT(q1->w, q2->w) - MULT(q1->x, q2->x) - MULT(q1->y, q2->y) - MULT(q1->z, q2->z);
   output.x = MULT(q1->w, q2->x) + MULT(q1->x, q2->w) + MULT(q1->y, q2->z) - MULT(q1->z, q2->y);
   output.y = MULT(q1->w, q2->y) + MULT(q1->y, q2->w) + MULT(q1->z, q2->x) - MULT(q1->x, q2->z); // x<>z Switched!
   output.z = MULT(q1->w, q2->z) + MULT(q1->z, q2->w) + MULT(q1->x, q2->y) - MULT(q1->y, q2->x);

   return output;
}

MtrxData
engineer_math_quat_matrixify(Quat *q)
{
   MtrxData output;
   SclrData factor, twoW, twoX, twoY;
   SclrData wSq, xSq, ySq, zSq;
   SclrData xy, xz, yz, wx, wy, wz;

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

QuatData
engineer_math_quat_normalize(Quat *q)
{
   QuatData output;
   SclrData basis, square, sqrt, inverse;

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

