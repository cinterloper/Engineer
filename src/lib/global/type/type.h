#ifndef TYPE
   #include "sclr.h"
   #define TYPE Vec2
#endif

#ifndef SUBTYPES
   #define SUBTYPES FIELD(x, Sclr) FIELD(y, Sclr)
#endif

#define FIELD(key, type) type key;
#define DEFINE(type) \
   typedef struct \
   { \
      SUBTYPES \
   } \
   type;
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD

#define SUBSTRUCT(type) type##SOA

#define FIELD(key, type) type##SOA key;
#define DEFINE(type) \
   typedef struct \
   { \
      SUBTYPES \
   } \
   SUBSTRUCT(type);
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD


#define SYMBOL(type) type##SIZE
#define FIELD(key, type) type##SIZE(counter);
#define DEFINE(type) \
   inline void SYMBOL(type)(uint64_t *counter) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) type##NEW
#define FIELD(subkey, type) type##NEW(&key->subkey);
#define DEFINE(type) \
   inline void SYMBOL(type)(SUBSTRUCT(type) *key) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) type##FREE
#define FIELD(subkey, type) type##FREE(&key->subkey);
#define DEFINE(type) \
   inline void SYMBOL(type)(SUBSTRUCT(type) *key) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) type##PUSH
#define FIELD(subkey, type) type##PUSH(&key->subkey, &input->subkey);
#define DEFINE(type) \
   inline void SYMBOL(type)(SUBSTRUCT(type) *key, type *input) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) type##POP
#define FIELD(subkey, type) type##POP(&key->subkey);
#define DEFINE(type) \
   inline void SYMBOL(type)(SUBSTRUCT(type) *key) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) type##READ
#define FIELD(subkey, type) type##READ(&key->subkey, &buffer->subkey, index);
#define DEFINE(type) \
   inline void SYMBOL(type)(SUBSTRUCT(type) *key, type *buffer, uint64_t index) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) type##WRITE
#define FIELD(subkey, type) type##WRITE(&key->subkey, &buffer->subkey, index);
#define DEFINE(type) \
   inline void SYMBOL(type)(SUBSTRUCT(type) *key, type *buffer, uint64_t index) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) type##COPY
#define FIELD(subkey, type) type##COPY(&key->subkey, &target->subkey, index);
#define DEFINE(type) \
   inline void SYMBOL(type)(SUBSTRUCT(type) *key, SUBSTRUCT(type) *target, uint64_t index) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#undef SUBSTRUCT
#undef SUBTYPES
#undef TYPE
