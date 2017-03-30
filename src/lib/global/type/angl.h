#ifndef _ENGINEER_TYPE_ANGL_H_
#define _ENGINEER_TYPE_ANGL_H_

#include <Ecore_Getopt.h>
#include "../const.h"

typedef BASE Angl;

#define AnglSOA Eina_Inarray*

inline void
AnglSIZE(uint64_t *counter)
{
   *counter += 1;
}

inline void
AnglNEW(Eina_Inarray **key)
{
   *key = eina_inarray_new(sizeof(Angl), 0);
}

inline void
AnglFREE(Eina_Inarray **key)
{
   eina_inarray_free(*key);
}

inline void
AnglPUSH(Eina_Inarray **key, Angl *input)
{
   eina_inarray_push(*key, input);
}

inline void
AnglPOP(Eina_Inarray **key)
{
   eina_inarray_pop(*key);
}

inline void
AnglREAD(Eina_Inarray **key, Angl *bufferkey, uint64_t index)
{
   *bufferkey = *(Angl*)eina_inarray_nth(*key, index);
}

inline void
AnglWRITE(Eina_Inarray **key, Angl *bufferkey, uint64_t index)
{
   eina_inarray_replace_at(*key, index, bufferkey);
}

inline void
AnglCOPY(Eina_Inarray **source, Eina_Inarray **destination, uint64_t index)
{
   eina_inarray_replace_at(*destination, index, eina_inarray_nth(*source, index));
}

#endif

