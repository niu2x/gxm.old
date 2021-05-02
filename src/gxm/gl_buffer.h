#ifndef GXM_GL_BUFFER_H
#define GXM_GL_BUFFER_H

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "common.h"

namespace gxm {

class gl_buffer : private boost::noncopyable {
public:
    enum class bind_point : uint8_t {
        vertex = 0,
        vertex_indice,
        copy_read,
        copy_write,
        uniform,
        count,
    };

    enum class usage : uint8_t {
        stream_draw = 0,
        stream_read,
        stream_copy,

        static_draw,
        static_read,
        static_copy,

        dynamic_draw,
        dynamic_read,
        dynamic_copy,

        count,
    };

    enum class access : uint8_t {
        read = 0,
        write,
        read_write,
    };

    gl_buffer(bool immutable = false);
    ~gl_buffer();

    void bind_to(bind_point target);
    void unbind();

    void resize(size_t bytes);

    bind_point current_bp() const noexcept {
        return active_buffers[(size_t)(current_bp_)] == name_
                   ? current_bp_
                   : bind_point::count;
    }
    bool had_bind_to(bind_point target) const noexcept {
        return current_bp() == target;
    }

    void set_usage_hint(usage hint) noexcept {
        usage_hint_ = hint;
    }

    void *map(access p_access);
    void  unmap();

private:
    GLuint name_;

    bool immutable_;
    bool alloced_;
    bool maping_;

    usage usage_hint_;

    bind_point    current_bp_;
    static GLuint active_buffers[(size_t)(bind_point::count)];
};

} // namespace gxm
#endif