#ifndef _ENGINEER_MATH_SCLR_H_
#define _ENGINEER_MATH_SCLR_H_

#define SWITCH

#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/sclr.h"
#include "vec3.h"
#include "cordic.h"

#define MULT(a, b)     engineer_math_mult(a, b)
#define DIVD(a, b)     engineer_math_divd(a, b)

#define ABS(a)         engineer_math_abs(a)
#define CLAMP(a, b, c) engineer_math_clamp(a, b, c)
#define EXP(a)         engineer_math_exp(a)
#define LOG(a)         engineer_math_ln(a)
#define SQRT(a)        engineer_math_sqrt(a)

Sclr engineer_math_mult(Sclr multiplicand, Sclr multiplier);
Sclr engineer_math_divd(Sclr dividend,     Sclr divisor);

Sclr engineer_math_abs(Sclr input);
Sclr engineer_math_clamp(Sclr input, Sclr min, Sclr max);

Sclr engineer_math_exp(Sclr input);
Sclr engineer_math_ln(Sclr input);
Sclr engineer_math_sqrt(Sclr input);

#endif

