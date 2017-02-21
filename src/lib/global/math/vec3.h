#ifndef _ENGINEER_MATH_VEC3_H_
#define _ENGINEER_MATH_VEC3_H_

#define SWITCH

#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/vec3.h"
#include "sclr.h"

#define VEC3SCLE(a, b)   engineer_math_vec_scale(a, b)
#define VEC3DOT(a, b)    engineer_math_vec3_dot(a, b)
#define VEC3CROSS(a, b)  engineer_math_vec3_cross(a, b)
#define VEC3NORM(a, b)   engineer_math_vec3_normalize(a)

Vec3 engineer_math_vec3_scale(Vec3 input, Sclr factor);
Sclr engineer_math_vec3_dot(Vec3 inputa, Vec3 inputb);
Vec3 engineer_math_vec3_cross(Vec3 inputa, Vec3 inputb);
Vec3 engineer_math_vec3_normalize(Vec3 input);

#endif

