/*
american fuzzy lop - type definitions and minor macros
------------------------------------------------------

Written and maintained by Michal Zalewski <lcamtuf@google.com>

Copyright 2013, 2014, 2015 Google Inc. All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at:

http://www.apache.org/licenses/LICENSE-2.0

*/

#ifndef _HAVE_TYPES_H
#define _HAVE_TYPES_H

#include <stdint.h>
#include <stdlib.h>
#include <intrin.h>

typedef char u8;
typedef uint16_t u16;
typedef uint32_t u32;

/*

Ugh. There is an unintended compiler / glibc #include glitch caused by
combining the u64 type an %llu in format strings, necessitating a workaround.

In essence, the compiler is always looking for 'unsigned long long' for %llu.
On 32-bit systems, the u64 type (aliased to uint64_t) is expanded to
'unsigned long long' in <bits/types.h>, so everything checks out.

But on 64-bit systems, it is #ifdef'ed in the same file as 'unsigned long'.
Now, it only happens in circumstances where the type happens to have the
expected bit width, *but* the compiler does not know that... and complains
about 'unsigned long' being unsafe to pass to %llu.

*/

#ifdef _WIN64
typedef unsigned long long u64;
#else
typedef uint64_t u64;
#endif /* _WIN64 */

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

#ifndef MIN
#  define MIN(_a,_b) ((_a) > (_b) ? (_b) : (_a))
#  define MAX(_a,_b) ((_a) > (_b) ? (_a) : (_b))
#endif /* !MIN */

#define SWAP16(x) (((x) >> 8) | ((x) << 8))
#define SWAP32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

#define R(x) (rand() % (x))

#define STRINGIFY_INTERNAL(x) #x
#define STRINGIFY(x) STRINGIFY_INTERNAL(x)

#define MEM_BARRIER() _ReadWriteBarrier(); MemoryBarrier()

#define __builtin_expect(exp, c)  (exp)
#define likely(_x)   __builtin_expect(!!(_x), 1)
#define unlikely(_x)  __builtin_expect(!!(_x), 0)

#endif /* ! _HAVE_TYPES_H */
