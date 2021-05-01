#ifndef GXM_GL_BUFFER_H
#define GXM_GL_BUFFER_H

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

namespace gxm {

class gl_buffer : private boost::noncopyable {
public:
    gl_buffer();
    ~gl_buffer();

private:
    GLuint name_;
};

} // namespace gxm
#endif