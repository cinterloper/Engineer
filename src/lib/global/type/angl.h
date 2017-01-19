#ifndef _ENGINEER_TYPE_ANGL_H_
#define _ENGINEER_TYPE_ANGL_H_

#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include "../const.h"
#include "sclr.h"

#define ANGL(a)      engineer_type_AnglData_alloc(a)
#define ANGLFREE(a)  engineer_type_AnglData_free(a)

typedef long Angl;
typedef long AnglBuffer;

Angl* engineer_type_Angl_soa_new();
uint  engineer_type_Angl_soa_push(Angl *target, Angl *input);
void  engineer_type_Angl_soa_nth(Angl *target, uint index, Angl *output);
void  engineer_type_Angl_soa_replace_at(Angl *target, uint index, Angl *input);
void  engineer_type_Angl_soa_remove_at(Angl *target, uint index);
void  engineer_type_Angl_soa_free(Angl *target);

Angl* engineer_type_Angl_handle_alloc();
void  engineer_type_Angl_handle_free(Angl *target);

#endif

