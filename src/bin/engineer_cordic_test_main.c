#include "engineer_cordic_test_main.h"

int main()
{
   // Let's test the CORDIC library for accuracy.
   cordic_init();

   cordic_mult_test(1.00, 1.00);
   cordic_mult_test(1.00, -1.00);
   cordic_mult_test(-1.00, 1.00);
   cordic_mult_test(-1.00, -1.00);
   cordic_mult_test(-2.00, -1.00);
   cordic_mult_test(-1.00, -2.00);
   cordic_mult_test(3.00, 2.00);
   cordic_mult_test(-3.00, -2.00);
   cordic_mult_test(-4.00, -2.00);
   cordic_mult_test(-2.00, -4.00);
   cordic_mult_test(-4.00, -8.00);
   cordic_mult_test(2.00, 4.00);
   cordic_mult_test(0.50, 2.00);
   cordic_mult_test(2.00, 0.50);
   cordic_mult_test(4.00, 0.25);
   cordic_mult_test(2.00, 2.00);
   cordic_mult_test(64.00, 2.00);
   cordic_mult_test(128.00, 0.50);
   cordic_mult_test(64.00, 4.00);

   cordic_divd_test(1.00, 1.00);
   cordic_divd_test(2.00, 1.00);
   cordic_divd_test(4.00, 2.00);
   cordic_divd_test(1.00, 2.00);

   cordic_sincos_test(1.00);
   cordic_sincos_test(0.50);
/*
   cordic_tan_test(1.00);
   cordic_tan_test(0.50);

   cordic_atan_test(1.00);
   cordic_atan_test(0.50);

   cordic_asin_test(1.00);
   cordic_asin_test(0.50);

   cordic_sincosh_test(1.00);
   cordic_sincosh_test(0.50);

   cordic_tanh_test(1.00);
   cordic_tanh_test(0.50);

   cordic_atanh_test(1.00);
   cordic_atanh_test(0.50);

   cordic_exp_test(1.00);
   cordic_exp_test(2.00);

   cordic_log_test(1.00);
   cordic_log_test(2.00);

   cordic_sqrt_test(1.00);
   cordic_sqrt_test(4.00);
   cordic_sqrt_test(9.00);
   cordic_sqrt_test(16.00);
*/
   return 0;
}

void
cordic_mult_test(double a, double b)
{
   Word v, x, c;
   double outputa, outputb, outputc;

   x = (Word)(a * SCLRBASE);
   c = (Word)(b * SCLRBASE);
   v = MULT(x, c);
   x = x >> 8;
   c = c >> 8;
   v = v >> 8;
   outputa = (double)x / (SCLRBASE >> 8);
   outputb = (double)c / (SCLRBASE >> 8);
   outputc = (double)v / (SCLRBASE >> 8);
   printf("FX CORDIC MULT(%ld * %ld) = %ld\n", x, c, v);
   printf("FP CORDIC MULT(%f * %f) = %f\n\n", outputa, outputb, outputc);
}

void
cordic_divd_test(double a, double b)
{
   Word v, x, c;
   double outputa, outputb, outputc;

   x = (Word)(a * SCLRBASE);
   c = (Word)(b * SCLRBASE);
   v = DIVD(x, c);
   x = x >> 8;
   c = c >> 8;
   v = v >> 8;
   outputa = (double)x / (SCLRBASE >> 8);
   outputb = (double)c / (SCLRBASE >> 8);
   outputc = (double)v / (SCLRBASE >> 8);
   printf("FX CORDIC DIVD(%ld / %ld) = %ld\n", x, c, v);
   printf("FP CORDIC DIVD(%f / %f) = %f\n\n", outputa, outputb, outputc);
}

void
cordic_sincos_test(double a)
{
   Word v, x, c;
   EngVec2 ans;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   ans = SINCOS(x);
   c = ans.x;
   v = ans.y;
   outputa = (double)x / ANGLBASE;
   outputb = (double)c / ANGLBASE;
   printf("FX CORDIC COS(%ld) = %ld\n", x, c);
   printf("FP CORDIC COS(%f) = %f\n\n", outputa, outputb);
   outputb = (double)v / ANGLBASE;
   printf("FX CORDIC SIN(%ld) = %ld\n", x, v);
   printf("FP CORDIC SIN(%f) = %f\n\n", outputa, outputb);
}

void
cordic_tan_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   v = TAN(x);
   outputa = (double)x / ANGLBASE;
   outputb = (double)v / SCLRBASE;
   printf("CORDIC TAN(%f) = %f\n", outputa, outputb);
}

void
cordic_atan_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   v = ATAN(x);
   outputa = (double)x / ANGLBASE;
   outputb = (double)v / SCLRBASE;
   printf("CORDIC ATAN(%f) = %f\n", outputa, outputb);
}

void
cordic_asin_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   v = ASIN(x);
   outputa = (double)x / ANGLBASE;
   outputb = (double)v / SCLRBASE;
   printf("CORDIC ASIN(%f) = %f\n", outputa, outputb);
}

void
cordic_sincosh_test(double a)
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
   printf("CORDIC COSH(%f) = %f\n", outputa, outputb);
   outputb = (double)v / SCLRBASE;
   printf("CORDIC SINH (%f) = %f\n", outputa, outputb);
}

void
cordic_tanh_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   v = TANH(x);
   outputa = (double)x / ANGLBASE;
   outputb = (double)v / SCLRBASE;
   printf("CORDIC TANH(%f) = %f\n", outputa, outputb);
}

void
cordic_atanh_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ANGLBASE);
   v = ATANH(x);
   outputa = (double)x / ANGLBASE;
   outputb = (double)v / SCLRBASE;
   printf("CORDIC ATANH(%f) = %f\n", outputa, outputb);
}

void
cordic_exp_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * SCLRBASE);
   v = EXP(x);
   outputa = (double)x / SCLRBASE;
   outputb = (double)v / SCLRBASE;
   printf("CORDIC EXP(%f) = %f\n", outputa, outputb);
}

void
cordic_log_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * SCLRBASE);
   v = LOG(x);
   outputa = (double)x / SCLRBASE;
   outputb = (double)v / SCLRBASE;
   printf("CORDIC LOG(%f) = %f\n", outputa, outputb);
}

void
cordic_sqrt_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * SCLRBASE);
   v = SQRT(x);
   outputa = (double)x / SCLRBASE;
   outputb = (double)v / SCLRBASE;
   printf("CORDIC SQRT(%f) = %f\n", outputa, outputb);
}

