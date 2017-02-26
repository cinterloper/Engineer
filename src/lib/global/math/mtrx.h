#ifndef _ENGINEER_MATH_MTRX_H_
#define _ENGINEER_MATH_MTRX_H_

#define SWITCH

#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/mtrx.h"
#include "quat.h"

Quat engineer_math_mtrx_mult_by_quat(Mtrx multiplicand, Quat multiplier);
Mtrx engineer_math_mtrx_rotation_setup(Quat input);

#endif

