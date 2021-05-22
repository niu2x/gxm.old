#include <gxm/render/gl4/render.h>

#include <gxm/render/gl4/window.h>

namespace gxm::render {

std::unique_ptr<window> gl4_render::create_window() {
    return std::make_unique<gl4_window>();
}

gl4_render::gl4_render() {}
gl4_render::~gl4_render() {}

}; // namespace gxm::render
