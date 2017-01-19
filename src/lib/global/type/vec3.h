#ifndef _ENGINEER_TYPE_VEC3_H_
#define _ENGINEER_TYPE_VEC3_H_

#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include "sclr.h"

#define VEC3(a, b, c) engineer_type_Vec3Data_alloc(a, b, c)
#define VEC3FREE(a)   engineer_type_Vec3Data_free(a)

typedef struct
{
   Sclr *x, *y, *z;
}
Vec3;

typedef struct
{
   SclrBuffer x, y, z;
}
Vec3Buffer;

Vec3* engineer_type_Vec3_soa_new();
uint  engineer_type_Vec3_soa_push(Vec3 *target, Vec3 *input);
void  engineer_type_Vec3_soa_nth(Vec3 *target, uint index, Vec3 *output);
void  engineer_type_Vec3_soa_replace_at(Vec3 *target, uint index, Vec3 *input);
void  engineer_type_Vec3_soa_remove_at(Vec3 *target, uint index);
void  engineer_type_Vec3_soa_free(Vec3 *target);

Vec3* engineer_type_Vec3_handle_alloc();
void  engineer_type_Vec3_handle_free(Vec3 *target);

#endif

