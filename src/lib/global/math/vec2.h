#ifndef _ENGINEER_MATH_VEC2_H_
#define _ENGINEER_MATH_VEC2_H_

#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/vec2.h"
#include "../math/sclr.h"

#define VEC2DOT(a, b)    engineer_math_vec2_dot(a, b)
#define VEC2NORM(a)      engineer_math_vec2_normalize(a)

SclrBuffer engineer_math_vec2_dot(Vec2 *va, Vec2 *vb);
Vec2Buffer engineer_math_vec2_normalize(Vec2 *v);

#endif

