#include "gl_context.h"

#include "exception.h"
#include "log.h"

namespace gxm {

gl_context *gl_context::instance_ = nullptr;

gl_context::gl_context() {}
gl_context::~gl_context() {}

void gl_context::draw() {}

void gl_context::create_instance() {
    assert(instance_ == nullptr);

    instance_ = new gl_context;
}
void gl_context::delete_instance() {
    assert(instance_ != nullptr);

    delete instance_;
    instance_ = nullptr;
}

void gl_context::dump_infos() {
    GXM_LOG_I << "GL_VENDOR: " << glGetString(GL_VENDOR);
    GXM_LOG_I << "GL_RENDERER: " << glGetString(GL_RENDERER);
    GXM_LOG_I << "GL_VERSION: " << glGetString(GL_VERSION);
    GXM_LOG_I << "GL_SHADING_LANGUAGE_VERSION: "
              << glGetString(GL_SHADING_LANGUAGE_VERSION);
}

} // namespace gxm