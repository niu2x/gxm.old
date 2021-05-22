#ifndef GXM_GL_RENDERBUFFER_H
#define GXM_GL_RENDERBUFFER_H

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "common.h"

namespace gxm {

class gl_renderbuffer : boost::noncopyable {
public:
    enum type_t {
        stencil_depth = 0,
    };
    gl_renderbuffer(size_t width, size_t height);
    ~gl_renderbuffer();

    void use(size_t texture_unit_idx);

    size_t width() const noexcept {
        return width_;
    }
    size_t height() const noexcept {
        return height_;
    }

    GLuint name() const noexcept {
        return name_;
    }

private:
    GLuint name_;
    type_t type_;

    size_t width_;
    size_t height_;
};

} // namespace gxm

#endif