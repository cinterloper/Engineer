#include "vec2.h"

typedef Eina_Inarray Inarray;

/*** 2D Vector Type Management ***/

Vec2 *
engineer_type_Vec2_soa_new()
{
   Vec2 *output = malloc(sizeof(Vec2));

   output->x = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->y = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);

   return output;
}

uint
engineer_type_Vec2_soa_push(Vec2 *target, Vec2 *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target->x, input->x);
   output = eina_inarray_push((Inarray*)target->y, input->y);

   return output;
}

void
engineer_type_Vec2_soa_nth(Vec2 *target, uint index, Vec2 *output)
{
   output->x = eina_inarray_nth((Inarray*)target->x, index);
   output->y = eina_inarray_nth((Inarray*)target->y, index);
}

void
engineer_type_Vec2_soa_replace_at(Vec2 *target, uint index, Vec2 *input)
{
   eina_inarray_replace_at((Inarray*)target->x, index, input->x);
   eina_inarray_replace_at((Inarray*)target->y, index, input->y);
}

void
engineer_type_Vec2_soa_remove_at(Vec2 *target, uint index)
{
   eina_inarray_remove_at((Inarray*)target->y, index);
   eina_inarray_remove_at((Inarray*)target->x, index);
}

void
engineer_type_Vec2_soa_free(Vec2 *target)
{
   eina_inarray_free((Inarray*)target->y);
   eina_inarray_free((Inarray*)target->x);

   free(target);
}

Vec2 *
engineer_type_Vec2_handle_alloc()
{
   Vec2 *output = malloc(sizeof(Vec2));

   output->x = NULL;
   output->y = NULL;

   return output;
}

void
engineer_type_Vec2_handle_free(Vec2 *target)
{
   free(target);
}

