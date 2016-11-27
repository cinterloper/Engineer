#ifndef _ENGINEER_MATH_H_
#define _ENGINEER_MATH_H_

#include <math.h>

// This sets the (signed) Scalar type/bitwidth used by the Engineer.so library.
typedef long Sclr;
typedef Sclr Angl;

#define SCALE (sizeof(Sclr) * 8)

// This sets, from the right, where our radix point will be placed in our Word.
#define RADIX 16
#define BASIS ((Sclr)1 << RADIX)

#define ANGLRADIX 31
#define ANGLBASIS ((Sclr)1 << ANGLRADIX)

#define ANGL2SCLR(a) (a >> (ANGLRADIX - RADIX));
#define SCLR2ANGL(a) (a << (ANGLRADIX - RADIX));

#define UINT_NULL  ~((uint)0)
#define ULONG_NULL ~((ulong)0)

#define PI (Sclr)(3.1415926536897932384626 * BASIS)

#define MULT(a, b)       engineer_math_mult(a, b)
#define DIVD(a, b)       engineer_math_divd(a, b)

#define MULTANGL(a, b)   engineer_math_mult_angl(a, b)
#define DIVDANGL(a, b)   engineer_math_divd_angl(a, b)

#define MULTSBYA(s, a)
#define DIVDSBYA(s, a)

#define MULTABYS(a, s)
#define DIVDABYS(a, s)

#define ABS(a)           engineer_math_abs(a)
#define CLAMP(a, b, c)   engineer_math_clamp(a, b, c)
#define EXP(a)           engineer_math_exp(a)
#define LOG(a)           engineer_math_ln(a)
#define SQRT(a)          engineer_math_sqrt(a)

#define SINCOS(a)        engineer_math_sincos(a)
#define TAN(a)           engineer_math_tan(a)
#define ATAN(a)          engineer_math_atan(a)
#define ASIN(a)          engineer_math_asin(a)

#define SINCOSH(a)       engineer_math_sincosh(a)
#define TANH(a)          engineer_math_tanh(a)
#define ATANH(a)         engineer_math_atanh(a)

#define VEC2(a, b)       engineer_math_vec2(a, b)
#define VEC2DOT(a, b)    engineer_math_vec2_dot(a, b)
#define VEC2NORM(a)      engineer_math_vec2_normalize(a)

#define VEC3(a, b, c)    engineer_math_vec3(a, b, c)
#define VEC3DOT(a, b)    engineer_math_vec3_dot(a, b)
#define VEC3CROSS(a, b)  engineer_math_vec3_cross(a, b)
#define VEC3NORM(a, b)   engineer_math_vec3_normalize(a)

#define QUAT(a, b, c, d) engineer_math_quat(a, b, c, d)
#define QUATMULT(a, b)   engineer_math_quat_multiply(a, b)
#define QUATMTRX(a)      engineer_math_quat_matrixify(a)
#define QUATNORM(a)      engineer_math_quat_normalize(a)

// Define this to perform all multiplications and divisions with the linear CORDIC method.
// Protip: DO NOT DEFINE THIS.  It does NOT output correct vaules.
//#define CORDIC_LINEAR    1


typedef struct
{
   Sclr x, y;
}
Vec2;

typedef struct
{
   Sclr x, y, z;
}
Vec3;

typedef struct
{
   Angl w;
   Sclr x, y, z;
}
Quat;

typedef struct
{
   Sclr r0c0, r0c1, r0c2;
   Sclr r1c0, r1c1, r1c2;
   Sclr r2c0, r2c1, r2c2;
}
Mtrx;


void cordic_init();

void cordic_linear_init();
void cordic_linear_ymode(Sclr *x0, Sclr *y0, Sclr *z0);
void cordic_linear_zmode(Sclr *x0, Sclr *y0, Sclr *z0);

void cordic_circular_init();
void cordic_circular_ymode(Sclr *x0, Sclr *y0, Sclr *z0);
void cordic_circular_aymode(Sclr *x0, Sclr *y0, Sclr *z0);
void cordic_circular_zmode(Sclr *x0, Sclr *y0, Sclr *z0);

void cordic_hyperbolic_init();
void cordic_hyperbolic_ymode(Sclr *x0, Sclr *y0, Sclr *z0);
void cordic_hyperbolic_zmode(Sclr *x0, Sclr *y0, Sclr *z0);


Sclr engineer_math_mult(Sclr a, Sclr b);
Sclr engineer_math_divd(Sclr a, Sclr b);

Angl engineer_math_mult_angl(Angl a, Angl b);
Angl engineer_math_divd_angl(Angl a, Angl b);

Sclr engineer_math_abs(Sclr a);
Sclr engineer_math_clamp(Sclr a, Sclr min, Sclr max);

Sclr engineer_math_exp(Sclr a);
Sclr engineer_math_ln(Sclr a);
Sclr engineer_math_sqrt(Sclr a);


Vec2 engineer_math_sincos(Angl a);
Sclr engineer_math_tan(Angl a);
Sclr engineer_math_atan(Angl a);
Sclr engineer_math_asin(Angl a);

Vec2 engineer_math_sincosh(Angl a);
Sclr engineer_math_tanh(Angl a);
Sclr engineer_math_atanh(Angl a);


Vec2 engineer_math_vec2(Sclr xinput, Sclr yinput);
Sclr engineer_math_vec2_dot(Vec2 *va, Vec2 *vb);
Vec2 engineer_math_vec2_normalize(Vec2 *v);

Vec3 engineer_math_vec3(Sclr xinput, Sclr yinput, Sclr zinput);
Sclr engineer_math_vec3_dot(Vec3 *va, Vec3 *vb);
Vec3 engineer_math_vec3_cross(Vec3 *va, Vec3 *vb);
Vec3 engineer_math_vec3_normalize(Vec3 *v);

Quat engineer_math_quat(Sclr winput, Sclr xinput, Sclr yinput, Sclr zinput);
Quat engineer_math_quat_multiply(Quat *q1, Quat *q2);
Mtrx engineer_math_quat_matrixify(Quat *q);
Quat engineer_math_quat_normalize(Quat *q);

#endif

