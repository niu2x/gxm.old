#include "gl_program.h"

#include <glsl/glsl_optimizer.h>

namespace gxm {

namespace {

#define IS_REQUIRED(t) is_required<t>::value

gl_program::shader_type required_shaders[] = {
    gl_program::shader_type::vertex,
    gl_program::shader_type::fragment,
};

GLenum gl_shader_map[] = {
    GL_VERTEX_SHADER,
    GL_FRAGMENT_SHADER,
    GL_GEOMETRY_SHADER,
};

bool check_required_shaders(const gl_program::source &p_source) {
    for (auto shader_type : required_shaders) {
        if (p_source.find(shader_type) == p_source.end())
            return false;
    }
    return true;
}

GLuint compile_shader(gl_program::shader_type type, const char *source) {

    GXM_LOG_T << "compile_shader " << 0 << "type:" << (size_t)type;
    auto name = glCreateShader(GXM_MAP_ENUM(gl_shader_map, type));
    GXM_LOG_T << "compile_shader " << 1;
    assert(name != 0);
    GXM_LOG_T << "compile_shader " << 1.1;
    assert(source != nullptr);
    GXM_LOG_T << "compile_shader " << 1.2;

    glShaderSource(name, 1, &source, nullptr);
    GXM_LOG_T << "compile_shader " << 2;

    glCompileShader(name);
    GXM_LOG_T << "compile_shader " << 3;

    GLint success = 0;
    glGetShaderiv(name, GL_COMPILE_STATUS, &success);
    GXM_LOG_T << "compile_shader " << 4;

    if (success == GL_FALSE) {
        GLint maxLength = 0;
        GXM_LOG_T << "compile_shader " << 5;
        glGetShaderiv(name, GL_INFO_LOG_LENGTH, &maxLength);

        GXM_LOG_T << "compile_shader " << 6;
        std::vector<GLchar> error_log(maxLength);
        glGetShaderInfoLog(name, maxLength, &maxLength, &error_log[0]);

        GXM_LOG_T << "compile_shader " << 7;
        GXM_LOG_E << "glsl compile failed: " << error_log.data();
        glDeleteShader(name); // Don't leak the shader.
        return 0;
    }
    GXM_LOG_T << "compile_shader " << 8;

    return name;
}

auto opt_enable = false;

using opt_source =
    std::map<gl_program::shader_type, std::pair<const char *, std::string>>;

opt_source opt_glsl_source(const gl_program::source &p_source) {

    opt_source my_opt_source;

    auto ctx = glslopt_initialize(kGlslTargetOpenGL);
    for (auto &it : p_source) {

        glslopt_shader_type opt_shader_type;

        if (opt_enable && it.first == gl_program::shader_type::vertex) {
            opt_shader_type = kGlslOptShaderVertex;
        }

        else if (opt_enable && it.first == gl_program::shader_type::fragment) {
            opt_shader_type = kGlslOptShaderFragment;
        }

        else {
            my_opt_source[it.first] = std::make_pair<const char *, std::string>(
                (const char *)(it.second), "");
            continue;
        }

        auto shader = glslopt_optimize(ctx, opt_shader_type, it.second, 0);
        if (glslopt_get_status(shader)) {
            auto new_source = glslopt_get_output(shader);

            my_opt_source[it.first] = std::make_pair<const char *, std::string>(
                nullptr, new_source);
        } else {
            auto error_log = glslopt_get_log(shader);
            GXM_LOG_F << "glslopt_optimize error: " << error_log;
            my_opt_source[it.first] = std::make_pair<const char *, std::string>(
                (const char *)(it.second), "");
        }
        glslopt_shader_delete(shader);
    }
    glslopt_cleanup(ctx);
    return my_opt_source;
}

} // namespace

// auto v = IS_REQUIRED(gl_program::shader_type::fragment);

gl_program::gl_program()
    : name_(0) {}
gl_program::~gl_program() {
    if (valid())
        glDeleteProgram(name_);
}

void gl_program::use() {
    glUseProgram(name_);
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

    opt_source my_opt_source = opt_glsl_source(p_source);

    for (auto &iter : my_opt_source) {
        const char *src = iter.second.first;
        if (!src)
            src = iter.second.second.c_str();
        auto shader = compile_shader(iter.first, src);
        if (shader)
            GXM_MAP_ENUM(my_shaders.names, iter.first) = shader;
        else {
            GXM_LOG_F << "compile_shader failed";
            return false;
        }
    }

    name_ = glCreateProgram();
    assert(name_ != 0);

    for (auto shader : my_shaders.names) {
        if (shader != 0)
            glAttachShader(name_, shader);
    }
    glLinkProgram(name_);

    GLint success = 0;
    glGetProgramiv(name_, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(name_, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> error_log(maxLength);
        glGetProgramInfoLog(name_, maxLength, &maxLength, &error_log[0]);

        GXM_LOG_E << "glsl link failed: " << error_log.data();
        glDeleteProgram(name_); // Don't leak the shader.
        return false;
    }

    return true;
}

} // namespace gxm