#ifndef GXM_TEXTURE_H
#define GXM_TEXTURE_H

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "common.h"

namespace gxm {

class gl_texture : boost::noncopyable {
public:
    enum type_t {
        tex_2d = 0,
    };
    gl_texture();
    ~gl_texture();

    bool load_from_file(const char *pathname, bool no_line = true);
    void set_data(size_t w, size_t h, pixel_format format, void *data);
    void generate_mipmap();
    void use(size_t texture_unit_idx);

    size_t width() const noexcept {
        return width_;
    }
    size_t height() const noexcept {
        return height_;
    }

private:
    GLuint name_;
    type_t type_;

    size_t width_;
    size_t height_;
};

} // namespace gxm

#endif