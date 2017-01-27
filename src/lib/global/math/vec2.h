#ifndef _ENGINEER_MATH_VEC2_H_
#define _ENGINEER_MATH_VEC2_H_

//#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/vec2.h"
#include "../math/sclr.h"

#define VEC2SCLE(a, b)   engineer_math_vec2_scle(a, b)
#define VEC2MULT(a, b)   engineer_math_vec2_mult(a, b)
#define VEC2DIVD(a, b)   engineer_math_vec2_divd(a, b)
#define VEC2DOT(a, b)    engineer_math_vec2_dot(a, b)
#define VEC2NORM(a)      engineer_math_vec2_normalize(a)

Vec2Buffer engineer_math_vec2_scle(Vec2 *v, Sclr *s);
Vec2Buffer engineer_math_vec2_mult(Vec2 *va, Vec2 *vb);
Vec2Buffer engineer_math_vec2_divd(Vec2 *va, Vec2 *vb);
SclrBuffer engineer_math_vec2_dot(Vec2 *va, Vec2 *vb);
Vec2Buffer engineer_math_vec2_normalize(Vec2 *v);

#endif

