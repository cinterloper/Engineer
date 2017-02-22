#ifndef _ENGINEER_TYPE_H_

#ifdef TYPE
#ifdef SUBTYPES

#define SUBSTRUCT(type) type##SOA

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

#define FIELD(key, type) SUBSTRUCT(type) key;
#define DEFINE(type) \
   typedef struct \
   { \
      SUBTYPES \
   } \
   SUBSTRUCT(type);
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD

#define SYMBOL(type) inline void type##SIZE
#define FIELD(key, type) type##SIZE(counter);
#define DEFINE(type) \
   SYMBOL(type)(uint64_t *counter) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) inline void type##NEW
#define FIELD(subkey, type) type##NEW(&key->subkey);
#define DEFINE(type) \
   SYMBOL(type)(SUBSTRUCT(type) *key) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) inline void type##FREE
#define FIELD(subkey, type) type##FREE(&key->subkey);
#define DEFINE(type) \
   SYMBOL(type)(SUBSTRUCT(type) *key) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) inline void type##PUSH
#define FIELD(subkey, type) type##PUSH(&key->subkey, &input->subkey);
#define DEFINE(type) \
   SYMBOL(type)(SUBSTRUCT(type) *key, type *input) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) inline void type##POP
#define FIELD(subkey, type) type##POP(&key->subkey);
#define DEFINE(type) \
   SYMBOL(type)(SUBSTRUCT(type) *key) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) inline void type##READ
#define FIELD(subkey, type) type##READ(&key->subkey, &buffer->subkey, index);
#define DEFINE(type) \
   SYMBOL(type)(SUBSTRUCT(type) *key, type *buffer, uint64_t index) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) inline void type##WRITE
#define FIELD(subkey, type) type##WRITE(&key->subkey, &buffer->subkey, index);
#define DEFINE(type) \
   SYMBOL(type)(SUBSTRUCT(type) *key, type *buffer, uint64_t index) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#define SYMBOL(type) inline void type##COPY
#define FIELD(subkey, type) type##COPY(&key->subkey, &target->subkey, index);
#define DEFINE(type) \
   SYMBOL(type)(SUBSTRUCT(type) *key, SUBSTRUCT(type) *target, uint64_t index) \
   { \
      SUBTYPES \
   }
   DEFINE(TYPE)
#undef DEFINE
#undef FIELD
#undef SYMBOL

#ifdef SWITCH
   #undef SUBSTRUCT
   #undef SUBTYPES
   #undef TYPE
#else
   #define _ENGINEER_TYPE_H_
#endif

#endif
#endif

#endif

