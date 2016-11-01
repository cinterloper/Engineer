#ifndef _ENGINEER_MATH_H_
#define _ENGINEER_MATH_H_

#include "Engineer.h"
#include "engineer_module.h"

#define my_pi 3.1415926536897932384626
#define my_k1 0.6072529350088812561694

#define LUT_SIZE 64 // LUT = Lookup Table.  This needs to be set to the size of our integer bitwidth.

// Define this to perform all (non 2^x) multiplications and divisions with the cordic linear method.
#define CORDIC_LINEAR    1

#ifdef CORDIC_LINEAR
#define MULT(a, b)    engineer_math_mul(a, b)
#define DIVD(a, b)    engineer_math_div(a, b)
#else
#define MULT(a, b)    (a) * (b)
#define DIVD(a, b)    (a) / (b)
#endif

#define EXP(a)     engineer_math_exp(a)
#define LOG(a)     engineer_math_ln(a)
#define SQRT(a)    engineer_math_sqrt(a)

#define SINCOS(a)  engineer_math_sincos(a)
#define TAN(a)     engineer_math_tan(a)
#define ATAN(a)    engineer_math_atan(a)
#define ASIN(a)    engineer_math_asin(a)

#define SINCOSH(a) engineer_math_sinhcosh(a)
#define TANH(a)    engineer_math_tanh(a)
#define ATANH(a)   engineer_math_atanh(a)

#define VEC2DOT(a, b)
#define VEC2CROSS(a, b)
#define VEC2NORM(a)

#define VEC3DOT(a, b)
#define VEC3CROSS(a, b)
#define VEC3NORM(a, b)

#define QUATMULT(a, b) engineer_math_quat_multiply(a, b)
#define QUATNORM(a)    engineer_math_quat_normalize(a)
#define QUATMTRX(a)    engineer_math_quat_matrixify(a)

void cordic_init();
void cordic_test();

void cordic_linear_init();
void cordic_linear_ymode();
void cordic_linear_zmode();

void cordic_circular_init();
void cordic_circular_ymode();
void cordic_circular_zmode();

void cordic_hyperbolic_init();
void cordic_hyperbolic_ymode();
void cordic_hyperbolic_zmode();

long engineer_math_mul(long a, long b);
long engineer_math_div(long a, long b);

cordic_ans_t engineer_math_sincos(long a);
long         engineer_math_tan(long a);
long         engineer_math_atan(long a);
long         engineer_math_asin(long a);

cordic_ans_t engineer_math_sincosh(long a);
long         engineer_math_tanh(long a);
long         engineer_math_atanh(long a);

long engineer_math_exp(long a);
long engineer_math_ln(long a);
long engineer_math_sqrt(long a);

#endif

