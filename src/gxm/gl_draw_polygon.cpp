#include "gl_draw_polygon.h"

#include "gl_bridge.h"

namespace gxm {

#define OFF(st, mem) GXM_OFFSET_OF(st, mem)

gl_draw_polygon::gl_draw_polygon()
    : vertex_count_(0)
    , indice_count_(0) {

    vertex_buffer_.set_usage_hint(gl_buffer::usage::dynamic_draw);
    indice_buffer_.set_usage_hint(gl_buffer::usage::dynamic_draw);
    assert(!glGetError());

    vertex_array_.bind();

    reserve_vertex(3);
    reserve_indice(3);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    auto gvap = glVertexAttribPointer;
    gvap(0, 3, GL_FLOAT, GL_FALSE, sizeof(gl_vertex), OFF(gl_vertex, x));
    gvap(1, 4, GL_FLOAT, GL_FALSE, sizeof(gl_vertex), OFF(gl_vertex, r));
    gvap(2, 2, GL_FLOAT, GL_FALSE, sizeof(gl_vertex), OFF(gl_vertex, u));

    vertex_array_.unbind();
}

gl_draw_polygon::~gl_draw_polygon() {}

void gl_draw_polygon::reserve_vertex(size_t p_vertex_count) {
    if (vertex_count_ != p_vertex_count) {
        vertex_count_ = p_vertex_count;
        vertex_buffer_.bind_to(gl_buffer::bind_point::vertex);
        vertex_buffer_.resize(vertex_count_ * sizeof(gl_vertex));
    }
}

void gl_draw_polygon::draw() {

    vertex_array_.bind();

    vertex_buffer_.bind_to(gl_buffer::bind_point::vertex);
    indice_buffer_.bind_to(gl_buffer::bind_point::vertex_indice);

    program()->use();
    glBlendFunc(GL_ONE, GL_ONE);
    auto m = GXM_MAP_ENUM(gl_mode_map, mode());
    glDrawElements(m, indice_count_, GL_UNSIGNED_SHORT, 0);

    vertex_array_.unbind();
}

void gl_draw_polygon::reserve_indice(size_t p_indice_count) {
    if (indice_count_ != p_indice_count) {
        indice_count_ = p_indice_count;
        indice_buffer_.bind_to(gl_buffer::bind_point::vertex_indice);
        indice_buffer_.resize(indice_count_ * sizeof(uint16_t));
    }
}

void gl_draw_polygon::set_vertex(size_t index, const gl_vertex &v) {
    assert(index < vertex_count_);

    vertex_buffer_.bind_to(gl_buffer::bind_point::vertex);
    vertex_buffer_.set_data(index * sizeof(gl_vertex), &v, sizeof(v));
}

void gl_draw_polygon::set_indice(size_t index, uint16_t indice) {
    assert(index < indice_count_);
    indice_buffer_.bind_to(gl_buffer::bind_point::vertex_indice);
    indice_buffer_.set_data(index * sizeof(uint16_t), &indice, sizeof(indice));
}

} // namespace gxm