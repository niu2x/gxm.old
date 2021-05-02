#ifndef GXM_GL_DRAW_COMMAND_H
#define GXM_GL_DRAW_COMMAND_H

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "common.h"
#include "gl_blend.h"
#include "gl_program.h"

namespace gxm {

class gl_draw_command : private boost::noncopyable {
public:
    gl_draw_command();
    virtual ~gl_draw_command();
    virtual void draw() = 0;

    void set_blend(const gl_blend &p_blend);
    void set_program(gl_program *p_program);

    gl_blend &blend() noexcept {
        return blend_;
    }

    gl_program *program() const noexcept {
        return program_;
    }

private:
    gl_blend    blend_;
    gl_program *program_;
};

} // namespace gxm

#endif