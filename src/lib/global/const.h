#ifndef _ENGINEER_GLOBAL_CONSTANTS_H_
#define _ENGINEER_GLOBAL_CONSTANTS_H_

#define STRINGIFY(x)  STRINGIFY2(x)
#define STRINGIFY2(x) #x

// This sets the base word size/data type for all number storage.
//    It should be set equal in size to the native bitwidth of the target CPU arch.
#define BASE int64_t

// This sets the (signed) Scalar type/bitwidth used by the Engineer.so library.
#define SCALE (sizeof(BASE) * 8)

// This sets, from the right, where our radix point will be placed in our Word.
#define RADIX 16
#define BASIS ((BASE)1 << RADIX)

#define ANGLRADIX 31
#define ANGLBASIS ((BASE)1 << ANGLRADIX)

#define ANGL2SCLR(a) (a >> (ANGLRADIX - RADIX));
#define SCLR2ANGL(a) (a << (ANGLRADIX - RADIX));

#define UINT_NULL  ~((uint)0)
#define ULONG_NULL ~((ulong)0)

#define PI (BASE)(3.1415926536897932384626 * BASIS)

#endif

