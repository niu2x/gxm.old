#include <gxm/main/app.h>

#include <cstdlib>

#include <gxm/render/gl4/render.h>

namespace gxm::main {

app::app()
    : exit_code_(EXIT_SUCCESS)
    , should_exit_(false) {}
app::~app() {}

void app::setup() {
    init_render();
    init_window();
}

void app::cleanup() {}
void app::run() {
    bool clicked_close;

    while (!should_exit_) {
        clicked_close = window_->iterate();
        if (clicked_close) {
            handle_input(input::event(input::event::close));
        }
    }
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

void app::exit(int code) {
    exit_code_   = code;
    should_exit_ = true;
}

void app::handle_input(const input::event &e) {
    switch (e.type()) {
        case input::event::close: {
            exit(EXIT_SUCCESS);
            break;
        }
    }
}

} // namespace gxm::main