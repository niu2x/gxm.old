#ifndef GXM_RENDER_GL4_WINDOW_H
#define GXM_RENDER_GL4_WINDOW_H

#include <atomic>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gxm/common.h>
#include <gxm/render/window.h>

namespace gxm::render {

class gl4_window : public window {
public:
    gl4_window(int w = 640, int h = 480);
    virtual ~gl4_window();
    virtual void show() override;
    virtual void hide() override;
    virtual bool iterate() override;

private:
    GLFWwindow *glfw_window_;

    static void                  setup();
    static void                  cleanup();
    static std::atomic<uint32_t> instance_counter;
};

}; // namespace gxm::render

#endif