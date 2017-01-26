#ifndef _ENGINEER_TYPE_SCLR_H_
#define _ENGINEER_TYPE_SCLR_H_

//#define EFL_BETA_API_SUPPORT
#include <Ecore_Getopt.h>
#include "../const.h"

#define SCLR(a)      engineer_type_SclrData_alloc(a)
#define SCLRFREE(a)  engineer_type_SclrData_free(a)

typedef BASE Sclr;
typedef BASE SclrBuffer;

Sclr* engineer_type_Sclr_soa_new();
uint  engineer_type_Sclr_soa_push(Sclr *target, Sclr *input);
void  engineer_type_Sclr_soa_nth(Sclr *target, uint index, Sclr *output);
void  engineer_type_Sclr_soa_replace_at(Sclr *target, uint index, Sclr *input);
void  engineer_type_Sclr_soa_remove_at(Sclr *target, uint index);
void  engineer_type_Sclr_soa_free(Sclr *target);

Sclr* engineer_type_Sclr_handle_alloc();
void  engineer_type_Sclr_handle_free(Sclr *target);

#endif

