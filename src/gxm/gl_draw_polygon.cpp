#include "gl_draw_polygon.h"

namespace gxm {

#define OFF(st, mem) GXM_OFFSET_OF(st, mem)

gl_draw_polygon::gl_draw_polygon()
    : vertex_count_(0)
    , indice_count_(0)
    , vao_(0) {
    reserve_vertex(3);
    reserve_indice(3);

    glGenVertexArrays(1, &vao_);

    glBindVertexArray(vao_);
    vertex_buffer_.bind_to(gl_buffer::bind_point::vertex);
    indice_buffer_.bind_to(gl_buffer::bind_point::vertex_indice);

    auto gvap = glVertexAttribPointer;
    gvap(0, 3, GL_FLOAT, GL_FALSE, sizeof(gl_vertex), OFF(gl_vertex, x));
    gvap(1, 4, GL_FLOAT, GL_FALSE, sizeof(gl_vertex), OFF(gl_vertex, r));
    gvap(2, 2, GL_FLOAT, GL_FALSE, sizeof(gl_vertex), OFF(gl_vertex, u));
}

gl_draw_polygon::~gl_draw_polygon() {
    glDeleteVertexArrays(1, &vao_);
}

void gl_draw_polygon::reserve_vertex(size_t p_vertex_count) {
    if (vertex_count_ != p_vertex_count) {
        vertex_count_ = p_vertex_count;
        glBindVertexArray(vao_);
        vertex_buffer_.resize(vertex_count_ * sizeof(gl_vertex));
    }
}

void gl_draw_polygon::draw() {}

void gl_draw_polygon::reserve_indice(size_t p_indice_count) {
    if (indice_count_ != p_indice_count) {
        indice_count_ = p_indice_count;
        glBindVertexArray(vao_);

        indice_buffer_.resize(indice_count_ * sizeof(uint16_t));
    }
}

void gl_draw_polygon::set_vertex(size_t index, const gl_vertex &v) {
    assert(index < vertex_count_);
    glBindVertexArray(vao_);

    vertex_buffer_.set_data(index * sizeof(gl_vertex), &v, sizeof(v));
}

void gl_draw_polygon::set_indice(size_t index, uint16_t indice) {
    assert(index < indice_count_);
    glBindVertexArray(vao_);
    indice_buffer_.set_data(index * sizeof(uint16_t), &indice, sizeof(indice));
}

} // namespace gxm