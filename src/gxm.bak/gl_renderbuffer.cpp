#include "gl_renderbuffer.h"

namespace gxm {

gl_renderbuffer::gl_renderbuffer(size_t w, size_t h)
    : name_(0)
    , type_(type_t::stencil_depth)
    , width_(w)
    , height_(h) {

    glGenRenderbuffers(1, &name_);
    assert(name_);

    auto rb = GL_RENDERBUFFER;
    glBindRenderbuffer(rb, name_);
    glRenderbufferStorage(rb, GL_DEPTH24_STENCIL8, width_, height_);
}

gl_renderbuffer::~gl_renderbuffer() {
    glDeleteRenderbuffers(1, &name_);
}

} // namespace gxm
