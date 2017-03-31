#include "angl.h"

extern inline Angl
angl(double input);

extern inline void
AnglSIZE(uint64_t *counter);

extern inline void
AnglNEW(Eina_Inarray **key);

extern inline void
AnglFREE(Eina_Inarray **key);

extern inline void
AnglPUSH(Eina_Inarray **key, Angl *input);

extern inline void
AnglPOP(Eina_Inarray **key);

extern inline void
AnglREAD(Eina_Inarray **key, Angl *bufferkey, uint64_t index);

extern inline void
AnglWRITE(Eina_Inarray **key, Angl *bufferkey, uint64_t index);

extern inline void
AnglCOPY(Eina_Inarray **source, Eina_Inarray **destination, uint64_t index);

#undef SUBTYPES
#undef TYPE

