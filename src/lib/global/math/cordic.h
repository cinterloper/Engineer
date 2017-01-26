#ifndef _ENGINEER_MATH_CORDIC_H_
#define _ENGINEER_MATH_CORDIC_H_

//#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "sclr.h"
#include "angl.h"

// Define this to perform all multiplications and divisions with the linear CORDIC method.
// Protip: DO NOT DEFINE THIS.  It does NOT output correct vaules.
//#define CORDIC_LINEAR    1

void cordic_init();

void cordic_linear_init();
void cordic_linear_ymode(Sclr *x0, Sclr *y0, Sclr *z0);
void cordic_linear_zmode(Sclr *x0, Sclr *y0, Sclr *z0);

void cordic_circular_init();
void cordic_circular_ymode(Sclr *x0, Sclr *y0, Sclr *z0);
void cordic_circular_aymode(Sclr *x0, Sclr *y0, Sclr *z0);
void cordic_circular_zmode(Sclr *x0, Sclr *y0, Sclr *z0);

void cordic_hyperbolic_init();
void cordic_hyperbolic_ymode(Sclr *x0, Sclr *y0, Sclr *z0);
void cordic_hyperbolic_zmode(Sclr *x0, Sclr *y0, Sclr *z0);

#endif

