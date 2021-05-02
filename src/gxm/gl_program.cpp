#include "gl_program.h"

namespace gxm {

namespace {

#define IS_REQUIRED(t) is_required<t>::value

gl_program::shader_type required_shaders[] = {
    gl_program::shader_type::vertex,
    gl_program::shader_type::fragment,
};

bool check_required_shaders(const gl_program::source &p_source) {
    for (auto shader_type : required_shaders) {
        if (p_source.find(shader_type) == p_source.end())
            return false;
    }
    return true;
}

GLuint compile_shader(gl_program::shader_type type, const char *source) {
    return 0;
}
} // namespace

// auto v = IS_REQUIRED(gl_program::shader_type::fragment);

gl_program::gl_program()
    : name_(0) {}
gl_program::~gl_program() {
    if (valid())
        glDeleteProgram(name_);
}

bool gl_program::init(const source &p_source) {
    assert(!valid());
    assert(check_required_shaders(p_source));

    struct shaders {
        GLuint names[size_t(shader_type::count)];
        shaders() {
            memset(names, 0, sizeof(names));
        }
        ~shaders() {
            for (auto name : names) {
                if (name != 0)
                    glDeleteShader(name);
            }
        }
    } my_shaders;

    for (auto &iter : p_source) {
        auto shader = compile_shader(iter.first, iter.second);
        if (shader)
            GXM_MAP_ENUM(shaders.names, iter.first) = shader;
        else
            return false;
    }

    return true;
}

} // namespace gxm