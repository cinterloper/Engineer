#ifndef _ENGINEER_MATH_QUAT_H_
#define _ENGINEER_MATH_QUAT_H_

#define SWITCH

#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/quat.h"
#include "sclr.h"

Quat engineer_math_quat_multiply(Quat multiplicand, Quat multiplier);
Quat engineer_math_quat_normalize(Quat input);

#endif

