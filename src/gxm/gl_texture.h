#ifndef GXM_TEXTURE_H
#define GXM_TEXTURE_H

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "common.h"

namespace gxm {

class gl_texture : boost::noncopyable {
public:
    enum type {
        tex_2d,
    };
    gl_texture();
    ~gl_texture();

    bool load_from_file(const char *pathname);
    void set_data(size_t w, size_t h, pixel_format format, void *data);
    void generate_mipmap();
    void use(size_t texture_unit_idx);

private:
    GLuint name_;
};

} // namespace gxm

#endif