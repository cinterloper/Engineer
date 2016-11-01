#include "engineer_math.h"

// Global constants.
const uint scale     = 64; // How many bits our numbers contain.
const uint magnitude = 16; // How many of those bits are fractional.

// Gains
long cordic_gain_c;
long cordic_gain_h;

// LUTs
long cordic_lut_l[scale]; // Linear Lookup Table.
long cordic_lut_c[scale]; // Circular Lookup Table.
long cordic_lut_h[scale]; // Hyperbolic Lookup Table.
long cordic_lut_m[scale]; // Hyperbolic Repeat Mask Lookup Table.

void
cordic_init()
{
   cordic_linear_init();
   cordic_circular_init();
   cordic_hyperbolic_init();
}

void
cordic_test()
{
    // Let's run a few tests.
    long v, x, c, ans;
    float output;

    cordic_init();

    x = 1 << magnitude;
    v = cordic_atan(x);
    printf("atan %d = %d\n", x, v);

    x = 1 << magnitude;
    ans = cordic_sincos(x);
    c = ans.x;
    v = ans.y;
    printf("cos %d = %d\n", x, c);
    printf("sin %d = %d\n", x, v);

    x = 1 << magnitude;
    v = cordic_tan(x);
    printf("tan %d = %d\n", x, v);

    x = 1 << (magnitude - 1);
    v = cordic_asin(x);
    printf("asin %d = %d\n", x, v);

    x = 1 << magnitude;
    ans = cordic_sincosh(x);
    c = ans.x;
    v = ans.y;
    printf("cosh %d = %d\n", x, c);
    printf("sinh %d = %d\n", x, v);

    x = 1 << magnitude;
    v = cordic_tanh(x);
    printf("tanh %d = %d\n", x, v);

    x = 1 << (magnitude - 1);
    v = cordic_atanh(x);
    printf("atanh %d = %d\n", x, v);

    x = 0.8;
    v = cordic_ln(x);
    printf("log %d = %d\n", x, v);

    x = 2 << magnitude;
    v = cordic_sqrt(x);
    printf("sqrt %d = %d\n", x, v);

    x = 1 << magnitude;
    v = cordic_exp(x);
    printf("exp %d = %d\n", x, v);
    x = 2 << magnitude;
    v = cordic_exp(x);
    printf("exp %d = %d\n", x, v);

    x = 1 << (magnitude - 1);
    c = 2;
    v = cordic_mul(x, c);
    printf("mul %d %d = %d\n", x, c, v);

    x = 1 << magnitude;
    c = 2 << magnitude;
    v = cordic_div(x, c);
    printf("div %d %d = %d\n", x, c, v);
}


/*** Linear CORDIC ***/

void
cordic_linear_init()
{
   // Compute our Lookup Table for the linear CORDIC algorithims.
   long t = 1 << magnitude;
   uint i;
   for (i = 0; i < scale; ++i)
   {
      cordic_lut_l[i]  = atan(t);
      t = t >> 1;
   }
}

