#include "sclr.h"

extern inline Sclr
sclr(double input);

extern inline void
SclrSIZE(uint64_t *counter);

extern inline void
SclrNEW(Eina_Inarray **key);

extern inline void
SclrFREE(Eina_Inarray **key);

extern inline void
SclrPUSH(Eina_Inarray **key, Sclr *input);

extern inline void
SclrPOP(Eina_Inarray **key);

extern inline void
SclrREAD(Eina_Inarray **key, Sclr *bufferkey, uint64_t index);

extern inline void
SclrWRITE(Eina_Inarray **key, Sclr *bufferkey, uint64_t index);

extern inline void
SclrCOPY(Eina_Inarray **source, Eina_Inarray **destination, uint64_t index);

#undef SUBTYPES
#undef TYPE
