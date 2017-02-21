#ifndef _ENGINEER_MATH_VEC2_H_
#define _ENGINEER_MATH_VEC2_H_

#define SWITCH

#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/vec2.h"
#include "sclr.h"

//#define VEC2MULT(a, b)   engineer_math_vec2_mult(a, b)
//#define VEC2DIVD(a, b)   engineer_math_vec2_divd(a, b)
#define VEC2SCLE(a, b)   engineer_math_vec2_scale(a, b)
#define VEC2DOT(a, b)    engineer_math_vec2_dot(a, b)
#define VEC2NORM(a)      engineer_math_vec2_normalize(a)

//Vec2 engineer_math_vec2_mult(Vec2 va, Vec2 vb);
//Vec2 engineer_math_vec2_divd(Vec2 va, Vec2 vb);
Vec2 engineer_math_vec2_scale(Vec2 input, Sclr factor);
Sclr engineer_math_vec2_dot(Vec2 inputa, Vec2 inputb);
Vec2 engineer_math_vec2_normalize(Vec2 input);

#endif

