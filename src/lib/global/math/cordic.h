#ifndef _ENGINEER_MATH_CORDIC_H_
#define _ENGINEER_MATH_CORDIC_H_

#define SWITCH

#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "sclr.h"
#include "angl.h"
#include "vec3.h"

// Define this to perform all multiplications and divisions with the linear CORDIC method.
// Protip: DO NOT DEFINE THIS.  It does NOT output correct vaules.
//#define CORDIC_LINEAR    1

void cordic_init();

void cordic_linear_init();
Vec3 cordic_linear_ymode(Vec3 input);
Vec3 cordic_linear_zmode(Vec3 input);

void cordic_circular_init();
Vec3 cordic_circular_ymode(Vec3 input);
Vec3 cordic_circular_aymode(Vec3 input);
Vec3 cordic_circular_zmode(Vec3 input);

void cordic_hyperbolic_init();
Vec3 cordic_hyperbolic_ymode(Vec3 input);
Vec3 cordic_hyperbolic_zmode(Vec3 input);

#undef SWITCH
#endif

