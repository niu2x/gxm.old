#include "gl_texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace gxm {

namespace {
GLenum gl_texture_map[] = {GL_TEXTURE_2D};

}

gl_texture::gl_texture()
    : type_(type_t::tex_2d)
    , width_(0)
    , height_(0) {
    glGenTextures(1, &name_);
    assert(name_);
}
gl_texture::~gl_texture() {
    glDeleteTextures(1, &name_);
}

void gl_texture::set_data(size_t w, size_t h, pixel_format format, void *data) {

    auto target = GXM_MAP_ENUM(gl_texture_map, type_);
    glBindTexture(target, name_);
    auto load = glTexImage2D;

    switch (format) {
        case pixel_format::red: {
            load(target, 0, GL_R8, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);
            break;
        }
        case pixel_format::rgb: {
            load(target, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        }
        case pixel_format::s_rgb: {
            load(target, 0, GL_SRGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        }
        case pixel_format::rgba: {
            load(target, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        }
        case pixel_format::s_rgba: {
            load(target,
                 0,
                 GL_SRGB8_ALPHA8,
                 w,
                 h,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 data);
            break;
        }

        default: {
            GXM_LOG_F << "unsupport pixel_format";
            throw exception("unsupport pixel_format");
        }
    }

    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    width_  = w;
    height_ = h;

    glBindTexture(target, 0);
}

void gl_texture::generate_mipmap() {}

void gl_texture::use(size_t texture_unit_idx) {
    glActiveTexture(GL_TEXTURE0 + texture_unit_idx);
    glBindTexture(GXM_MAP_ENUM(gl_texture_map, type_), name_);
}

bool gl_texture::load_from_file(const char *pathname, bool no_line) {

    int      w, h, channels;
    uint8_t *data = stbi_load(pathname, &w, &h, &channels, 0);
    if (!data){
        return false;
    }

    auto_release free_image([data]() {
        stbi_image_free(data);
    });


    switch (channels) {
        case 1: {
            set_data(w, h, pixel_format::red, data);
            break;
        }
        case 3: {
            if (no_line) {
                set_data(w, h, pixel_format::s_rgb, data);
            } else
                set_data(w, h, pixel_format::rgb, data);

            break;
        }
        case 4: {
            if (no_line) {
                set_data(w, h, pixel_format::s_rgba, data);
            } else
                set_data(w, h, pixel_format::rgba, data);
            break;
        }
        default:
            return false;
    }
    return true;
}

} // namespace gxm