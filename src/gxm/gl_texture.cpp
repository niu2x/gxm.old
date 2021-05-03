#include "gl_texture.h"

namespace gxm {

gl_texture::gl_texture() {}
gl_texture::~gl_texture() {}

void gl_texture::set_data(size_t w, size_t h, pixel_format format, void *data) {
    unused(w, h, format, data);
}

void gl_texture::generate_mipmap() {}

void gl_texture::use(size_t texture_unit_idx) {
    unused(texture_unit_idx);
}

bool gl_texture::load_from_file(const char *pathname) {
    unused(pathname);
    return false;
}

} // namespace gxm