#ifndef _ENGINEER_MATH_ANGL_H_
#define _ENGINEER_MATH_ANGL_H_

#define SWITCH

#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/angl.h"
#include "vec2.h"
#include "vec3.h"
#include "cordic.h"

#define ANGLMULT(a, b) engineer_math_angl_mult(a, b)
#define ANGLDIVD(a, b) engineer_math_angl_divd(a, b)

#define SINCOS(a) engineer_math_sincos(a)
#define TAN(a)    engineer_math_tan(a)
#define ATAN(a)   engineer_math_atan(a)
#define ASIN(a)   engineer_math_asin(a)

#define SINCOSH(a) engineer_math_sincosh(a)
#define TANH(a)    engineer_math_tanh(a)
#define ATANH(a)   engineer_math_atanh(a)

Angl engineer_math_angl_mult(Angl multiplicand, Angl multiplier);
Angl engineer_math_angl_divd(Angl dividend,     Angl divisor);

Vec2 engineer_math_sincos(Angl input);
Sclr engineer_math_tan(Angl input);
Sclr engineer_math_atan(Angl input);
Sclr engineer_math_asin(Angl input);

Vec2 engineer_math_sincosh(Angl input);
Sclr engineer_math_tanh(Angl input);
Sclr engineer_math_atanh(Angl input);

#endif

