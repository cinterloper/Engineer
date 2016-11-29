#include "engineer_type.h"

typedef Eina_Inarray Inarray;

Sclr *
engineer_type_Sclr_soa_new()
{
   Sclr *output = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);

   return output;
}

uint
engineer_type_Sclr_soa_push(Sclr *target, SclrData *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target, input);

   return output;
}

void
engineer_type_Sclr_soa_replace_at(Sclr *target, uint index, SclrData *input)
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

Angl *
engineer_type_Angl_soa_new()
{
   Angl *output = (Angl*)eina_inarray_new(sizeof(Angl), 0);

   return output;
}

uint
engineer_type_Angl_soa_push(Angl *target, AnglData *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target, input);

   return output;
}

void
engineer_type_Angl_soa_replace_at(Angl *target, uint index, AnglData *input)
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

Vec2 *
engineer_type_Vec2_soa_new()
{
   Vec2 *output = malloc(sizeof(Vec2));

   output->x = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);
   output->y = (Sclr*)eina_inarray_new(sizeof(Sclr), 0);

   return output;
}

uint
engineer_type_Vec2_soa_push(Vec2 *target, Vec2Data *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target->x, &input->x);
   output = eina_inarray_push((Inarray*)target->y, &input->y);

   return output;
}

void
engineer_type_Vec2_soa_replace_at(Vec2 *target, uint index, Vec2Data *input)
{
   eina_inarray_replace_at((Inarray*)target->x, index, &input->x);
   eina_inarray_replace_at((Inarray*)target->y, index, &input->y);
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
engineer_type_Vec3_soa_push(Vec3 *target, Vec3Data *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target->x, &input->x);
   output = eina_inarray_push((Inarray*)target->y, &input->y);
   output = eina_inarray_push((Inarray*)target->z, &input->z);

   return output;
}

void
engineer_type_Vec3_soa_replace_at(Vec3 *target, uint index, Vec3Data *input)
{
   eina_inarray_replace_at((Inarray*)target->x, index, &input->x);
   eina_inarray_replace_at((Inarray*)target->y, index, &input->y);
   eina_inarray_replace_at((Inarray*)target->z, index, &input->z);
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
engineer_type_Quat_soa_push(Quat *target, QuatData *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target->w, &input->w);
   output = eina_inarray_push((Inarray*)target->x, &input->x);
   output = eina_inarray_push((Inarray*)target->y, &input->y);
   output = eina_inarray_push((Inarray*)target->z, &input->z);

   return output;
}

void
engineer_type_Quat_soa_replace_at(Quat *target, uint index, QuatData *input)
{
   eina_inarray_replace_at((Inarray*)target->w, index, &input->w);
   eina_inarray_replace_at((Inarray*)target->x, index, &input->x);
   eina_inarray_replace_at((Inarray*)target->y, index, &input->y);
   eina_inarray_replace_at((Inarray*)target->z, index, &input->z);
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

uint
engineer_type_Mtrx_soa_push(Mtrx *target, MtrxData *input)
{
   uint output;

   output = eina_inarray_push((Inarray*)target->r0c0, &input->r0c0);
   output = eina_inarray_push((Inarray*)target->r0c1, &input->r0c1);
   output = eina_inarray_push((Inarray*)target->r0c2, &input->r0c2);

   output = eina_inarray_push((Inarray*)target->r1c0, &input->r1c0);
   output = eina_inarray_push((Inarray*)target->r1c1, &input->r1c1);
   output = eina_inarray_push((Inarray*)target->r1c2, &input->r1c2);

   output = eina_inarray_push((Inarray*)target->r2c0, &input->r2c0);
   output = eina_inarray_push((Inarray*)target->r2c1, &input->r2c1);
   output = eina_inarray_push((Inarray*)target->r2c2, &input->r2c2);

   return output;
}

void
engineer_type_Mtrx_soa_replace_at(Mtrx *target, uint index, MtrxData *input)
{
   eina_inarray_replace_at((Inarray*)target->r0c0, index, &input->r0c0);
   eina_inarray_replace_at((Inarray*)target->r0c1, index, &input->r0c1);
   eina_inarray_replace_at((Inarray*)target->r0c2, index, &input->r0c2);

   eina_inarray_replace_at((Inarray*)target->r1c0, index, &input->r1c0);
   eina_inarray_replace_at((Inarray*)target->r1c1, index, &input->r1c1);
   eina_inarray_replace_at((Inarray*)target->r1c2, index, &input->r1c2);

   eina_inarray_replace_at((Inarray*)target->r2c0, index, &input->r2c0);
   eina_inarray_replace_at((Inarray*)target->r2c1, index, &input->r2c1);
   eina_inarray_replace_at((Inarray*)target->r2c2, index, &input->r2c2);
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

