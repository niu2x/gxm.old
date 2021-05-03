#ifndef GXM_GEOMETRY_H
#define GXM_GEOMETRY_H

namespace gxm {

namespace geometry {

template <class T>
class size_t {
public:
    T width, height;
};
} // namespace geometry

using size     = geometry::size_t<double>;
using int_size = geometry::size_t<int>;

class color {
public:
    float r, g, b, a;

    static constexpr color rgba(float r, float g, float b, float a) {
        return color{r, g, b, a};
    }

    static constexpr color rgb(float r, float g, float b) {
        return color{r, g, b, 1};
    }

    static const color red;
    static const color green;
    static const color blue;
    static const color yellow;
    static const color white;
    static const color black;
};

enum class pixel_format {
    rgba,
    s_rgba,
    rgb,
    s_rgb,
    alpha,
    count,
};

} // namespace gxm

#endif