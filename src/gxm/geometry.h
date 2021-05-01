#ifndef GXM_GEOMETRY_H
#define GXM_GEOMETRY_H

namespace gxm {

template <class T>
class size_t {
public:
    T width, height;
};

using size     = size_t<double>;
using int_size = size_t<int>;

} // namespace gxm

#endif