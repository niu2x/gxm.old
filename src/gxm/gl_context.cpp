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

} // namespace gxm