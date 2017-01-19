#ifndef _ENGINEER_TYPE_MTRX_H_
#define _ENGINEER_TYPE_MTRX_H_

#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include "sclr.h"
#include "vec3.h"

#define MTRX(r0c0, r0c1, r0c2, r1c0, r1c1, r1c2, r2c0, r2c1, r2c2) \
   engineer_type_MtrxData_alloc(r0c0, r0c1, r0c2, r1c0, r1c1, r1c2, r2c0, r2c1, r2c2)
#define MTRXFREE(a)  engineer_type_MtrxData_free(a)

typedef struct
{
   Sclr *r0c0, *r0c1, *r0c2;
   Sclr *r1c0, *r1c1, *r1c2;
   Sclr *r2c0, *r2c1, *r2c2;
}
Mtrx;

typedef struct
{
   SclrBuffer r0c0, r0c1, r0c2;
   SclrBuffer r1c0, r1c1, r1c2;
   SclrBuffer r2c0, r2c1, r2c2;
}
MtrxBuffer;

Mtrx* engineer_type_Mtrx_soa_new();
uint  engineer_type_Mtrx_soa_push(Mtrx *target, Mtrx *input);
void  engineer_type_Mtrx_soa_nth(Mtrx *target, uint index, Mtrx *output);
void  engineer_type_Mtrx_soa_replace_at(Mtrx *target, uint index, Mtrx *input);
void  engineer_type_Mtrx_soa_remove_at(Mtrx *target, uint index);
void  engineer_type_Mtrx_soa_free(Mtrx *target);

Mtrx* engineer_type_Mtrx_handle_alloc();
void  engineer_type_Mtrx_handle_free(Mtrx *target);

#endif

