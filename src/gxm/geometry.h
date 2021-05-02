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

} // namespace gxm

#endif