#ifndef _ENGINEER_MATH_VEC3_H_
#define _ENGINEER_MATH_VEC3_H_

#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include <math.h>
#include "../const.h"
#include "../type/vec3.h"
#include "../math/sclr.h"

#define VEC3DOT(a, b)    engineer_math_vec3_dot(a, b)
#define VEC3CROSS(a, b)  engineer_math_vec3_cross(a, b)
#define VEC3NORM(a, b)   engineer_math_vec3_normalize(a)

SclrBuffer engineer_math_vec3_dot(Vec3 *va, Vec3 *vb);
Vec3Buffer engineer_math_vec3_cross(Vec3 *va, Vec3 *vb);
Vec3Buffer engineer_math_vec3_normalize(Vec3 *v);

#endif

