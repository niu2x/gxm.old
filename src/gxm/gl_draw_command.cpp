#include "gl_draw_command.h"

namespace gxm {

gl_draw_command::gl_draw_command()
    : blend_(gl_blend::normal)
    , program_(nullptr) {}

gl_draw_command::~gl_draw_command() {}

void gl_draw_command::set_program(gl_program *p_program) {
    program_ = p_program;
}

void gl_draw_command::set_blend(const gl_blend &p_blend) {
    blend_ = p_blend;
}

} // namespace gxm