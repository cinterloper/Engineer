#include "vec3.h"

typedef Eina_Inarray Inarray;

/*** 3D Vector Type Management ***/

Vec3 *
engineer_type_Vec3_soa_new()
{
   Vec3 *output = malloc(sizeof(Vec3));

   output->x = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->y = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->z = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);

   return output;
}

uint
engineer_type_Vec3_soa_push(Vec3 *target, Vec3 *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target->x, input->x);
   output = eina_inarray_push((Inarray*)target->y, input->y);
   output = eina_inarray_push((Inarray*)target->z, input->z);

   return output;
}

void
engineer_type_Vec3_soa_nth(Vec3 *target, uint index, Vec3 *output)
{
   output->x = eina_inarray_nth((Inarray*)target->x, index);
   output->y = eina_inarray_nth((Inarray*)target->y, index);
   output->z = eina_inarray_nth((Inarray*)target->z, index);
}

void
engineer_type_Vec3_soa_replace_at(Vec3 *target, uint index, Vec3 *input)
{
   eina_inarray_replace_at((Inarray*)target->x, index, input->x);
   eina_inarray_replace_at((Inarray*)target->y, index, input->y);
   eina_inarray_replace_at((Inarray*)target->z, index, input->z);
}

void
engineer_type_Vec3_soa_remove_at(Vec3 *target, uint index)
{
   eina_inarray_remove_at((Inarray*)target->z, index);
   eina_inarray_remove_at((Inarray*)target->y, index);
   eina_inarray_remove_at((Inarray*)target->x, index);
}

void
engineer_type_Vec3_soa_free(Vec3* target)
{
   eina_inarray_free((Inarray*)target->z);
   eina_inarray_free((Inarray*)target->y);
   eina_inarray_free((Inarray*)target->x);

   free(target);
}

Vec3 *
engineer_type_Vec3_handle_alloc()
{
   Vec3 *output;

   output    = malloc(sizeof(Vec3));
   output->x = 0;
   output->y = 0;
   output->z = 0;

   return output;
}

void
engineer_type_Vec3_handle_free(Vec3 *target)
{
   free(target);
}

