#ifndef GXM_RENDER_VBO_H
#define GXM_RENDER_VBO_H

#include <boost/noncopyable.hpp>

namespace gxm::render {

class vbo : private boost::noncopyable {
public:
    vbo();
    virtual ~vbo();
};

} // namespace gxm::render
#endif