#ifndef GXM_GL_CONTEXT_H
#define GXM_GL_CONTEXT_H

#include <memory>

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "common.h"

namespace gxm {

class gl_context : private boost::noncopyable {
public:
    static void create_instance();
    static void delete_instance();

    static gl_context &instance() noexcept {
        return *instance_;
    }

    void draw();
    void dump_infos();

    void set_clear_color(const color &p_color);
    void set_depth_test_enable(bool b);

private:
    gl_context();
    ~gl_context();
    static gl_context *instance_;
};

} // namespace gxm

#endif