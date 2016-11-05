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
   //#ifdef CORDIC_LINEAR
   cordic_linear_init();
   //#endif
   cordic_circular_init();
   cordic_hyperbolic_init();
}

/*** Linear CORDIC ***/

//#ifdef CORDIC_LINEAR
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
//#endif


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
   printf("FX Circular Pre-Gain %ld\n", x);
   printf("FP Circular Pre-Gain: %lf\n\n", (double)x / ANGLBASE);
   Rstr basis = ANGLBASE;
   Rstr invgain = x;

   cordic_gain_c = (basis << ANGLMAG) / invgain;
}

void
cordic_circular_ymode(Word *x0, Word *y0, Word *z0)
{
   Word x  = *x0; // fixedpoint_get(cordic_fx_1K);
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
cordic_circular_zmode(Word *x0, Word *y0, Word *z0)
{
   Word x  = *x0; // fixedpoint_get(cordic_fx_1K);
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
cordic_hyperbolic_init()
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


/*** Linear Functions ***/

EngSclr
engineer_math_mult(EngSclr a, EngSclr b)
{
   #ifndef CORDIC_LINEAR
   EngSclr output = a * b;
   output += ((output & (1 << (SCLRMAG - 1)) ) << 1);
   output >>= SCLRMAG;

   return output;
   #else
   Word x = a;
   Word y = 0;
   Word z = b;
   cordic_linear_zmode(&x, &y, &z);

   return y;
   #endif
}

EngSclr
engineer_math_divd(EngSclr a, EngSclr b)
{
   #ifndef CORDIC_LINEAR
   EngSclr output = (a << SCLRMAG)/ b;

   return output;
   #else
   Word x = b;
   Word y = a;
   Word z = 0;
   cordic_linear_ymode(&x, &y, &z);

   return z;
   #endif
}


/*** Circular Functions ***/

EngVec2
engineer_math_sincos(EngAngl a)
{
   // Domain: |a| < 1.74
   EngVec2 output;
   Word sin, cos;

   sin = 0;
   cos = cordic_gain_c;
   cordic_circular_zmode(&cos, &sin, &a);
   output.x = cos;
   output.y = sin;

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
   Rstr sinout = sin;
   Rstr cosout = cos;

   output = (sinout << ANGLMAG) / cosout;
   //output = DIVD(sin, cos);

   return output;
}

EngSclr
engineer_math_atan(EngAngl a)
{
   // Domain: all a
   EngSclr output;
   Word x, z;

   x = (Word)1 << ANGLMAG;
   z = 0;
   cordic_circular_ymode(&x, &a, &z);
   output = z;

   return output;
}

EngSclr
engineer_math_asin(EngAngl a)
{
   // Domain: |a| < 0.98
   // We use the trig identity for this, as there really isnt a good way to vectorize it directly.
   return ATAN(DIVD(a, SQRT(1 - MULT(a, a))));
}


/*** Hyperbolic Functions ***/

EngVec2
engineer_math_sincosh(EngAngl a)
{
   // Domain: |a| < 1.13 OR |a| <= 1.125, after scaling,
   EngVec2 ans;
   Word coshp, y;

   coshp  = cordic_gain_h;
   y      = 0;
   cordic_hyperbolic_zmode(&coshp, &y, &a);
   ans.x = coshp;
   ans.y = y;

   return ans;
}

EngSclr
engineer_math_tanh(EngAngl a)
{
   // Domain: |a| < 1.13 units.
   EngSclr ans;
   Word sinhp, coshp;

   coshp = cordic_gain_h;
   sinhp = 0;
   cordic_hyperbolic_zmode(&coshp, &sinhp, &a);
   ans = DIVD(sinhp, coshp);

   return ans;
}

EngSclr
engineer_math_atanh(EngAngl a)
{
   // Domain: |a| < 1.13 units.
   EngSclr ans;
   Word x, z;

   x = (EngAngl)1 << ANGLMAG;
   z = 0;
   cordic_hyperbolic_ymode(&x, &a, &z);
   ans = z;

   return ans;
}

EngSclr
engineer_math_exp(EngSclr a)
{
   EngSclr ans;
   Word sinhp, coshp;

   coshp = cordic_gain_h;
   sinhp = 0;
   cordic_hyperbolic_zmode(&coshp, &sinhp, &a);
   ans = (sinhp + coshp);

   return ans;
}

EngSclr
engineer_math_ln(EngSclr a)
{
   // Domain: 0.1 < a < 9.58 units.
   EngSclr ans;
   Word x, y, z;

   x = a + ((Word)1 << SCLRMAG);
   y = a - ((Word)1 << SCLRMAG);
   z = 0;
   cordic_hyperbolic_ymode(&x, &y, &z);
   ans =  z << 1;

   return ans;
}

EngSclr
engineer_math_sqrt(EngSclr a)
{
   // Domain: 0.03 < a < 2 units.
   EngSclr ans;
   Word x, y, z;

   x = a + ((Word)1 << (SCLRMAG - 2));
   y = a - ((Word)1 << (SCLRMAG - 2));
   z = 0;
   cordic_hyperbolic_ymode(&x, &y, &z);
   ans = MULT(x, cordic_gain_h);

   return ans;
}
/*
static void
engineer_math_quat_multiply(const EngQuat& q1, const EngQuat& q2)
{
   EngQuat quaternion;
   quaternion.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
   quaternion.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
   quaternion.y = q1.w*q2.y + q1.y*q2.w + q1.z*q2.x - q1.x*q2.z; // x<>z Switched!
   quaternion.z = q1.w*q2.z + q1.z*q2.w + q1.x*q2.y - q1.y*q2.x;
   return quaternion;
}

static EngQuat
engineer_math_quat_normalize(const Quat& q)
{
   EngQuat quaternion;
   float sq;
   sq  = q.x * q.x;
   sq += q.y * q.y;
   sq += q.z * q.z;
   sq += q.w * q.w;
   //detect badness
   assert(sq > 0.1f);
   float inv = 1.0f / SQRT(sq);
   quaternion.x = q.x * inv;
   quaternion.y = q.y * inv;
   quaternion.z = q.z * inv;
   quaternion.w = q.w * inv;
   return quaternion;
}

static EngMtrx
engineer_math_quat_matrixify(const EngQuat &q)
{
   EngMtrx matrix;

   // Helper quantities, we calculate these up front to avoid redundancies.
   float xSq  = q.x * q.x,  ySq  = q.y * q.y,  zSq  = q.z * q.z,  wSq = q.w * q.w;
   float twoX = 2.0f * q.x, twoY = 2.0f * q.y, twoW = 2.0f * q.w;
   float xy   = twoX * q.y, xz   = twoX * q.z, yz   = twoY * q.z;
   float wx   = twoW * q.x, wy   = twoW * q.y, wz   = twoW * q.z;

   // Fill in the first row.
   matrix.cell00 = wSq + xSq - ySq - zSq;
   matrix.cell01 = xy - wz;
   matrix.cell02 = xz + wy;
   // Fill in the second row.
   matrix.cell10 = xy + wz;
   matrix.cell11 = wSq - xSq + ySq - zSq;
   matrix.cell12 = yz - wx;
   // Fill in the third row.
   matrix.cell20 = xz - wy;
   matrix.cell21 = yz + wx;
   matrix.cell22 = wSq - xSq - ySq + zSq;

   return matrix;
}
*/
