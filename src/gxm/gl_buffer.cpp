#include "gl_buffer.h"

namespace gxm {

GLuint gl_buffer::active_buffers[size_t(gl_buffer::bind_point::count)] = {0};

gl_buffer::gl_buffer(bool immutable)
    : name_(0)
    , immutable_(immutable)
    , alloced_(false)
    , maping_(false)
    , size_(0)
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

    GXM_LOG_I << "bind_to " << (int)target;
}

void gl_buffer::resize(size_t bytes) {
    assert(!(alloced_ && immutable_));
    assert(current_bp() != bind_point::count);
    assert(usage_hint_ != usage::count);
    assert(!maping_);

    if (size_ == bytes)
        return;

    std::unique_ptr<std::vector<uint8_t>> origin_data;

    if (size_ > 0) {
        origin_data = std::make_unique<std::vector<uint8_t>>();
        origin_data->resize(size_);
        void *ptr = map(access::read);
        memcpy(origin_data->data(), ptr, size_);
        unmap();
    }

    size_ = bytes;

    auto  gl_target = MAP(gl_buffer_map, current_bp_);
    auto *ptr       = origin_data ? origin_data->data() : nullptr;
    if (immutable_) {
        auto bits = GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
        glBufferStorage(gl_target, size_, ptr, bits);
    } else {
        auto gl_usage = MAP(gl_usage_map, usage_hint_);
        glBufferData(gl_target, size_, ptr, gl_usage);
    }

    alloced_ = true;
}

void gl_buffer::set_data(size_t offset, const void *ptr, size_t size) {
    assert(!maping_);
    assert(current_bp() != bind_point::count);
    assert(offset + size <= size_);

    glBufferSubData(MAP(gl_buffer_map, current_bp_), offset, size, ptr);
    assert(!glGetError());
}

void gl_buffer::dump() {
    assert(!maping_);
    assert(current_bp() != bind_point::count);
    uint16_t *ptr = (uint16_t *)map(access::read);
    unused(ptr);
    // for (size_t i = 0; i < size_ / 2; i++)
    //     printf("%u ", ptr[i]);
    // printf("\n");
    unmap();
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

void gl_buffer::invalid_binds() {
    memset(active_buffers, 0, sizeof(active_buffers));
}

void *gl_buffer::map(access p_access) {
    assert(current_bp() != bind_point::count);
    assert(!maping_);

    maping_ = true;
    assert(!glGetError());
    auto *ptr = glMapBuffer(MAP(gl_buffer_map, current_bp_),
                            MAP(gl_access_map, p_access));
    assert(!glGetError());
    return ptr;
}

void gl_buffer::unmap() {
    assert(current_bp() != bind_point::count);
    assert(maping_);
    glUnmapBuffer(MAP(gl_buffer_map, current_bp_));
    maping_ = false;
}

} // namespace gxm