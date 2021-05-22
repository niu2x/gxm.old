#include <gxm/render/gl4/window.h>

namespace gxm::render {

std::atomic<uint32_t> gl4_window::instance_counter;

gl4_window::gl4_window(int w, int h) {
    if (++instance_counter == 1) {
        setup();
    }

    glfwWindowHint(GLFW_SAMPLES, 8);
    glfw_window_ = glfwCreateWindow(w, h, "", 0, nullptr);
    GXM_ASSERT(glfw_window_ != nullptr, "create glfw window failed.");
    glfwMakeContextCurrent(glfw_window_);
}
gl4_window::~gl4_window() {
    if (glfw_window_) {
        glfwDestroyWindow(glfw_window_);
        glfw_window_ = nullptr;
    }

    if (--instance_counter == 0) {
        cleanup();
    }
}
void gl4_window::show() {}
void gl4_window::hide() {}

bool gl4_window::iterate() {
    glfwPollEvents();
    glfwSwapBuffers(glfw_window_);
    return glfwWindowShouldClose(glfw_window_);
}

void gl4_window::setup() {
    GXM_ASSERT(glfwInit(), "glfw init failed");
}
void gl4_window::cleanup() {
    glfwTerminate();
}

} // namespace gxm::render
