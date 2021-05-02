#include "gl_buffer.h"

namespace gxm {

GLuint gl_buffer::active_buffers[size_t(gl_buffer::bind_point::count)] = {0};

gl_buffer::gl_buffer(bool immutable)
    : name_(0)
    , immutable_(immutable)
    , alloced_(false)
    , maping_(false)
    , usage_hint_(usage::count)
    , current_bp_(bind_point::count) {
    glGenBuffers(1, &name_);
    assert(name_ != 0);
}

gl_buffer::~gl_buffer() {
    glDeleteBuffers(1, &name_);
}

namespace {

GLenum gl_buffer_map[] = {
    GL_ARRAY_BUFFER,
    GL_ELEMENT_ARRAY_BUFFER,
    GL_COPY_READ_BUFFER,
    GL_COPY_WRITE_BUFFER,
    GL_UNIFORM_BUFFER,
};

GLenum gl_usage_map[] = {
    GL_STREAM_DRAW,
    GL_STREAM_READ,
    GL_STREAM_COPY,

    GL_STATIC_DRAW,
    GL_STATIC_READ,
    GL_STATIC_COPY,

    GL_DYNAMIC_DRAW,
    GL_DYNAMIC_READ,
    GL_DYNAMIC_COPY,
};

GLenum gl_access_map[] = {
    GL_READ_ONLY,
    GL_WRITE_ONLY,
    GL_READ_WRITE,
};

} // namespace

#define MAP(map, v) GXM_MAP_ENUM(map, v)

void gl_buffer::bind_to(bind_point target) {
    if (had_bind_to(target))
        return;

    current_bp_ = target;

    auto gl_target = MAP(gl_buffer_map, current_bp_);
    glBindBuffer(gl_target, name_);

    MAP(active_buffers, current_bp_) = name_;
}

void gl_buffer::resize(size_t bytes) {
    assert(!(alloced_ && immutable_));
    assert(current_bp() != bind_point::count);
    assert(usage_hint_ != usage::count);
    assert(!maping_);

    auto gl_target = MAP(gl_buffer_map, current_bp_);

    if (immutable_) {
        auto bits = GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
        glBufferStorage(gl_target, bytes, nullptr, bits);
    } else {
        auto gl_usage = MAP(gl_usage_map, usage_hint_);
        glBufferData(gl_target, bytes, nullptr, gl_usage);
    }

    alloced_ = true;
}

void gl_buffer::unbind() {
    assert(!maping_);
    if (current_bp() != bind_point::count) {
        auto gl_target = MAP(gl_buffer_map, current_bp_);
        glBindBuffer(gl_target, 0);
        MAP(active_buffers, current_bp_) = 0;
        current_bp_                      = bind_point::count;
    }
}

void *gl_buffer::map(access p_access) {
    assert(current_bp() != bind_point::count);
    assert(!maping_);

    maping_ = true;
    return glMapBuffer(MAP(gl_buffer_map, current_bp_),
                       MAP(gl_access_map, p_access));
}

void gl_buffer::unmap() {
    assert(current_bp() != bind_point::count);
    assert(maping_);
    glUnmapBuffer(MAP(gl_buffer_map, current_bp_));
}

} // namespace gxm