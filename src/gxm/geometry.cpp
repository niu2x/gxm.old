#include "geometry.h"

namespace gxm {

#define DEF_COLOR_RGB(name, r, g, b)                                           \
    const color color::name = color::rgb(r, g, b);

DEF_COLOR_RGB(red, 1, 0, 0)
DEF_COLOR_RGB(green, 0, 1, 0)
DEF_COLOR_RGB(blue, 0, 0, 1)
DEF_COLOR_RGB(yellow, 1, 1, 0)
DEF_COLOR_RGB(white, 1, 1, 1)
DEF_COLOR_RGB(black, 0, 0, 0)

} // namespace gxm