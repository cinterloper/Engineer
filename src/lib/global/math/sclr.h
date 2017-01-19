#ifndef _ENGINEER_MATH_SCLR_H_
#define _ENGINEER_MATH_SCLR_H_

#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/sclr.h"
#include "../math/cordic.h"

#define MULT(a, b)     engineer_math_mult(a, b)
#define DIVD(a, b)     engineer_math_divd(a, b)
/*
#define MULTSBYA(s, a)
#define DIVDSBYA(s, a)

#define MULTABYS(a, s)
#define DIVDABYS(a, s)
*/
#define ABS(a)         engineer_math_abs(a)
#define CLAMP(a, b, c) engineer_math_clamp(a, b, c)
#define EXP(a)         engineer_math_exp(a)
#define LOG(a)         engineer_math_ln(a)
#define SQRT(a)        engineer_math_sqrt(a)

SclrBuffer engineer_math_mult(Sclr *a, Sclr *b);
SclrBuffer engineer_math_divd(Sclr *a, Sclr *b);

SclrBuffer engineer_math_abs(Sclr *a);
SclrBuffer engineer_math_clamp(Sclr *a, Sclr *min, Sclr *max);

SclrBuffer engineer_math_exp(Sclr *a);
SclrBuffer engineer_math_ln(Sclr *a);
SclrBuffer engineer_math_sqrt(Sclr *a);

#endif

