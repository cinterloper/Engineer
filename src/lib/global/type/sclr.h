#ifndef _ENGINEER_TYPE_SCLR_H_
#define _ENGINEER_TYPE_SCLR_H_

#include <Ecore_Getopt.h>
#include "../const.h"

typedef BASE Sclr;

#define SclrSOA Eina_Inarray*

inline void SclrSIZE(uint32_t *counter)
{
   *counter += 1;
}

inline void SclrNEW(Eina_Inarray **key)
{
   *key = eina_inarray_new(sizeof(Sclr), 0);
}

inline void SclrFREE(Eina_Inarray **key)
{
   eina_inarray_free(*key);
}

inline void SclrPUSH(Eina_Inarray **key, Sclr *input)
{
   eina_inarray_push(*key, input);
}

inline void SclrPOP(Eina_Inarray **key)
{
   eina_inarray_pop(*key);
}

inline void SclrREAD(Eina_Inarray **key, Sclr *bufferkey, uint32_t index)
{
   *bufferkey = *(Sclr*)eina_inarray_nth(*key, index);
}

inline void SclrWRITE(Eina_Inarray **key, Sclr *bufferkey, uint32_t index)
{
   eina_inarray_replace_at(*key, index, bufferkey);
}

inline void SclrCOPY(Eina_Inarray **source, Eina_Inarray **destination, uint32_t index)
{
   eina_inarray_replace_at(*source, index, *destination);
}

#endif

