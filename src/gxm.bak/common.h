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
#include <functional>
#include <type_traits>

#include "exception.h"
#include "geometry.h"
#include "log.h"

namespace gxm {

inline void unused(...) {}

#define GXM_MAP_ENUM(map, v)   map[uint8_t(v)]
#define GXM_OFFSET_OF(st, mem) (&((reinterpret_cast<st *>(0))->mem))

class auto_release {
public:
    auto_release(std::function<void()> delegate)
        : delegate_(delegate) {}
    ~auto_release() {
        delegate_();
    }

private:
    std::function<void()> delegate_;
};

#define GXM_CHECK_GL_ERROR()                                                   \
    do {                                                                       \
        auto e = glGetError();                                                 \
        if (e) {                                                               \
            GXM_LOG_E << __FILE__ << __LINE__ << "opengl error: " << e;        \
        }                                                                      \
    } while (false);

} // namespace gxm

#endif