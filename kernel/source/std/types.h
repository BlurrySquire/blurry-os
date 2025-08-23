#ifndef _H_STD_TYPES
#define _H_STD_TYPES

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
typedef unsigned char bool;

#define true 1
#define false 0
#endif

#define NULL ((void*)0)

#define offsetof(type, member) __builtin_offsetof(type, member)

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long int64_t;

#define INT8_MIN        (-128)
#define INT16_MIN       (-32768)
#define INT32_MIN       (-2147483648)
#define INT64_MIN       (-9223372036854775808)

#define INT8_MAX        (127)
#define INT16_MAX       (32767)
#define INT32_MAX       (2147483647)
#define INT64_MAX       (9223372036854775807)

typedef int64_t intptr_t;

#define INTPTR_MIN      INT64_MIN
#define INTPTR_MAX      INT64_MAX

typedef int64_t ptrdiff_t;

#define PTRDIFF_MIN     (-9223372036854775808)
#define PTRDIFF_MAX     (9223372036854775807)

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

#define UINT8_MAX       (255)
#define UINT16_MAX      (65535)
#define UINT32_MAX      (4294967295)
#define UINT64_MAX      (18446744073709551615)

typedef uint64_t uintptr_t;

#define UINTPTR_MAX     UINT64_MAX

typedef uint64_t size_t;

#define SIZE_MAX        UINT64_MAX

#ifdef __cplusplus
}
#endif

#endif