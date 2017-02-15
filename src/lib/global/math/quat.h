#ifndef _ENGINEER_MATH_QUAT_H_
#define _ENGINEER_MATH_QUAT_H_

#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/quat.h"
#include "../type/mtrx.h"
#include "../math/sclr.h"
//#include "../math/mtrx.h"

Quat engineer_math_quat_multiply(Quat multiplicand, Quat multiplier);
Mtrx engineer_math_quat_matrixify(Quat input);
Quat engineer_math_quat_normalize(Quat input);

#endif

