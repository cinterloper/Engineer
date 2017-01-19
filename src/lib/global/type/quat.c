#include "quat.h"

typedef Eina_Inarray Inarray;

/*** Quaternion Type Management ***/

Quat *
engineer_type_Quat_soa_new()
{
   Quat *output = malloc(sizeof(Quat));

   output->w = (Angl*)eina_inarray_new(sizeof(Angl), 0);
   output->x = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->y = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->z = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);

   return output;
}

uint
engineer_type_Quat_soa_push(Quat *target, Quat *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target->w, input->w);
   output = eina_inarray_push((Inarray*)target->x, input->x);
   output = eina_inarray_push((Inarray*)target->y, input->y);
   output = eina_inarray_push((Inarray*)target->z, input->z);

   return output;
}

void
engineer_type_Quat_soa_nth(Quat *target, uint index, Quat *output)
{
   output->w = eina_inarray_nth((Inarray*)target->w, index);
   output->x = eina_inarray_nth((Inarray*)target->x, index);
   output->y = eina_inarray_nth((Inarray*)target->y, index);
   output->z = eina_inarray_nth((Inarray*)target->z, index);
}

void
engineer_type_Quat_soa_replace_at(Quat *target, uint index, Quat *input)
{
   eina_inarray_replace_at((Inarray*)target->w, index, input->w);
   eina_inarray_replace_at((Inarray*)target->x, index, input->x);
   eina_inarray_replace_at((Inarray*)target->y, index, input->y);
   eina_inarray_replace_at((Inarray*)target->z, index, input->z);
}

void
engineer_type_Quat_soa_remove_at(Quat *target, uint index)
{
   eina_inarray_remove_at((Inarray*)target->z, index);
   eina_inarray_remove_at((Inarray*)target->y, index);
   eina_inarray_remove_at((Inarray*)target->x, index);
   eina_inarray_remove_at((Inarray*)target->w, index);
}

void
engineer_type_Quat_soa_free(Quat *target)
{
   eina_inarray_free((Inarray*)target->z);
   eina_inarray_free((Inarray*)target->y);
   eina_inarray_free((Inarray*)target->x);
   eina_inarray_free((Inarray*)target->w);

   free(target);
}

Quat *
engineer_type_Quat_handle_alloc()
{
   Quat *output;

   output    = malloc(sizeof(Quat));
   output->w = 0;
   output->x = 0;
   output->y = 0;
   output->z = 0;

   return output;
}

void
engineer_type_Quat_handle_free(Quat *target)
{
   free(target);
}

