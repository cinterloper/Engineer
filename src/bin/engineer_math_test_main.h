#ifndef _ENGINEER_MATH_TEST_MAIN_H_
#define _ENGINEER_MATH_TEST_MAIN_H_

#include <math.h>
#include "../headers/Engineer.h"

extern Word cordic_gain_c;
extern Word cordic_gain_h;

void
math_mult_test(double a, double b);

void
math_divd_test(double a, double b);

void
math_sincos_test(double a);

void
math_tan_test(double a);

void
math_atan_test(double a);

void
math_asin_test(double a);

void
math_sincosh_test(double a);

void
math_tanh_test(double a);

void
math_atanh_test(double a);

void
math_abs_test(double a);

void
math_exp_test(double a);

void
math_log_test(double a);

void
math_sqrt_test(double a);

#endif
