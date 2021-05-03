#ifndef GXM_APP_H
#define GXM_APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <boost/noncopyable.hpp>

#include "common.h"
#include "gl_context.h"

namespace gxm {

class app : private boost::noncopyable {
public:
    // using update_t = void (*)();
    using update_t = std::function<void()>;

    app() noexcept;
    virtual ~app();

    virtual void setup(int argc, char *argv[]);
    virtual void cleanup() noexcept;

    void set_window_title(const char *);
    void set_fullscreen(bool fullscreen);
    void toggle_fullscreen();

    void run();

    void set_update(update_t p_update) noexcept;

private:
    GLFWwindow *main_window_;
    bool        fullscreen_;

    update_t    update_;
    gl_context *gl_context_;

    int_size main_window_size_;

    void handle_size_change(GLFWwindow *, int, int);
    void handle_key(
        GLFWwindow *window, int key, int scancode, int action, int mods);

    static void key_callback(
        GLFWwindow *window, int key, int scancode, int action, int mods);

    static void size_change_callback(GLFWwindow *, int, int);

    void switch_to_fullscreen();
    void switch_to_window();
};

} // namespace gxm

#endif