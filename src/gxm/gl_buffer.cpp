#include "gl_buffer.h"

namespace gxm {

gl_buffer::gl_buffer()
    : name_(0) {
    glGenBuffers(1, &name_);
}

gl_buffer::~gl_buffer() {
    glDeleteBuffers(1, &name_);
}

} // namespace gxm