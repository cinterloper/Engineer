#include "sclr.h"

typedef Eina_Inarray Inarray;

/*** Scalar Type Management ***/

Sclr *
engineer_type_Sclr_soa_new()
{
   Sclr *output = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);

   return output;
}

uint
engineer_type_Sclr_soa_push(Sclr *target, Sclr *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target, input);

   return output;
}

void
engineer_type_Sclr_soa_nth(Sclr *target, uint index, Sclr *output)
{
   output = eina_inarray_nth((Inarray*)target, index);
}

void
engineer_type_Sclr_soa_replace_at(Sclr *target, uint index, Sclr *input)
{
   eina_inarray_replace_at((Inarray*)target, index, input);
}

void
engineer_type_Sclr_soa_remove_at(Sclr *target, uint index)
{
   eina_inarray_remove_at((Inarray*)target, index);
}

void
engineer_type_Sclr_soa_free(Sclr *target)
{
   eina_inarray_free((Inarray*)target);
}

Sclr *
engineer_type_Sclr_handle_alloc()
{
   Sclr *output = malloc(sizeof(Sclr));

   *output = 0;

   return output;
}

void
engineer_type_Sclr_handle_free(Sclr *target)
{
   free(target);
}

