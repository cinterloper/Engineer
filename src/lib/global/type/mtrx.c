#include "mtrx.h"

typedef Eina_Inarray Inarray;

/*** 3x3 Matrix Type Management ***/

Mtrx *
engineer_type_Mtrx_soa_new()
{
   Mtrx *output = malloc(sizeof(Mtrx));

   output->r0c0 = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->r0c1 = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->r0c2 = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);

   output->r1c0 = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->r1c1 = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->r1c2 = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);

   output->r2c0 = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->r2c1 = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->r2c2 = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);

   return output;
}

void
engineer_type_Mtrx_soa_nth(Mtrx *target, uint index, Mtrx *output)
{
   output->r0c0 = eina_inarray_nth((Inarray*)target->r0c0, index);
   output->r0c1 = eina_inarray_nth((Inarray*)target->r0c1, index);
   output->r0c2 = eina_inarray_nth((Inarray*)target->r0c2, index);

   output->r1c0 = eina_inarray_nth((Inarray*)target->r1c0, index);
   output->r1c1 = eina_inarray_nth((Inarray*)target->r1c1, index);
   output->r1c2 = eina_inarray_nth((Inarray*)target->r1c2, index);

   output->r2c0 = eina_inarray_nth((Inarray*)target->r2c0, index);
   output->r2c1 = eina_inarray_nth((Inarray*)target->r2c1, index);
   output->r2c2 = eina_inarray_nth((Inarray*)target->r2c2, index);
}

uint
engineer_type_Mtrx_soa_push(Mtrx *target, Mtrx *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target->r0c0, input->r0c0);
   output = eina_inarray_push((Inarray*)target->r0c1, input->r0c1);
   output = eina_inarray_push((Inarray*)target->r0c2, input->r0c2);

   output = eina_inarray_push((Inarray*)target->r1c0, input->r1c0);
   output = eina_inarray_push((Inarray*)target->r1c1, input->r1c1);
   output = eina_inarray_push((Inarray*)target->r1c2, input->r1c2);

   output = eina_inarray_push((Inarray*)target->r2c0, input->r2c0);
   output = eina_inarray_push((Inarray*)target->r2c1, input->r2c1);
   output = eina_inarray_push((Inarray*)target->r2c2, input->r2c2);

   return output;
}

void
engineer_type_Mtrx_soa_replace_at(Mtrx *target, uint index, Mtrx *input)
{
   eina_inarray_replace_at((Inarray*)target->r0c0, index, input->r0c0);
   eina_inarray_replace_at((Inarray*)target->r0c1, index, input->r0c1);
   eina_inarray_replace_at((Inarray*)target->r0c2, index, input->r0c2);

   eina_inarray_replace_at((Inarray*)target->r1c0, index, input->r1c0);
   eina_inarray_replace_at((Inarray*)target->r1c1, index, input->r1c1);
   eina_inarray_replace_at((Inarray*)target->r1c2, index, input->r1c2);

   eina_inarray_replace_at((Inarray*)target->r2c0, index, input->r2c0);
   eina_inarray_replace_at((Inarray*)target->r2c1, index, input->r2c1);
   eina_inarray_replace_at((Inarray*)target->r2c2, index, input->r2c2);
}

void
engineer_type_Mtrx_soa_remove_at(Mtrx *target, uint index)
{
   eina_inarray_remove_at((Inarray*)target->r2c2, index);
   eina_inarray_remove_at((Inarray*)target->r2c1, index);
   eina_inarray_remove_at((Inarray*)target->r2c0, index);

   eina_inarray_remove_at((Inarray*)target->r1c2, index);
   eina_inarray_remove_at((Inarray*)target->r1c1, index);
   eina_inarray_remove_at((Inarray*)target->r1c0, index);

   eina_inarray_remove_at((Inarray*)target->r0c2, index);
   eina_inarray_remove_at((Inarray*)target->r0c1, index);
   eina_inarray_remove_at((Inarray*)target->r0c0, index);
}

void
engineer_type_Mtrx_soa_free(Mtrx *target)
{
   eina_inarray_free((Inarray*)target->r2c2);
   eina_inarray_free((Inarray*)target->r2c1);
   eina_inarray_free((Inarray*)target->r2c0);

   eina_inarray_free((Inarray*)target->r1c2);
   eina_inarray_free((Inarray*)target->r1c1);
   eina_inarray_free((Inarray*)target->r1c0);

   eina_inarray_free((Inarray*)target->r0c2);
   eina_inarray_free((Inarray*)target->r0c1);
   eina_inarray_free((Inarray*)target->r0c0);

   free(target);
}

Mtrx *
engineer_type_Mtrx_handle_alloc()
{
   Mtrx *output;

   output = malloc(sizeof(Mtrx));

   output->r0c0 = 0;
   output->r0c1 = 0;
   output->r0c2 = 0;

   output->r1c0 = 0;
   output->r1c1 = 0;
   output->r1c2 = 0;

   output->r2c0 = 0;
   output->r2c1 = 0;
   output->r2c2 = 0;

   return output;
}

void
engineer_type_Mtrx_handle_free(Mtrx *target)
{
   free(target);
}
