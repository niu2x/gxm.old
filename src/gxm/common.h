#ifndef GXM_COMMON_H
#define GXM_COMMON_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uchar.h>
#include <wchar.h>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <type_traits>

#include "exception.h"
#include "geometry.h"
#include "log.h"

namespace gxm {

inline void unused(...) {}

#define GXM_MAP_ENUM(map, v)   map[uint8_t(v)]
#define GXM_OFFSET_OF(st, mem) (&((reinterpret_cast<st *>(0))->mem))

} // namespace gxm

#endif