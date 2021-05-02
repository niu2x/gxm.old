#ifndef GXM_GL_VERTEX_ARRAY_H
#define GXM_GL_VERTEX_ARRAY_H

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "common.h"

namespace gxm {

class gl_vertex_array : private boost::noncopyable {
public:
    gl_vertex_array();
    ~gl_vertex_array();

    void bind();
    void unbind();

private:
    GLuint name_;
};

} // namespace gxm

#endif