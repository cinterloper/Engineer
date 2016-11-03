#include "engineer_cordic_test_main.h"

int main()
{
   // Let's test the CORDIC library for accuracy.
   long v, x, c;
   EngVec2 ans;
   double outputa, outputb, outputc;

   cordic_init();

   x = (EngSclr)1 << (SCLRMAG - 1); // 0.5
   c = (EngSclr)2 << SCLRMAG;
   v = MULT(x, c);
   outputa = x / ((EngSclr)1 << SCLRMAG);
   outputb = c / ((EngSclr)1 << SCLRMAG);
   outputc = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC MULT(%f, %f) = %f\n", outputa, outputb, outputc);

   x = (EngSclr)1 << SCLRMAG;
   c = (EngSclr)2 << SCLRMAG;
   v = DIVD(x, c);
   outputa = x / ((EngSclr)1 << SCLRMAG);
   outputb = c / ((EngSclr)1 << SCLRMAG);
   outputc = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC DIVD(%f, %f) = %f\n", outputa, outputb, outputc);

   x = (EngAngl)1 << ANGLMAG; // 1.0
   v = ATAN(x);
   outputa = (double)(x / ((EngAngl)1 << ANGLMAG));
   outputb = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC ATAN(%f) = %f\n", outputa, outputb);

   x = (EngAngl)1 << ANGLMAG; // 1.0
   ans = SINCOS(x);
   c = ans.x;
   v = ans.y;
   outputa = x / ((EngAngl)1 << ANGLMAG);
   outputb = c / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC COS(%f) = %f\n", outputa, outputb);
   outputb = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC SIN(%f) = %f\n", outputa, outputb);

   x = (EngAngl)1 << ANGLMAG; // 1.0
   v = TAN(x);
   outputa = x / ((EngAngl)1 << ANGLMAG);
   outputb = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC TAN(%f) = %f\n", outputa, outputb);

   x = (EngAngl)1 << (ANGLMAG - 1); // 0.5
   v = ASIN(x);
   outputa = x / ((EngAngl)1 << ANGLMAG);
   outputb = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC ASIN(%f) = %f\n", outputa, outputb);

   x = (EngAngl)1 << ANGLMAG; // 1.0
   ans = SINCOSH(x);
   c = ans.x;
   v = ans.y;
   outputa = x / ((EngAngl)1 << ANGLMAG);
   outputb = c / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC COSH(%f) = %f\n", outputa, outputb);
   outputb = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC SINH (%f) = %f\n", outputa, outputb);

   x = (EngAngl)1 << ANGLMAG; // 1.0
   v = TANH(x);
   outputa = x / ((EngAngl)1 << ANGLMAG);
   outputb = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC TANH(%f) = %f\n", outputa, outputb);

   x = (EngAngl)1 << (ANGLMAG - 1);
   v = ATANH(x);
   outputa = x / ((EngAngl)1 << ANGLMAG);
   outputb = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC ATANH(%f) = %f\n", outputa, outputb);

   x = MULT(3, ((EngSclr)1 << (SCLRMAG - 2))); // 0.75
   v = LOG(x);
   outputa = x / ((EngSclr)1 << SCLRMAG);
   outputb = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC LOG(%f) = %f\n", outputa, outputb);

   x = (EngSclr)1 << SCLRMAG;
   v = SQRT(x);
   outputa = x / ((EngSclr)1 << SCLRMAG);
   outputb = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC SQRT(%f) = %f\n", outputa, outputb);

   x = (EngSclr)1 << SCLRMAG; // 1.0
   v = EXP(x);
   outputa = x / ((EngSclr)1 << SCLRMAG);
   outputb = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC EXP(%f) = %f\n", outputa, outputb);
   x = (EngSclr)2 << SCLRMAG; // 2.0
   v = EXP(x);
   outputa = x / ((EngSclr)1 << SCLRMAG);
   outputb = v / ((EngSclr)1 << SCLRMAG);
   printf("CORDIC EXP(%f) = %f\n", outputa, outputb);

   return 0;
}
