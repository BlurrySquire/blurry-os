#ifndef _H_TYPES_DEF
#define _H_TYPES_DEF

#ifdef __cplusplus
extern "C" {
#endif

typedef signed long     ptrdiff_t;

#define PTRDIFF_MIN     (-9223372036854775808)

#define PTRDIFF_MAX     (9223372036854775807)

#define NULL ((void*)0)

#define offsetof(type, member) __builtin_offsetof(type, member)

#ifdef __cplusplus
}
#endif

#endif