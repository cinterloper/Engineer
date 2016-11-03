#ifndef _ENGINEER_MATH_H_
#define _ENGINEER_MATH_H_

#include "Engineer.h"
#include "engineer_module.h"

#define PI 3.1415926536897932384626
#define K1 0.6072529350088812561694

#define SCALE   64 // This needs to be set to the size of our integer bitwidth.
#define ANGLMAG 60 // Angle Magnitude, how many places from the left our unit radix is placed.
#define SCLRMAG 16 // Scalar Magnitude, must ALWAYS be greater than Scalar Magnitude.

// Define this to perform all (non 2^x) multiplications and divisions with the cordic linear method.
#define CORDIC_LINEAR    1

#ifdef CORDIC_LINEAR
#define MULT(a, b)      engineer_math_mul(a, b)
#define DIVD(a, b)      engineer_math_div(a, b)
#else
#define MULT(a, b)      (a) * (b)
#define DIVD(a, b)      (a) / (b)
#endif

#define EXP(a)          engineer_math_exp(a)
#define LOG(a)          engineer_math_ln(a)
#define SQRT(a)         engineer_math_sqrt(a)

#define SINCOS(a)       engineer_math_sincos(a)
#define TAN(a)          engineer_math_tan(a)
#define ATAN(a)         engineer_math_atan(a)
#define ASIN(a)         engineer_math_asin(a)

#define SINCOSH(a)      engineer_math_sincosh(a)
#define TANH(a)         engineer_math_tanh(a)
#define ATANH(a)        engineer_math_atanh(a)

//#define VEC2DOT(a, b)
//#define VEC2CROSS(a, b)
//#define VEC2NORM(a)

//#define VEC3DOT(a, b)
//#define VEC3CROSS(a, b)
//#define VEC3NORM(a, b)

//#define QUATMULT(a, b)  engineer_math_quat_multiply(a, b)
//#define QUATNORM(a)     engineer_math_quat_normalize(a)
//#define QUATMTRX(a)     engineer_math_quat_matrixify(a)

typedef long EngSclr;
typedef long EngAngl;

typedef struct
{
   EngSclr x, y;
}
EngVec2;

typedef struct
{
   EngSclr x, y, z;
}
EngVec3;

typedef struct
{
   EngAngl w;
   EngSclr x, y, z;
}
EngQuat;

typedef struct
{
   EngSclr cell00, cell01, cell02;
   EngSclr cell10, cell11, cell12;
   EngSclr cell20, cell21, cell22;
}
EngMtrx;

void cordic_init();

void cordic_linear_init();
void cordic_linear_ymode();
void cordic_linear_zmode();

void cordic_circular_init();
void cordic_circular_ymode();
void cordic_circular_zmode();

void cordic_hyperbolic_init();
void cordic_hyperbolic_ymode();
void cordic_hyperbolic_zmode();

EngSclr engineer_math_mul(EngSclr a, EngSclr b);
EngSclr engineer_math_div(EngSclr a, EngSclr b);

EngVec2 engineer_math_sincos(EngAngl a);
EngSclr engineer_math_tan(EngAngl a);
EngSclr engineer_math_atan(EngAngl a);
EngSclr engineer_math_asin(EngAngl a);

EngVec2 engineer_math_sincosh(EngAngl a);
EngSclr engineer_math_tanh(EngAngl a);
EngSclr engineer_math_atanh(EngAngl a);

EngSclr engineer_math_exp(EngSclr a);
EngSclr engineer_math_ln(EngSclr a);
EngSclr engineer_math_sqrt(EngSclr a);

#endif

