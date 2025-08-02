#ifndef _H_TYPES_DEF
#define _H_TYPES_DEF

typedef unsigned long   size_t;
typedef signed long     ptrdiff_t;

#define PTRDIFF_MIN     (-9223372036854775808)

#define SIZE_MAX        (18446744073709551615)
#define PTRDIFF_MAX     (9223372036854775807)

#define NULL ((void*)0)

#define offsetof(type, member) __builtin_offsetof(type, member)

#endif