#include "engineer_math.h"

// Gains
Word cordic_gain_c;
Word cordic_gain_h;

// LUTs
Word cordic_lut_c[SCALE]; // Circular Lookup Table.
Word cordic_lut_h[SCALE]; // Hyperbolic Lookup Table.
Word cordic_lut_m[SCALE]; // Hyperbolic Repeat Mask Lookup Table.

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
Word cordic_lut_l[SCALE]; // Linear Lookup Table.

void
cordic_linear_init()
{
   // Compute our Lookup Table for the linear CORDIC algorithims.
   Word t = SCLRBASE;
   uint i;
   for (i = 0; i < SCALE; ++i)
   {
      cordic_lut_l[i] = t;
      t = t >> 1;
   }
}

void
cordic_linear_ymode(Word *x0, Word *y0, Word *z0)
{
   Word x  = *x0;
   Word y  = *y0;
   Word z  = *z0;
   Word ds = 0;

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
cordic_linear_zmode(Word *x0, Word *y0, Word *z0)
{
   Word x  = *x0;
   Word y  = *y0;
   Word z  = *z0;
   Word ds = 0;

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
   uint i;
   for (i = 0; i < SCALE; ++i)
   {
      cordic_lut_c[i] = (Word)(atan(t) * ANGLBASE);
      t /= 2;
   }

   // Calculate circular gain by evaluating cos(0) without inverse gain.
   Word x = ANGLBASE;
   Word y = 0;
   Word z = 0;
   cordic_circular_zmode(&x, &y, &z);

   cordic_gain_c = ANGLDIVD(ANGLBASE, x);
}

void
cordic_circular_ymode(Word *x0, Word *y0, Word *z0)
{
   Word x  = *x0;
   Word y  = *y0;
   Word z  = *z0;
   Word dx = 0;
   Word ds = 0;

   for (uint i = 0; i < SCALE; i++)
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
cordic_circular_aymode(Word *x0, Word *y0, Word *z0)
{
   Word x  = *x0;
   Word y  = 0;
   Word z  = *z0;
   Word ay = *y0;
   Word dx = 0;
   Word ds = 0;

   for (uint i = 0; i < SCALE; i++)
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
cordic_circular_zmode(Word *x0, Word *y0, Word *z0)
{
   Word x  = *x0;
   Word y  = *y0;
   Word z  = *z0;
   Word dx = 0;
   Word ds = 0;

   for (uint i = 0; i < SCALE; i++)
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
// The `x' iteration has the opposite sign. Iterations 4, 7, .. 3k+1 are repeated.
// Iteration 0 is not performed.

void
cordic_hyperbolic_init() // Fixme //
{
   // Compute our Lookup Table for the hyperbolic CORDIC computers.
   Word t = ANGLBASE;
   uint i;
   for (i = 0; i < SCALE; ++i)
   {
      t = t >> 1;
      cordic_lut_h[i] = (Word)(log((ANGLBASE + t) / (ANGLBASE - t))) >> 1;
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
        cordic_lut_m[i] = (Word)ldexp(1, SCALE);
        t = 2;
     }
   }

   // Calculate hyperbolic gain.
   Word x = ANGLBASE;
   Word y = 0;
   Word z = 0;
   cordic_hyperbolic_zmode(&x, &y, &z);
   cordic_gain_h = DIVD(ANGLBASE, x);// (ANGLBASE << ANGLMAG)/ x
}

void
cordic_hyperbolic_ymode(long *x0, long *y0, long *z0)
{
   long x = *x0;
   long y = *y0;
   long z = *z0;
   long dx = 0;
   long ds = 0;

   for (uint i = 0; i < SCALE; i++)
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
cordic_hyperbolic_zmode(long *x0, long *y0, long *z0)
{
   long x = *x0;
   long y = *y0;
   long z = *z0;
   long dx = 0;
   long ds = 0;

   for (uint i = 0; i < SCALE; i++)
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


/*** Elementary Scalar Functions ***/

EngSclr
engineer_math_mult(EngSclr a, EngSclr b)
{
   EngSclr output = a * b;
   output += ((output & (1 << (SCLRMAG - 1)) ) << 1);
   output >>= SCLRMAG;

   return output;
}

EngSclr
engineer_math_divd(EngSclr a, EngSclr b)
{
   EngSclr output = (a << SCLRMAG)/ b;

   return output;
}

EngSclr
engineer_math_abs(EngSclr a)
{
   EngSclr output;

   output = (a ^ (a >> (SCALE - 1))) - (a >> (SCALE - 1));

   return output;
}

EngSclr
engineer_math_clamp(EngSclr a, EngSclr min, EngSclr max)
{
   EngSclr output;

   min <<= 1;
   max <<= 1;
   a      = ((a + min) - ABS(a - min)) >> 1;
   output = ((a + max) + ABS(a - max)) >> 1;

   return output;
}

EngSclr
engineer_math_exp(EngSclr a) // Fixme //
{
   EngSclr output;
   Word sinh, cosh;

   cosh = cordic_gain_h;
   sinh = 0;
   cordic_hyperbolic_zmode(&cosh, &sinh, &a);
   output = (sinh + cosh);

   return output;
}

EngSclr
engineer_math_ln(EngSclr a) // Fixme //
{
   // Domain: 0.1 < a < 9.58 units.
   EngSclr output;
   Word x, y, z;

   x = a + SCLRBASE;
   y = a - SCLRBASE;
   z = 0;
   cordic_hyperbolic_ymode(&x, &y, &z);
   output =  z << 1;

   return output;
}

EngSclr
engineer_math_sqrt(EngSclr a)
{
   // Domain: |a| units.
   // Christophe Meessen's shift-and-add algorithim for approximating
   //    square roots of fixed point numbers.
   EngSclr output;
   Word x, y, z, mask;

   x = ABS(a);
   y = (Word)1 << (SCLRMAG + 14);
   z = 0;
   for (uint i = 0; i < (SCALE - 8); i++)
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


/*** Elementary Angular Functions ***/

EngAngl
engineer_math_angl_mult(EngAngl a, EngAngl b)
{
   #ifndef CORDIC_LINEAR
   EngAngl output = a * b;
   output += ((output & ((Word)1 << (ANGLMAG - 1)) ) << 1);
   output >>= ANGLMAG;

   return output;
   #else
   Word x = a;
   Word y = 0;
   Word z = b;
   cordic_linear_zmode(&x, &y, &z);

   return y;
   #endif
}

EngAngl
engineer_math_angl_divd(EngAngl a, EngAngl b)
{
   #ifndef CORDIC_LINEAR
   Rstr abuf = a;
   Rstr bbuf = b;
   EngAngl output = (abuf << ANGLMAG)/ bbuf;

   return output;
   #else
   Word x = b;
   Word y = a;
   Word z = 0;
   cordic_linear_ymode(&x, &y, &z);

   return z;
   #endif
}


/*** Elementary Trigonomic Functions ***/

EngVec2
engineer_math_sincos(EngAngl a)
{
   // Domain: |a| < 1.74
   EngVec2 output;
   Word sin, cos;

   sin = 0;
   cos = cordic_gain_c;
   cordic_circular_zmode(&cos, &sin, &a);
   output.x = ANGL2SCLR(cos);
   output.y = ANGL2SCLR(sin);

   return output;
}

EngSclr
engineer_math_tan(EngAngl a)
{
   // Domain: |a| < 1.74
   EngSclr output;
   Word sin, cos;

   sin = 0;
   cos = cordic_gain_c;
   cordic_circular_zmode(&cos, &sin, &a);
   output = ANGLDIVD(sin, cos);
   output = ANGL2SCLR(output);

   return output;
}

EngSclr
engineer_math_atan(EngAngl a)
{
   // Domain: all a
   EngSclr output;
   Word x, z;

   x = ANGLBASE;
   z = 0;
   cordic_circular_ymode(&x, &a, &z);
   output = ANGL2SCLR(z);

   return output;
}

EngSclr
engineer_math_asin(EngAngl a) // Fixme //
{
   // Domain: |a| < 0.98
   // We use the trig identity for this, as there really isnt a good way to vectorize it directly.
   EngSclr output;

   //output = ANGL2SCLR(ATAN(DIVD(a, SQRT(1 - MULT(a, a)))));

   Word x, z;

   x = cordic_gain_c;
   z = 0;
   cordic_circular_aymode(&x, &a, &z);
   output = ANGL2SCLR(z);

   return output;
}


/*** Hyperbolic Functions ***/

EngVec2
engineer_math_sincosh(EngAngl a)
{
   // Domain: |a| < 1.13 OR |a| <= 1.125, after scaling,
   EngVec2 output;
   Word cosh, sinh;

   sinh  = 0;
   cosh  = cordic_gain_h;
   cordic_hyperbolic_zmode(&cosh, &sinh, &a);
   output.x = cosh;
   output.y = sinh;

   return output;
}

EngSclr
engineer_math_tanh(EngAngl a)
{
   // Domain: |a| < 1.13 units.
   EngSclr output;
   Word sinh, cosh;

   cosh = cordic_gain_h;
   sinh = 0;
   cordic_hyperbolic_zmode(&cosh, &sinh, &a);
   output = ANGLDIVD(sinh, cosh);

   return output;
}

EngSclr
engineer_math_atanh(EngAngl a)
{
   // Domain: |a| < 1.13 units.
   EngSclr output;
   Word x, z;

   x = ANGLBASE;
   z = 0;
   cordic_hyperbolic_ymode(&x, &a, &z);
   output = z;

   return output;
}


/*** Vector Algebra Functions ***/

EngVec2
engineer_math_vec2(EngSclr xinput, EngSclr yinput)
{
   EngVec2 output;

   output.x = xinput;
   output.y = yinput;

   return output;
}

EngSclr
engineer_math_vec2_dot(EngVec2 *va, EngVec2 *vb)
{
   EngSclr output;

   output = MULT(va->x, vb->x) + MULT(va->y, vb->y);

   return output;
}

EngVec2
engineer_math_vec2_normalize(EngVec2 *v)
{
   EngVec2 output;
   EngSclr square, inverse;

   square   = MULT(v->x, v->x) + MULT(v->y, v->y);
   inverse  = DIVD(SCLRBASE, SQRT(square));
   output.x = MULT(v->x, inverse);
   output.y = MULT(v->y, inverse);

   return output;
}

EngVec3
engineer_math_vec3(EngSclr xinput, EngSclr yinput, EngSclr zinput)
{
   EngVec3 output;

   output.x = xinput;
   output.y = yinput;
   output.z = zinput;

   return output;
}

EngSclr
engineer_math_vec3_dot(EngVec3 *va, EngVec3 *vb)
{
   EngSclr output;

   output = MULT(va->x, vb->x) + MULT(va->y, vb->y) + MULT(va->z, vb->z);

   return output;
}

EngVec3
engineer_math_vec3_cross(EngVec3 *va, EngVec3 *vb)
{
   EngVec3 output;

   output.x = MULT(va->y, vb->z) - MULT(va->z, vb->y);
   output.y = MULT(va->z, vb->x) - MULT(va->x, vb->z);
   output.z = MULT(va->x, vb->y) - MULT(va->y, vb->x);

   return output;
}

EngVec3
engineer_math_vec3_normalize(EngVec3 *v)
{
   EngVec3 output;
   EngSclr square, inverse;

   square   = MULT(v->x, v->x) + MULT(v->y, v->y) + MULT(v->z, v->z);
   inverse  = DIVD(SCLRBASE, SQRT(square));
   output.x = MULT(v->x, inverse);
   output.y = MULT(v->y, inverse);
   output.z = MULT(v->z, inverse);

   return output;
}

EngQuat
engineer_math_quat(EngSclr winput, EngSclr xinput, EngSclr yinput, EngSclr zinput)
{
   EngQuat output;

   output.w = winput;
   output.x = xinput;
   output.y = yinput;
   output.z = zinput;

   return output;
}

EngQuat
engineer_math_quat_multiply(EngQuat *q1, EngQuat *q2)
{
   EngQuat output;

   output.w = MULT(q1->w, q2->w) - MULT(q1->x, q2->x) - MULT(q1->y, q2->y) - MULT(q1->z, q2->z);
   output.x = MULT(q1->w, q2->x) + MULT(q1->x, q2->w) + MULT(q1->y, q2->z) - MULT(q1->z, q2->y);
   output.y = MULT(q1->w, q2->y) + MULT(q1->y, q2->w) + MULT(q1->z, q2->x) - MULT(q1->x, q2->z); // x<>z Switched!
   output.z = MULT(q1->w, q2->z) + MULT(q1->z, q2->w) + MULT(q1->x, q2->y) - MULT(q1->y, q2->x);

   return output;
}

EngMtrx
engineer_math_quat_matrixify(EngQuat *q)
{
   EngMtrx output;

   // Helper quantities, we calculate these up front to avoid redundancies.
   EngSclr wSq  = MULT(q->w, q->w);
   EngSclr xSq  = MULT(q->x, q->x), ySq = MULT(q->y, q->y), zSq = MULT(q->z, q->z);
   EngSclr twoW = MULT(q->w, SCLRBASE << 1);
   EngSclr twoX = MULT(q->x, SCLRBASE << 1), twoY = MULT(q->y, SCLRBASE << 1);
   EngSclr xy   = MULT(twoX, q->y), xz = MULT(twoX, q->z), yz = MULT(twoY, q->z);
   EngSclr wx   = MULT(twoW, q->x), wy = MULT(twoW, q->y), wz = MULT(twoW, q->z);

   // Fill in the first row.
   output.cell00 = wSq + xSq - ySq - zSq;
   output.cell01 = xy  - wz;
   output.cell02 = xz  + wy;
   // Fill in the second row.
   output.cell10 = xy  + wz;
   output.cell11 = wSq - xSq + ySq - zSq;
   output.cell12 = yz  - wx;
   // Fill in the third row.
   output.cell20 = xz  - wy;
   output.cell21 = yz  + wx;
   output.cell22 = wSq - xSq - ySq + zSq;

   return output;
}

EngQuat
engineer_math_quat_normalize(EngQuat *q)
{
   EngQuat output;
   EngSclr square, inverse;

   square   = MULT(q->x, q->x) + MULT(q->y, q->y) + MULT(q->z, q->z) + MULT(q->w, q->w);
   inverse  = DIVD(SCLRBASE, SQRT(square));
   output.x = MULT(q->x, inverse);
   output.y = MULT(q->y, inverse);
   output.z = MULT(q->z, inverse);
   output.w = MULT(q->w, inverse);

   //detect badness
   //assert(square > 0.1f);

   return output;
}

