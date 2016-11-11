#include "engineer_math_test_main.h"

int main()
{
   // Let's test the engineer_math library for accuracy.
   cordic_init();

   printf("FX Circular Gain: %ld\n", cordic_gain_c);
   printf("FP Circular Gain: %lf\n\n", (double)cordic_gain_c / ANGLBASE);

   printf("FX Hyperbolic Gain: %ld\n", cordic_gain_h);
   printf("FP Hyperbolic Gain: %lf\n\n", (double)cordic_gain_h / ANGLBASE);

   math_mult_test(1.00, 1.00);
   math_mult_test(1.00, -1.00);
   math_mult_test(-1.00, 1.00);
   math_mult_test(-1.00, -1.00);

   math_mult_test(1.00, 2.00);
   math_mult_test(2.00, 1.00);

   math_mult_test(3.00, 2.00);
   math_mult_test(2.00, 3.00);

   math_mult_test(2.00, 0.50);
   math_mult_test(0.50, 2.00);
   math_mult_test(4.00, 0.25);
   math_mult_test(0.25, 4.00);

   math_mult_test(46340.2428, 46340.2428);
   math_mult_test(46340.25, 46340.25);
   math_mult_test(46341.00, 46341.00);
   math_mult_test(46340.25, 46342.00);

   math_mult_test(65536.00, 32767.00);
   math_mult_test(65536.00, 32768.00);
   math_mult_test(65536.00, 32769.00);
   math_mult_test(65536.00, 65536.00);
   math_mult_test(65536.00, 65537.00);

   math_divd_test(1.00, 1.00);
   math_divd_test(1.00, -1.00);
   math_divd_test(-1.00, 1.00);
   math_divd_test(-1.00, -1.00);

   math_divd_test(2.00, 1.00);
   math_divd_test(4.00, 2.00);
   math_divd_test(8.00, 2.00);

   math_divd_test(1.00, 2.00);
   math_divd_test(1.00, 4.00);
   math_divd_test(1.00, 3.00);

   math_abs_test(1.00);
   math_abs_test(-1.00);
   math_abs_test(1024.00);
   math_abs_test(-1024.00);

   math_sqrt_test(1.00);
   math_sqrt_test(4.00);
   math_sqrt_test(9.00);
   math_sqrt_test(16.00);
   math_sqrt_test(81.00);
   math_sqrt_test(0.0625);

   math_sincos_test(1.00);
   math_sincos_test(0.50);

   math_tan_test(1.00);
   math_tan_test(0.50);

   math_atan_test(1.00);
   math_atan_test(0.50);

   math_asin_test(1.00);
   math_asin_test(0.50);
/*
   math_sincosh_test(1.00);
   math_sincosh_test(0.50);

   math_tanh_test(1.00);
   math_tanh_test(0.50);

   math_atanh_test(1.00);
   math_atanh_test(0.50);

   math_exp_test(1.00);
   math_exp_test(2.00);

   math_log_test(1.00);
   math_log_test(2.00);
*/
   return 0;
}

void
math_mult_test(double a, double b)
{
   Word v, x, c;
   double outputa, outputb, outputc;

   x = (Word)(a * SCLRBASE);
   c = (Word)(b * SCLRBASE);
   v = MULT(x, c);
   outputa = (double)x / SCLRBASE;
   outputb = (double)c / SCLRBASE;
   outputc = (double)v / SCLRBASE;
   printf("FX MULT(%ld * %ld) = %ld\n", x, c, v);
   printf("FP MULT(%f * %f) = %f\n\n", outputa, outputb, outputc);
}

void
math_divd_test(double a, double b)
{
   Word v, x, c;
   double outputa, outputb, outputc;

   x = (Word)(a * SCLRBASE);
   c = (Word)(b * SCLRBASE);
   v = DIVD(x, c);
   outputa = (double)x / SCLRBASE;
   outputb = (double)c / SCLRBASE;
   outputc = (double)v / SCLRBASE;
   printf("FX DIVD(%ld / %ld) = %ld\n", x, c, v);
   printf("FP DIVD(%f / %f) = %f\n\n", outputa, outputb, outputc);
}

void
math_sincos_test(double a)
{
   Word v, x, c;
   EngVec2 ans;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   ans = SINCOS(x);
   c = ans.x;
   v = ans.y;
   outputa = (double)x / ANGLBASE;
   outputb = (double)c / SCLRBASE;
   printf("FX COS(%ld) = %ld\n", x, c);
   printf("FP COS(%f) = %f\n\n", outputa, outputb);
   outputb = (double)v / SCLRBASE;
   printf("FX SIN(%ld) = %ld\n", x, v);
   printf("FP SIN(%f) = %f\n\n", outputa, outputb);
}

void
math_tan_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   v = TAN(x);
   outputa = (double)x / ANGLBASE;
   outputb = (double)v / SCLRBASE;
   printf("FX TAN(%ld) = %ld\n", x, v);
   printf("FP TAN(%f) = %f\n\n", outputa, outputb);
}

void
math_atan_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   v = ATAN(x);
   outputa = (double)x / ANGLBASE;
   outputb = (double)v / SCLRBASE;
   printf("FX ATAN(%ld) = %ld\n", x, v);
   printf("FP ATAN(%f) = %f\n\n", outputa, outputb);
}

void
math_asin_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   v = ASIN(x);
   outputa = (double)x / ANGLBASE;
   outputb = (double)v / SCLRBASE;
   printf("FX ASIN(%ld) = %ld\n", x, v);
   printf("FP ASIN(%f) = %f\n\n", outputa, outputb);
}

void
math_sincosh_test(double a)
{
   Word v, x, c;
   EngVec2 ans;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   ans = SINCOSH(x);
   c = ans.x;
   v = ans.y;
   outputa = (double)x / ANGLBASE;
   outputb = (double)c / SCLRBASE;
   printf("COSH(%f) = %f\n", outputa, outputb);
   outputb = (double)v / SCLRBASE;
   printf("SINH (%f) = %f\n", outputa, outputb);
}

void
math_tanh_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   v = TANH(x);
   outputa = (double)x / ANGLBASE;
   outputb = (double)v / SCLRBASE;
   printf("TANH(%f) = %f\n", outputa, outputb);
}

void
math_atanh_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   v = ATANH(x);
   outputa = (double)x / ANGLBASE;
   outputb = (double)v / SCLRBASE;
   printf("ATANH(%f) = %f\n", outputa, outputb);
}

void
math_abs_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * SCLRBASE);
   v = ABS(x);
   outputa = (double)x / SCLRBASE;
   outputb = (double)v / SCLRBASE;
   printf("FX ABS(%ld) = %ld\n", x, v);
   printf("FP ABS(%f) = %f\n\n", outputa, outputb);
}

void
math_exp_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * SCLRBASE);
   v = EXP(x);
   outputa = (double)x / SCLRBASE;
   outputb = (double)v / SCLRBASE;
   printf("EXP(%f) = %f\n", outputa, outputb);
}

void
math_log_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * SCLRBASE);
   v = LOG(x);
   outputa = (double)x / SCLRBASE;
   outputb = (double)v / SCLRBASE;
   printf("LOG(%f) = %f\n", outputa, outputb);
}

void
math_sqrt_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * SCLRBASE);
   v = SQRT(x);
   outputa = (double)x / SCLRBASE;
   outputb = (double)v / SCLRBASE;
   printf("FX SQRT(%ld) = %ld\n", x, v);
   printf("FP SQRT(%f) = %f\n\n", outputa, outputb);
}

