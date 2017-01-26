#ifndef _ENGINEER_MATH_QUAT_H_
#define _ENGINEER_MATH_QUAT_H_

//#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/quat.h"
#include "../math/sclr.h"
#include "../math/mtrx.h"

QuatBuffer engineer_math_quat_multiply(Quat *q1, Quat *q2);
MtrxBuffer engineer_math_quat_matrixify(Quat *q);
QuatBuffer engineer_math_quat_normalize(Quat *q);

#endif

