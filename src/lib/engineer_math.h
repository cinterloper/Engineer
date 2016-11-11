#ifndef _ENGINEER_MATH_H_
#define _ENGINEER_MATH_H_

#include "Engineer.h"

#define PI (Word)(3.1415926536897932384626 * SCLRBASE)

#define SCALE   64 // This needs to be set to the size of our integer bitwidth.
#define ANGLMAG 60 // Angle Magnitude, how many places from the left our unit radix is placed.
#define SCLRMAG 16 // Scalar Magnitude, must ALWAYS be less than Angular Magnitude.

#define ANGLBASE ((Word)1 << ANGLMAG) // These define our Basis Vectors for
#define SCLRBASE ((Word)1 << SCLRMAG) //    fractional conversion.

// Define this to perform all multiplications and divisions with the linear CORDIC method.
// Protip: DO NOT DEFINE THIS.  It does NOT output correct vaules.
//#define CORDIC_LINEAR    1

#define ANGL2SCLR(a)    (a >> (ANGLMAG - SCLRMAG));
#define SCLR2ANGL(a)    (a << (ANGLMAG - SCLRMAG));

#define MULT(a, b)      engineer_math_mult(a, b)
#define DIVD(a, b)      engineer_math_divd(a, b)

#define ABS(a)          engineer_math_abs(a)
#define CLAMP(a, b, c)  engineer_math_clamp(a, b, c)
#define EXP(a)          engineer_math_exp(a)
#define LOG(a)          engineer_math_ln(a)
#define SQRT(a)         engineer_math_sqrt(a)

#define ANGLMULT(a, b)  engineer_math_angl_mult(a, b)
#define ANGLDIVD(a, b)  engineer_math_angl_divd(a, b)

#define SINCOS(a)       engineer_math_sincos(a)
#define TAN(a)          engineer_math_tan(a)
#define ATAN(a)         engineer_math_atan(a)
#define ASIN(a)         engineer_math_asin(a)

#define SINCOSH(a)      engineer_math_sincosh(a)
#define TANH(a)         engineer_math_tanh(a)
#define ATANH(a)        engineer_math_atanh(a)

#define VEC2DOT(a, b)   engineer_math_vec2_dot(a, b)
#define VEC2NORM(a)     engineer_math_vec2_normalize(a)

#define VEC3DOT(a, b)   engineer_math_vec3_dot(a, b)
#define VEC3CROSS(a, b) engineer_math_vec3_cross(a, b)
#define VEC3NORM(a, b)  engineer_math_vec3_normalize(a)

#define QUATMULT(a, b)  engineer_math_quat_multiply(a, b)
#define QUATMTRX(a)     engineer_math_quat_matrixify(a)
#define QUATNORM(a)     engineer_math_quat_normalize(a)

typedef long     Word;    // This sets the word size used by the Engineer.so library.
typedef __int128 Rstr;    // This needs to be a data type twice the size of the Word.
typedef          Word EngSclr; // Both our Scalar and Angular values should have a word
typedef          Word EngAngl; //    size equal to our library word size.

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
void cordic_circular_aymode();
void cordic_circular_zmode();

void cordic_hyperbolic_init();
void cordic_hyperbolic_ymode();
void cordic_hyperbolic_zmode();


EngSclr
engineer_math_mult(EngSclr a, EngSclr b);

EngSclr
engineer_math_divd(EngSclr a, EngSclr b);

EngSclr
engineer_math_abs(EngSclr a);

EngSclr
engineer_math_clamp(EngSclr a, EngSclr min, EngSclr max);

EngSclr
engineer_math_exp(EngSclr a);

EngSclr
engineer_math_ln(EngSclr a);

EngSclr
engineer_math_sqrt(EngSclr a);


EngAngl
engineer_math_angl_mult(EngAngl a, EngAngl b);

EngAngl
engineer_math_angl_divd(EngAngl a, EngAngl b);


EngVec2
engineer_math_sincos(EngAngl a);

EngSclr
engineer_math_tan(EngAngl a);

EngSclr
engineer_math_atan(EngAngl a);

EngSclr
engineer_math_asin(EngAngl a);


EngVec2
engineer_math_sincosh(EngAngl a);

EngSclr
engineer_math_tanh(EngAngl a);

EngSclr
engineer_math_atanh(EngAngl a);


EngSclr
engineer_math_vec2_dot(EngVec2 *va, EngVec2 *vb);

EngVec2
engineer_math_vec2_normalize(EngVec2 *v);


EngSclr
engineer_math_vec3_dot(EngVec3 *va, EngVec3 *vb);

EngVec3
engineer_math_vec3_cross(EngVec3 *va, EngVec3 *vb);

EngVec3
engineer_math_vec3_normalize(EngVec3 *v);


EngQuat
engineer_math_quat_multiply(EngQuat *q1, EngQuat *q2);

EngMtrx
engineer_math_quat_matrixify(EngQuat *q);

EngQuat
engineer_math_quat_normalize(EngQuat *q);

#endif

