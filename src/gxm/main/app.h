#ifndef GXM_MAIN_APP_H
#define GXM_MAIN_APP_H

#include <memory>

#include <boost/noncopyable.hpp>

#include <gxm/common.h>
#include <gxm/main/input.h>
#include <gxm/render/render.h>

namespace gxm::main {

class app : private boost::noncopyable {
public:
    app();
    virtual ~app();

    virtual void setup();

    virtual void cleanup();

    virtual void run();

    virtual void handle_input(const input::event &e);

    int exit_code() const noexcept {
        return exit_code_;
    }
    void exit(int code);

private:
    int exit_code_;
    bool should_exit_;

    std::unique_ptr<render::render> render_;
    std::unique_ptr<render::window> window_;

    void init_render();
    void init_window();
};

template <class APP_T>
int run_app() {
    APP_T my_app;
    my_app.setup();
    my_app.run();
    my_app.cleanup();
    return my_app.exit_code();
}

} // namespace gxm::main

#define GXM_MAIN(APP_T)                                                        \
    int main() {                                                               \
        return gxm::main::run_app<APP_T>();                                    \
    }

#endif