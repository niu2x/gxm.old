#include "app.h"

namespace gxm {

namespace {

void default_update() {
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

const int_size default_window_size = {640, 480};

} // namespace

app::app() noexcept
    : main_window_(nullptr)
    , fullscreen_(false)
    , update_(&default_update)
    , main_window_size_(default_window_size) {}

app::~app() {}

void app::setup(int argc, char *argv[]) {
    unused(argc, argv);

    auto glfw_init_success = glfwInit();
    assert(glfw_init_success);

    const char *window_title = "GXM Game App";

    main_window_ = glfwCreateWindow(main_window_size_.width,
                                    main_window_size_.height,
                                    window_title,
                                    0,
                                    nullptr);
    assert(main_window_);

    glfwSetWindowUserPointer(main_window_, this);
    glfwMakeContextCurrent(main_window_);

    set_fullscreen(fullscreen_);

    glfwSetKeyCallback(main_window_, &key_callback);

    auto glew_init_result = glewInit();
    assert(glew_init_result == GLEW_OK);

    // gl_context::create_instance();
    // gl_context_ = gl_context::instance();
    // gl_context_->dump_infos();
}

void app::cleanup() noexcept {

    // gl_context_ = nullptr;
    // gl_context::delete_instance();

    assert(main_window_);

    glfwDestroyWindow(main_window_);
    main_window_ = nullptr;

    glfwTerminate();
}

void app::run() {
    assert(main_window_);

    while (!glfwWindowShouldClose(main_window_)) {
        glfwSwapBuffers(main_window_);
        glfwPollEvents();
        update_();
    }
}

void app::set_window_title(const char *title) {
    assert(main_window_);

    glfwSetWindowTitle(main_window_, title);
}

void app::key_callback(
    GLFWwindow *window, int key, int scancode, int action, int mods) {
    app *my_app = reinterpret_cast<app *>(glfwGetWindowUserPointer(window));
    assert(my_app);
    my_app->handle_key(window, key, scancode, action, mods);
}

void app::handle_key(
    GLFWwindow *window, int key, int scancode, int action, int mods) {
    assert(window == main_window_);
    unused(key, scancode, action, mods);

    // GXM_LOG_D << "handle_key: action: " << action << "key: " << key;

    switch (action) {
        case GLFW_PRESS: {
            switch (key) {
                case GLFW_KEY_F4: {
                    toggle_fullscreen();
                    break;
                }
            }
            break;
        }
    }
}

void app::toggle_fullscreen() {
    set_fullscreen(!fullscreen_);
}

void app::set_fullscreen(bool fullscreen) {
    assert(main_window_);

    if (fullscreen_ != fullscreen) {
        fullscreen_ = fullscreen;

        if (fullscreen_) {
            switch_to_fullscreen();
        } else {
            switch_to_window();
        }
    }
}

void app::switch_to_fullscreen() {
    auto *             monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode    = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(main_window_,
                         monitor,
                         0,
                         0,
                         mode->width,
                         mode->height,
                         mode->refreshRate);
}
void app::switch_to_window() {
    glfwSetWindowMonitor(main_window_,
                         0,
                         0,
                         0,
                         main_window_size_.width,
                         main_window_size_.height,
                         0);
}

// void app

} // namespace gxm