#ifdef TYPE
#ifdef SUBTYPES

#include "type.h"

#define SYMBOL(type) extern inline void type##SIZE
#define DEFINE(type) SYMBOL(type)(uint64_t *counter);
DEFINE(TYPE)
#undef DEFINE
#undef SYMBOL

#define SYMBOL(type) extern inline void type##NEW
#define DEFINE(type) SYMBOL(type)(SUBSTRUCT(type) *key);
DEFINE(TYPE)
#undef DEFINE
#undef SYMBOL

#define SYMBOL(type) extern inline void type##FREE
#define DEFINE(type) SYMBOL(type)(SUBSTRUCT(type) *key);
DEFINE(TYPE)
#undef DEFINE
#undef SYMBOL

#define SYMBOL(type) extern inline void type##PUSH
#define DEFINE(type) SYMBOL(type)(SUBSTRUCT(type) *key, type *input);
DEFINE(TYPE)
#undef DEFINE
#undef SYMBOL

#define SYMBOL(type) extern inline void type##POP
#define DEFINE(type) SYMBOL(type)(SUBSTRUCT(type) *key);
DEFINE(TYPE)
#undef DEFINE
#undef SYMBOL

#define SYMBOL(type) extern inline void type##READ
#define DEFINE(type) SYMBOL(type)(SUBSTRUCT(type) *key, type *buffer, uint64_t index);
DEFINE(TYPE)
#undef DEFINE
#undef SYMBOL

#define SYMBOL(type) extern inline void type##WRITE
#define DEFINE(type) SYMBOL(type)(SUBSTRUCT(type) *key, type *buffer, uint64_t index);
DEFINE(TYPE)
#undef DEFINE
#undef SYMBOL

#define SYMBOL(type) extern inline void type##COPY
#define DEFINE(type) SYMBOL(type)(SUBSTRUCT(type) *key, SUBSTRUCT(type) *target, uint64_t index);
DEFINE(TYPE)
#undef DEFINE
#undef SYMBOL

#undef SUBSTRUCT

#undef SUBTYPES
#undef TYPE

#endif
#endif