void
cordic_linear_ymode(long *x0, long *y0, long *z0)
{
   long x  = *x0;
   long y  = *y0;
   long z  = *z0;
   long ds = 0;

   for (uint i = 0; i < scale; i++)
   {
      ds = y >> (scale - 1); // Most Significant Bit

      y  = y - (((x >> i)          ^ ds) - ds);
      z  = z + (((cordic_lut_l[i]) ^ ds) - ds);
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}

void
cordic_linear_zmode(long *x0, long *y0, long *z0)
{
   long x  = *x0;
   long y  = *y0;
   long z  = *z0;
   long ds = 0;

   for (uint i = 0; i < scale; i++)
   {
      ds = z >> (scale - 1); // Most Significant Bit

      y  = y + (((x >> i)          ^ ds) - ds);
      z  = z - (((cordic_lut_l[i]) ^ ds) - ds);
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}


/*** Circular CORDIC ***/

void
cordic_circular_init()
{
   // Compute our Lookup Table for the circular CORDIC computers.
   long t = 1 << magnitude;
   uint i;
   for (i = 0; i < scale; ++i)
   {
      cordic_lut_c[i]  = atan(t);
      t = t >> 1;
   }

   // Calculate circular gain by evaluating cos(0) without inverse gain.
   long x = 1 << magnitude;
   long y = 0;
   long z = 0;
   cordic_circular_zmode(&x, &y, &z);
   cordic_gain_c = (1 << magnitude) / x;
}

void
cordic_circular_ymode(long *x0, long *y0, long *z0)
{
   long x  = *x0; // fixedpoint_get(cordic_fx_1K);
   long y  = *y0;
   long z  = *z0;
   long dx = 0;
   long ds = 0;

   for (uint i = 0; i < scale; i++)
   {
      ds = y >> (scale - 1); // Most Significant Bit

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
cordic_circular_zmode(long *x0, long *y0, long *z0)
{
   long x  = *x0; // fixedpoint_get(cordic_fx_1K);
   long y  = *y0;
   long z  = *z0;
   long dx = 0;
   long ds = 0;

   for (uint i = 0; i < scale; i++)
   {
      ds = z >> (scale - 1); // Most Significant Bit

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
// The `x' iteration has the opposite sign.
// iterations 4, 7, .. 3k+1 are repeated.
// iteration 0 is not performed.

void
cordic_hyperbolic_init()
{
   // Compute our Lookup Table for the hyperbolic CORDIC computers.
   uint t = 1 << magnitude;
   uint i;
   for (i = 0; i < scale; ++i)
   {
      t = t >> 1;
      cordic_lut_h[i] = (long)(log(((1 << magnitude) + t)
                                 / ((1 << magnitude) - t))) >> 1;
   }

   // Set up our usage mask for the cyclical doubled iteration of the hyperbolic cordic.
   t = 3;
   for (i = 0; i < scale; i++)
   {
     if(t)
     {
        cordic_lut_m[i] = 0;
        t--;
     }
     else
     {
        cordic_lut_m[i] = (long)ldexp(1, scale);
        t = 2;
     }
   }

   // Calculate hyperbolic gain.
   long x = 1 << magnitude; // 1.0
   long y = 0;              // 0.0
   long z = 0;              // 0.0
   cordic_hyperbolic_zmode(&x, &y, &z);
   cordic_gain_h = (1 << magnitude) / x;
}

void
cordic_hyperbolic_ymode(long *x0, long *y0, long *z0)
{
   long x = *x0;
   long y = *y0;
   long z = *z0;
   long dx = 0;
   long ds = 0;

   for (uint i = 0; i < scale; i++)
   {
      ds = y >> (scale - 1); // Most Significant Bit

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

   for (uint i = 0; i < scale; i++)
   {
      ds = z >> (scale - 1); // Most Significant Bit

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

EngScalar
engineer_math_mul(EngScalar a, EngScalar b)
{
    long x, y, z;

    x = a;
    y = 0;
    z = b;
    cordic_linear_zmode(&x, &y, &z);

    return y;
}

EngScalar
engineer_math_div(EngScalar a, EngScalar b)
{
    long x, y, z;

    x = b;
    y = a;
    z = 0;
    cordic_linear_ymode(&x, &y, &z);

    return z;
}


/*** Circular Functions ***/

EngVec2
engineer_math_sincos(EngAngle a)
{
   // Domain: |a| < 1.74
   long sinp;
   long cosp;
   EngVec2 ans;

   sinp = 0;
   cosp = cordic_gain_c;
   cordic_circular_zmode(&cosp, &sinp, &a);
   ans.x = cosp;
   ans.y = sinp;

   return ans;
}

EngScalar
engineer_math_tan(EngAngle a)
{
    // Domain: |a| < 1.74
    long sinp;
    long cosp;
    long ans;

    sinp = 0;
    cosp = cordic_gain_c;
    cordic_circular_zmode(&cosp, &sinp, &a);
    ans = DIVD(sinp, cosp);

    return ans;
}

EngScalar
engineer_math_atan(EngAngle a)
{
    // Domain: all a
    long x = 1 << magnitude;
    long z = 0;

    cordic_circular_ymode(&x, &a, &z);

    return z;
}

EngScalar
engineer_math_asin(EngAngle a)
{
    // Domain: |a| < 0.98
    // We use the trig identity for this, as there really isnt a good way to vectorize it directly.
    return cordic_atan(DIVD(a, SQRT(1 - MULT(a, a))));
}


/*** Hyperbolic Functions ***/

EngVec2
engineer_math_sincosh(EngAngle a)
{
   // Domain: |a| < 1.13 OR |a| <= 1.125, after scaling,
   long y, coshp;
   EngVec2 ans;

   coshp  = cordic_gain_h;
   y      = 0;
   cordic_hyperbolic_zmode(&coshp, &y, &a);

   ans.x = coshp;
   ans.y = y;

   return ans;
}

EngScalar
engineer_math_tanh(EngAngle a)
{
    // Domain: |a| < 1.13 units.
    long sinhp, coshp, ans;

    coshp = cordic_gain_h;
    sinhp = 0;
    cordic_hyperbolic_zmode(&coshp, &sinhp, &a);
    ans = DIVD(sinhp, coshp);

    return ans;
}

EngScalar
engineer_math_atanh(EngAngle a)
{
    // Domain: |a| < 1.13 units.
    long x, z, ans;

    x = 1 << magnitude;
    z = 0;
    cordic_hyperbolic_ymode(&x, &a, &z);
    ans = z;

    return ans;
}

EngScalar
engineer_math_exp(EngScalar a)
{
    long sinhp, coshp, ans;

    coshp = cordic_gain_h;
    sinhp = 0;

    cordic_hyperbolic_zmode(&coshp, &sinhp, &a);
    ans = (sinhp + coshp);

    return ans;
}

EngScalar
engineer_math_ln(EngScalar a)
{
    // Domain: 0.1 < a < 9.58 units.
    long x, y, z, ans;

    x = a + (1 << magnitude);
    y = a - (1 << magnitude);
    z = 0;
    cordic_hyperbolic_ymode(&x, &y, &z);
    ans =  z << 1;

    return ans;
}

EngScalar
engineer_math_sqrt(EngScalar a)
{
    // Domain: 0.03 < a < 2 units.
    long x, y, z, ans;

    x = a + (1 << (magnitude - 2));
    y = a - (1 << (magnitude - 2));
    z = 0;
    cordic_hyperbolic_ymode(&x, &y, &z);
    ans = MULT(x, cordic_gain_h);

    return ans;
}

/*
static void
engineer_math_quat_multiply(const EngQuat& q1, const EngQuat& q2)
{
     Quat quaternion;
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

static EngMatrix
engineer_math_quat_matrixify(const EngQuat &q)
{
     EngMatrix matrix;

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
