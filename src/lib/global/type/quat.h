#ifndef _ENGINEER_TYPE_QUAT_H_
#define _ENGINEER_TYPE_QUAT_H_

#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include "sclr.h"
#include "angl.h"

#define QUAT(w, x, y, z) engineer_type_QuatData_alloc(w, x, y, z)
#define QUATFREE(a)      engineer_type_QuatData_free(a)

typedef struct
{
   Angl *w;
   Sclr *x, *y, *z;
}
Quat;

typedef struct
{
   AnglBuffer w;
   SclrBuffer x, y, z;
}
QuatBuffer;

Quat* engineer_type_Quat_soa_new();
uint  engineer_type_Quat_soa_push(Quat *target, Quat *input);
void  engineer_type_Quat_soa_nth(Quat *target, uint index, Quat *output);
void  engineer_type_Quat_soa_replace_at(Quat *target, uint index, Quat *input);
void  engineer_type_Quat_soa_remove_at(Quat *target, uint index);
void  engineer_type_Quat_soa_free(Quat *target);

Quat* engineer_type_Quat_handle_alloc();
void  engineer_type_Quat_handle_free(Quat *target);

#endif

