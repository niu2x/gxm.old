#ifndef GXM_GL_DRAW_POLYGON_H
#define GXM_GL_DRAW_POLYGON_H

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "common.h"
#include "gl_buffer.h"
#include "gl_draw_command.h"
#include "gl_texture.h"
#include "gl_vertex.h"
#include "gl_vertex_array.h"

namespace gxm {

class gl_draw_polygon : public gl_draw_command {
public:
    gl_draw_polygon();
    virtual ~gl_draw_polygon();

    void reserve_vertex(size_t p_vertex_count);
    void reserve_indice(size_t p_indice_count);
    void set_vertex(size_t index, const gl_vertex &v);
    void set_indice(size_t index, uint16_t indice);

    virtual void draw();

    void set_texture(size_t idx, gl_texture *tex) noexcept;

private:
    size_t vertex_count_;
    size_t indice_count_;

    gl_buffer vertex_buffer_;
    gl_buffer indice_buffer_;

    gl_vertex_array vertex_array_;

    enum { texture_capacity = 4 };
    gl_texture *textures_[texture_capacity];
};

} // namespace gxm

#endif