#ifndef GXM_GL_CONTEXT_H
#define GXM_GL_CONTEXT_H

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include <memory>

namespace gxm {

class gl_context : private boost::noncopyable {
public:
    static void        create_instance();
    static void        delete_instance();
    static gl_context *instance() noexcept {
        return instance_;
    }

    void draw();

private:
    gl_context();
    ~gl_context();
    static gl_context *instance_;
};

} // namespace gxm

#endif