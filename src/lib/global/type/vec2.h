#ifndef _ENGINEER_TYPE_VEC2_H_
#define _ENGINEER_TYPE_VEC2_H_

//#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include "sclr.h"

#define VEC2(a, b)  engineer_type_Vec2_buffer_alloc(a, b)
#define VEC2FREE(a) engineer_type_Vec2_buffer_free(a)

typedef struct
{
   Sclr *x, *y;
}
Vec2;

typedef struct
{
   SclrBuffer x, y;
}
Vec2Buffer;

Vec2* engineer_type_Vec2_soa_new();
uint  engineer_type_Vec2_soa_push(Vec2 *target, Vec2 *input);
void  engineer_type_Vec2_soa_nth(Vec2 *target, uint index, Vec2 *output);
void  engineer_type_Vec2_soa_replace_at(Vec2 *target, uint index, Vec2 *input);
void  engineer_type_Vec2_soa_remove_at(Vec2 *target, uint index);
void  engineer_type_Vec2_soa_free(Vec2 *target);

Vec2* engineer_type_Vec2_handle_alloc();
void  engineer_type_Vec2_handle_free(Vec2 *target);

#endif

