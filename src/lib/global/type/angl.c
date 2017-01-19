#include "angl.h"

typedef Eina_Inarray Inarray;

/*** Angle Type Management ***/

Angl *
engineer_type_Angl_soa_new()
{
   Angl *output = (Angl*)eina_inarray_new(sizeof(Angl), 0);

   return output;
}

uint
engineer_type_Angl_soa_push(Angl *target, Angl *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target, input);

   return output;
}

void
engineer_type_Angl_soa_nth(Angl *target, uint index, Angl *output)
{
   output = eina_inarray_nth((Inarray*)target, index);
}

void
engineer_type_Angl_soa_replace_at(Angl *target, uint index, Angl *input)
{
   eina_inarray_replace_at((Inarray*)target, index, input);
}

void
engineer_type_Angl_soa_remove_at(Angl *target, uint index)
{
   eina_inarray_remove_at((Inarray*)target, index);
}

void
engineer_type_Angl_soa_free(Angl *target)
{
   eina_inarray_free((Inarray*)target);
}

Angl *
engineer_type_Angl_handle_alloc()
{
   Angl *output = malloc(sizeof(Angl));

   *output = 0;

   return output;
}

void
engineer_type_Angl_handle_free(Angl *target)
{
   free(target);
}

