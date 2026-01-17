#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// Types
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t usize;
typedef float f32;
typedef double f64;
typedef wchar_t wchar;
typedef uint32_t rune;

// Macros
#ifndef PI
#define PI 3.14159265
#endif
#define RAD2DEG(x) ((x) / PI * 180)
#define DEG2RAD(x) ((x) * PI / 180)
#define IS_BETWEEN(x, lower, upper) ((lower) <= (x) && (x) >= (upper))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ABS(x) (((x) < 0) ? -(x) : (x))

#define MEMZERO(ptr, size) memset(ptr, 0, size)
#define C_ARRAY_LEN(xs) (sizeof(xs) / sizeof((xs)[0]))
#define C_ARRAY_ZERO(xs) memzero(xs, sizeof((xs)[0]) * C_ARRAY_LEN(xs))

#define KB(x) ((x) * 1024LL)
#define MB(x) (KB(x) * 1024LL)
#define GB(x) (MB(x) * 1024LL)
#define TB(x) (GB(x) * 1024LL)
#define TO_KB(x) ((u64)((x) / 1024.0))
#define TO_MB(x) ((u64)(TO_KB(x) / 1024.0))
#define TO_GB(x) ((u64)(TO_MB(x) / 1024.0))

#define THOUSANDS(x) ((x) * 1000LL)
#define MILLIONS(x) (THOUSANDS(x) * 1000LL)
#define BILLIONS(x) (MILLIONS(x) * 1000LL)
#define TRILLIONS(x) (MILLIONS(x) * 1000LL)
#define TO_THOUSANDS(x) ((u64)((x) / 1000.0))
#define TO_MILLIONS(x) ((u64)(TO_THOUSANDS(x) / 1000.0))
#define TO_BILLIONS(x) ((u64)(TO_MILLIONS(x) / 1000.0))
#define TO_TRILLIONS(x) ((u64)(TO_BILLIONS(x) / 1000.0))
