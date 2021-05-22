#ifndef GXM_GXM_H
#define GXM_GXM_H

#include <cstdint>

namespace gxm {

struct version {
    static const uint8_t major = 1;
    static const uint8_t minor = 0;
    static const uint8_t patch = 0;
};

} // namespace gxm

#include <gxm/main/app.h>

#endif