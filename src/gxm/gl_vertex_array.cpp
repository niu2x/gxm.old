#include "gl_vertex_array.h"

#include "gl_buffer.h"

namespace gxm {

gl_vertex_array::gl_vertex_array() {
    glGenVertexArrays(1, &name_);
    assert(name_ != 0);
}
gl_vertex_array::~gl_vertex_array() {
    glDeleteVertexArrays(1, &name_);
}

void gl_vertex_array::bind() {
    glBindVertexArray(name_);
    gl_buffer::invalid_binds();
}
void gl_vertex_array::unbind() {
    glBindVertexArray(0);
    gl_buffer::invalid_binds();
}

} // namespace gxm