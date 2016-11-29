#ifndef _ENGINEER_TYPE_H_
#define _ENGINEER_TYPE_H_

#include <stdlib.h>
#include <Elementary.h>
#define  EFL_BETA_API_SUPPORT

typedef long Sclr;
typedef Sclr SclrData;

typedef Sclr Angl;
typedef Angl AnglData;

typedef struct
{
   Sclr *x, *y;
}
Vec2;

typedef struct
{
   Sclr x, y;
}
Vec2Data;

typedef struct
{
   Sclr *x, *y, *z;
}
Vec3;

typedef struct
{
   Sclr x, y, z;
}
Vec3Data;

typedef struct
{
   Angl *w;
   Sclr *x, *y, *z;
}
Quat;

typedef struct
{
   Angl w;
   Sclr x, y, z;
}
QuatData;

typedef struct
{
   Sclr *r0c0, *r0c1, *r0c2;
   Sclr *r1c0, *r1c1, *r1c2;
   Sclr *r2c0, *r2c1, *r2c2;
}
Mtrx;

typedef struct
{
   Sclr r0c0, r0c1, r0c2;
   Sclr r1c0, r1c1, r1c2;
   Sclr r2c0, r2c1, r2c2;
}
MtrxData;

Sclr* engineer_type_Sclr_soa_new();
uint  engineer_type_Sclr_soa_push(Sclr *target, SclrData *input);
void  engineer_type_Sclr_soa_replace_at(Sclr *target, uint index, SclrData *input);
void  engineer_type_Sclr_soa_remove_at(Sclr *target, uint index);
void  engineer_type_Sclr_soa_free(Sclr *target);

Angl* engineer_type_Angl_soa_new();
uint  engineer_type_Angl_soa_push(Angl *target, AnglData *input);
void  engineer_type_Angl_soa_replace_at(Angl *target, uint index, AnglData *input);
void  engineer_type_Angl_soa_remove_at(Angl *target, uint index);
void  engineer_type_Angl_soa_free(Angl *target);

Vec2* engineer_type_Vec2_soa_new();
uint  engineer_type_Vec2_soa_push(Vec2 *target, Vec2Data *input);
void  engineer_type_Vec2_soa_replace_at(Vec2 *target, uint index, Vec2Data *input);
void  engineer_type_Vec2_soa_remove_at(Vec2 *target, uint index);
void  engineer_type_Vec2_soa_free(Vec2 *target);

Vec3* engineer_type_Vec3_soa_new();
uint  engineer_type_Vec3_soa_push(Vec3 *target, Vec3Data *input);
void  engineer_type_Vec3_soa_replace_at(Vec3 *target, uint index, Vec3Data *input);
void  engineer_type_Vec3_soa_remove_at(Vec3 *target, uint index);
void  engineer_type_Vec3_soa_free(Vec3 *target);

Quat* engineer_type_Quat_soa_new();
uint  engineer_type_Quat_soa_push(Quat *target, QuatData *input);
void  engineer_type_Quat_soa_replace_at(Quat *target, uint index, QuatData *input);
void  engineer_type_Quat_soa_remove_at(Quat *target, uint index);
void  engineer_type_Quat_soa_free(Quat *target);

Mtrx* engineer_type_Mtrx_soa_new();
uint  engineer_type_Mtrx_soa_push(Mtrx *target, MtrxData *input);
void  engineer_type_Mtrx_soa_replace_at(Mtrx *target, uint index, MtrxData *input);
void  engineer_type_Mtrx_soa_remove_at(Mtrx *target, uint index);
void  engineer_type_Mtrx_soa_free(Mtrx *target);

#endif

