#include <gxm/main/app.h>

#include <cstdlib>

#include <gxm/render/gl4/render.h>

namespace gxm::main {

app::app()
    : exit_code_(EXIT_SUCCESS) {}
app::~app() {}

void app::setup() {
    init_render();
    init_window();
}

void app::cleanup() {}
void app::run() {
    bool should_exit = true;
    do {
        should_exit = window_->iterate();
    } while (!should_exit);
}

void app::init_render() {
    GXM_ASSERT(render_ == nullptr, "render_ isn't nullptr");
    render_ = std::make_unique<render::gl4_render>();
}

void app::init_window() {
    GXM_ASSERT(render_ != nullptr, "render_ is nullptr");
    GXM_ASSERT(window_ == nullptr, "window_ isn't nullptr");
    window_ = render_->create_window();
    window_->show();
}

} // namespace gxm::main