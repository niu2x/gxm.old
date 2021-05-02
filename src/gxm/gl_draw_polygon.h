#ifndef GXM_GL_DRAW_POLYGON_H
#define GXM_GL_DRAW_POLYGON_H

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "common.h"
#include "gl_buffer.h"
#include "gl_draw_command.h"
#include "gl_vertex.h"

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

private:
    size_t vertex_count_;
    size_t indice_count_;

    gl_buffer vertex_buffer_;
    gl_buffer indice_buffer_;

    GLuint vao_;
};

} // namespace gxm

#endif