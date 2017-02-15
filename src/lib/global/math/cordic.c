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
   Vec3 gain;
   gain.x = ANGLBASIS;
   gain.y = 0;
   gain.z = 0;
   gain   = cordic_circular_zmode(gain);
   gain.y = ANGLBASIS;
   cordic_gain_c = ANGLDIVD(gain.y, gain.x);
}

Vec3
cordic_circular_ymode(Vec3 input)
{
   Sclr mask = 0;
   Sclr xbuf = 0;

   for (uint32_t i = 0; i < SCALE; i++)
   {
      mask    = input.y >> (SCALE - 1);                       // Most Significant Bit.
      xbuf    = input.x + (((input.y >> i)    ^ mask) - mask);
      input.y = input.y - (((input.x >> i)    ^ mask) - mask);
      input.z = input.z + (((cordic_lut_c[i]) ^ mask) - mask);
      input.x = xbuf;
   }

   return input;
}

Vec3
cordic_circular_aymode(Vec3 input)
{
   Sclr mask = 0;
   Sclr xbuf = 0;
   Sclr ybuf = input.y;
   input.y   = 0;

   for (uint32_t i = 0; i < SCALE; i++)
   {
      mask    = (input.y + ybuf) >> (SCALE - 1);              // Most Significant Bit.
      xbuf    = input.x - (((input.y >> i)    ^ mask) - mask);
      input.y = input.y + (((input.x >> i)    ^ mask) - mask);
      input.z = input.z - (((cordic_lut_c[i]) ^ mask) - mask);
      input.x = xbuf;
   }

   return input;
}

Vec3
cordic_circular_zmode(Vec3 input)
{
   Sclr mask = 0;
   Sclr xbuf = 0;


   for (uint32_t i = 0; i < SCALE; i++)
   {
      mask    = input.z >> (SCALE - 1);                       // Most Significant Bit.
      xbuf    = input.x - (((input.y >> i)    ^ mask) - mask);
      input.y = input.y + (((input.x >> i)    ^ mask) - mask);
      input.z = input.z - (((cordic_lut_c[i]) ^ mask) - mask);
      input.x = xbuf;
   }

   return input;
}


/*** Hyperbolic CORDIC ***/
// The 'x' iteration has the opposite sign. Iterations 4, 7, .. 3k+1 are repeated.
// Iteration 0 is not performed.

void
cordic_hyperbolic_init() // Fixme //
{
   Sclr     t;
   uint32_t i;

   // Compute our Lookup Table for the hyperbolic CORDIC computers.
   t = ANGLBASIS;
   for (i = 0; i < SCALE; i++) // ++i?
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
   Vec3 gain;
   gain.x = ANGLBASIS;
   gain.y = 0;
   gain.z = 0;
   gain   = cordic_hyperbolic_zmode(gain);
   gain.y = ANGLBASIS;
   cordic_gain_h = DIVD(gain.y, gain.x);// (ANGLBASE << ANGLMAG)/ x
}

Vec3
cordic_hyperbolic_ymode(Vec3 input)
{
   Sclr mask = 0;
   Sclr xbuf = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      mask    = input.y >> (SCALE - 1);                       // Most Significant Bit
      xbuf    = input.x - (((input.y >> i)    ^ mask) - mask);
      input.y = input.y - (((input.x >> i)    ^ mask) - mask);
      input.z = input.z + (((cordic_lut_c[i]) ^ mask) - mask);
      input.x = xbuf;

      xbuf    = input.x - ((((input.y >> i)    ^ mask) - mask) & cordic_lut_m[i]);
      input.y = input.y - ((((input.x >> i)    ^ mask) - mask) & cordic_lut_m[i]);
      input.z = input.z + ((((cordic_lut_c[i]) ^ mask) - mask) & cordic_lut_m[i]);
      input.x = xbuf;
   }

   return input;
}

Vec3
cordic_hyperbolic_zmode(Vec3 input)
{
   Sclr mask = 0;
   Sclr xbuf = 0;

   for (unsigned int i = 0; i < SCALE; i++)
   {
      mask    = input.z >> (SCALE - 1); // Most Significant Bit
      xbuf    = input.x + (((input.y >> i)    ^ mask) - mask);
      input.y = input.y + (((input.x >> i)    ^ mask) - mask);
      input.z = input.z - (((cordic_lut_c[i]) ^ mask) - mask);
      input.x = xbuf;

      xbuf    = input.x + ((((input.y >> i)    ^ mask) - mask) & cordic_lut_m[i]);
      input.y = input.y + ((((input.x >> i)    ^ mask) - mask) & cordic_lut_m[i]);
      input.z = input.z - ((((cordic_lut_c[i]) ^ mask) - mask) & cordic_lut_m[i]);
      input.x = xbuf;
   }

   return input;
}

