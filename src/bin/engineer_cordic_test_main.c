#include "engineer_cordic_test_main.h"

int main()
{
   // Let's test the CORDIC library for accuracy.
   cordic_init();

   cordic_mult_test(1.00, 1.00);
   cordic_mult_test(1.00, -1.00);
   cordic_mult_test(-1.00, -1.00);
   cordic_mult_test(0.50, 2.00);
   cordic_mult_test(4.00, 0.25);
   cordic_mult_test(2.00, 2.00);

   cordic_divd_test(1.00, 1.00);
   cordic_divd_test(2.00, 1.00);
   cordic_divd_test(4.00, 2.00);
   cordic_divd_test(1.00, 2.00);

   cordic_sincos_test(1.00);
   cordic_sincos_test(0.50);

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

   return 0;
}

void
cordic_mult_test(double a, double b)
{
   Word v, x, c;
   double outputa, outputb, outputc;

   x = (Word)(a * ((Word)1 << SCLRMAG));
   c = (Word)(b * ((Word)1 << SCLRMAG));
   printf("MULT converted inputs %d, %d\n", x, c);
   v = MULT(x, c);
   printf("MULT converted output %d\n", v);
   outputa = (double)x / ((Word)1 << SCLRMAG);
   outputb = (double)c / ((Word)1 << SCLRMAG);
   outputc = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC MULT(%f, %f) = %f\n\n", outputa, outputb, outputc);
}

void
cordic_divd_test(double a, double b)
{
   Word v, x, c;
   double outputa, outputb, outputc;

   x = (Word)(a * ((Word)1 << SCLRMAG));
   c = (Word)(b * ((Word)1 << SCLRMAG));
   v = DIVD(x, c);
   outputa = (double)x / ((Word)1 << SCLRMAG);
   outputb = (double)c / ((Word)1 << SCLRMAG);
   outputc = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC DIVD(%f, %f) = %f\n\n", outputa, outputb, outputc);
}

void
cordic_sincos_test(double a)
{
   Word v, x, c;
   EngVec2 ans;
   double outputa, outputb;

   x = (Word)(a * ((Word)1 << ANGLMAG));
   ans = SINCOS(x);
   c = ans.x;
   v = ans.y;
   outputa = (double)x / ((Word)1 << ANGLMAG);
   outputb = (double)c / ((Word)1 << SCLRMAG);
   printf("CORDIC COS(%f) = %f\n", outputa, outputb);
   outputb = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC SIN(%f) = %f\n", outputa, outputb);
}

void
cordic_tan_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ((Word)1 << ANGLMAG));
   v = TAN(x);
   outputa = (double)x / ((Word)1 << ANGLMAG);
   outputb = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC TAN(%f) = %f\n", outputa, outputb);
}

void
cordic_atan_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ((Word)1 << ANGLMAG));
   v = ATAN(x);
   outputa = (double)x / ((Word)1 << ANGLMAG);
   outputb = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC ATAN(%f) = %f\n", outputa, outputb);
}

void
cordic_asin_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ((Word)1 << ANGLMAG));
   v = ASIN(x);
   outputa = (double)x / ((Word)1 << ANGLMAG);
   outputb = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC ASIN(%f) = %f\n", outputa, outputb);
}

void
cordic_sincosh_test(double a)
{
   Word v, x, c;
   EngVec2 ans;
   double outputa, outputb;

   x = (Word)(a * ((Word)1 << ANGLMAG));
   ans = SINCOSH(x);
   c = ans.x;
   v = ans.y;
   outputa = (double)x / ((Word)1 << ANGLMAG);
   outputb = (double)c / ((Word)1 << SCLRMAG);
   printf("CORDIC COSH(%f) = %f\n", outputa, outputb);
   outputb = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC SINH (%f) = %f\n", outputa, outputb);
}

void
cordic_tanh_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ((Word)1 << ANGLMAG));
   v = TANH(x);
   outputa = (double)x / ((Word)1 << ANGLMAG);
   outputb = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC TANH(%f) = %f\n", outputa, outputb);
}

void
cordic_atanh_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ((Word)1 << ANGLMAG));
   v = ATANH(x);
   outputa = (double)x / ((Word)1 << ANGLMAG);
   outputb = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC ATANH(%f) = %f\n", outputa, outputb);
}

void
cordic_exp_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ((Word)1 << SCLRMAG));
   v = EXP(x);
   outputa = (double)x / ((Word)1 << SCLRMAG);
   outputb = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC EXP(%f) = %f\n", outputa, outputb);
}

void
cordic_log_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ((Word)1 << SCLRMAG));
   v = LOG(x);
   outputa = (double)x / ((Word)1 << SCLRMAG);
   outputb = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC LOG(%f) = %f\n", outputa, outputb);
}

void
cordic_sqrt_test(double a)
{
   Word v, x;
   double outputa, outputb;

   x = (Word)(a * ((Word)1 << SCLRMAG));
   v = SQRT(x);
   outputa = (double)x / ((Word)1 << SCLRMAG);
   outputb = (double)v / ((Word)1 << SCLRMAG);
   printf("CORDIC SQRT(%f) = %f\n", outputa, outputb);
}

