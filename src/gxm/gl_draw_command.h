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
    enum class mode_t {
        point,
        line,
        triangle,
    };

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

    mode_t mode() const noexcept {
        return mode_;
    }
    void set_mode(mode_t p_mode) {
        mode_ = p_mode;
    }

private:
    gl_blend    blend_;
    gl_program *program_;
    mode_t      mode_;
};

} // namespace gxm

#endif