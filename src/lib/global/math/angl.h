#ifndef _ENGINEER_MATH_ANGL_H_
#define _ENGINEER_MATH_ANGL_H_

#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/angl.h"
#include "../math/sclr.h"
#include "../math/vec2.h"
#include "../math/cordic.h"

#define MULTANGL(a, b)   engineer_math_mult_angl(a, b)
#define DIVDANGL(a, b)   engineer_math_divd_angl(a, b)

#define SINCOS(a)        engineer_math_sincos(a)
#define TAN(a)           engineer_math_tan(a)
#define ATAN(a)          engineer_math_atan(a)
#define ASIN(a)          engineer_math_asin(a)

#define SINCOSH(a)       engineer_math_sincosh(a)
#define TANH(a)          engineer_math_tanh(a)
#define ATANH(a)         engineer_math_atanh(a)

AnglBuffer engineer_math_mult_angl(Angl *a, Angl *b);
AnglBuffer engineer_math_divd_angl(Angl *a, Angl *b);

Vec2Buffer engineer_math_sincos(Angl *a);
SclrBuffer engineer_math_tan(Angl *a);
SclrBuffer engineer_math_atan(Angl *a);
SclrBuffer engineer_math_asin(Angl *a);

Vec2Buffer engineer_math_sincosh(Angl *a);
SclrBuffer engineer_math_tanh(Angl *a);
SclrBuffer engineer_math_atanh(Angl *a);

#endif

