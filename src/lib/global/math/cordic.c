#include "cordic.h"

// Gains
Sclr cordic_gain_c;
Sclr cordic_gain_h;

// LUTs
Sclr cordic_lut_c[SCALE]; // Circular Lookup Table.
Sclr cordic_lut_h[SCALE]; // Hyperbolic Lookup Table.
Sclr cordic_lut_m[SCALE]; // Hyperbolic Repeat Mask Lookup Table.

void
cordic_init()
{
   #ifdef CORDIC_LINEAR
   cordic_linear_init();
   #endif
   cordic_circular_init();
   cordic_hyperbolic_init();
}

/*** Linear CORDIC ***/

#ifdef CORDIC_LINEAR
// This is mostly useless, it's included as a simplified example of a working CORDIC.
// For educational purposes only.
Sclr cordic_lut_l[SCALE]; // Linear Lookup Table.

void
cordic_linear_init()
{
   // Compute our Lookup Table for the linear CORDIC algorithims.
   Sclr t = SCLRBASE;
   uint i;
   for (i = 0; i < SCALE; ++i)
   {
      cordic_lut_l[i] = t;
      t = t >> 1;
   }
}

void
cordic_linear_ymode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x  = *x0;
   Sclr y  = *y0;
   Sclr z  = *z0;
   Sclr ds = 0;

   for (uint i = 0; i < SCALE; ++i)
   {
      ds = y >> (SCALE - 1); // Most Significant Bit

      y  = y - (((x >> i)          ^ ds) - ds);
      z  = z + (((cordic_lut_l[i]) ^ ds) - ds);
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}

void
cordic_linear_zmode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x  = *x0;
   Sclr y  = *y0;
   Sclr z  = *z0;
   Sclr ds = 0;

   for (uint i = 0; i < SCALE; ++i)
   {
      ds = z >> (SCALE - 1); // Most Significant Bit

      y  = y + (((x >> i)          ^ ds) - ds);
      z  = z - (((cordic_lut_l[i]) ^ ds) - ds);
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}
#endif


/*** Circular CORDIC ***/

void
cordic_circular_init()
{
   // Compute our Lookup Table for the circular CORDIC computers.
   double t = 1.0;
   unsigned int i;
   for (i = 0; i < SCALE; ++i)
   {
      cordic_lut_c[i] = (Sclr)(atan(t) * ANGLBASIS);
      t /= 2;
   }

   // Calculate circular gain by evaluating cos(0) without inverse gain.
   Sclr x = ANGLBASIS;
   Sclr y = 0;
   Sclr z = 0;
   cordic_circular_zmode(&x, &y, &z);
   y = ANGLBASIS;
   cordic_gain_c = DIVDANGL(&y, &x);
}

void
cordic_circular_ymode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x  = *x0;
   Sclr y  = *y0;
   Sclr z  = *z0;
   Sclr dx = 0;
   Sclr ds = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      ds = y >> (SCALE - 1); // Most Significant Bit

      dx = x + (((y >> i)          ^ ds) - ds);
      y  = y - (((x >> i)          ^ ds) - ds);
      z  = z + (((cordic_lut_c[i]) ^ ds) - ds);

      x  = dx;
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}

void
cordic_circular_aymode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x  = *x0;
   Sclr y  = 0;
   Sclr z  = *z0;
   Sclr ay = *y0;
   Sclr dx = 0;
   Sclr ds = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      ds = (y + ay) >> (SCALE - 1); // Most Significant Bit

      dx = x - (((y >> i)          ^ ds) - ds);
      y  = y + (((x >> i)          ^ ds) - ds);
      z  = z - (((cordic_lut_c[i]) ^ ds) - ds);

      x  = dx;
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}

void
cordic_circular_zmode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x  = *x0;
   Sclr y  = *y0;
   Sclr z  = *z0;
   Sclr dx = 0;
   Sclr ds = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      ds = z >> (SCALE - 1); // Most Significant Bit

      dx = x - (((y >> i)          ^ ds) - ds);
      y  = y + (((x >> i)          ^ ds) - ds);
      z  = z - (((cordic_lut_c[i]) ^ ds) - ds);

      x  = dx;
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}


/*** Hyperbolic CORDIC ***/
// The 'x' iteration has the opposite sign. Iterations 4, 7, .. 3k+1 are repeated.
// Iteration 0 is not performed.

void
cordic_hyperbolic_init() // Fixme //
{
   // Compute our Lookup Table for the hyperbolic CORDIC computers.
   Sclr t = ANGLBASIS;
   unsigned int i;
   for (i = 0; i < SCALE; ++i)
   {
      t = t >> 1;
      cordic_lut_h[i] = (Sclr)(log((ANGLBASIS + t) / (ANGLBASIS - t))) >> 1;
   }

   // Set up our usage mask for the cyclical doubled iteration of the hyperbolic cordic.
   t = 3;
   for (i = 0; i < SCALE; i++)
   {
     if(t)
     {
        cordic_lut_m[i] = 0;
        t--;
     }
     else
     {
        cordic_lut_m[i] = (Sclr)ldexp(1, SCALE);
        t = 2;
     }
   }

   // Calculate hyperbolic gain.
   Sclr x = ANGLBASIS;
   Sclr y = 0;
   Sclr z = 0;
   cordic_hyperbolic_zmode(&x, &y, &z);
   y = ANGLBASIS;
   cordic_gain_h = DIVD(&y, &x);// (ANGLBASE << ANGLMAG)/ x
}

void
cordic_hyperbolic_ymode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x = *x0;
   Sclr y = *y0;
   Sclr z = *z0;
   Sclr dx = 0;
   Sclr ds = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      ds = y >> (SCALE - 1); // Most Significant Bit

      dx = x - (((y >> i)          ^ ds) - ds);
      y  = y - (((x >> i)          ^ ds) - ds);
      z  = z + (((cordic_lut_c[i]) ^ ds) - ds);

      x  = dx;

      dx = x - ((((y >> i)          ^ ds) - ds) & cordic_lut_m[i]);
      y  = y - ((((x >> i)          ^ ds) - ds) & cordic_lut_m[i]);
      z  = z + ((((cordic_lut_c[i]) ^ ds) - ds) & cordic_lut_m[i]);

      x  = dx;
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}

void
cordic_hyperbolic_zmode(Sclr *x0, Sclr *y0, Sclr *z0)
{
   Sclr x = *x0;
   Sclr y = *y0;
   Sclr z = *z0;
   Sclr dx = 0;
   Sclr ds = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      ds = z >> (SCALE - 1); // Most Significant Bit

      dx = x + (((y >> i)          ^ ds) - ds);
      y  = y + (((x >> i)          ^ ds) - ds);
      z  = z - (((cordic_lut_c[i]) ^ ds) - ds);

      x  = dx;

      dx = x + ((((y >> i)          ^ ds) - ds) & cordic_lut_m[i]);
      y  = y + ((((x >> i)          ^ ds) - ds) & cordic_lut_m[i]);
      z  = z - ((((cordic_lut_c[i]) ^ ds) - ds) & cordic_lut_m[i]);

      x  = dx;
   }

   *x0 = x;
   *y0 = y;
   *z0 = z;
}

