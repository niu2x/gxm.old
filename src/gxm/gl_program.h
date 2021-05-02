#ifndef GXM_GL_PROGRAM_H
#define GXM_GL_PROGRAM_H

#include <map>

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "common.h"

namespace gxm {

class gl_program : private boost::noncopyable {
public:
    enum class shader_type : uint8_t {
        vertex = 0,
        fragment,
        geometry,
        count,
    };

    using source = std::map<shader_type, const char *>;

    gl_program();
    ~gl_program();

    bool init(const source &p_source);
    bool valid() const noexcept {
        return name_ != 0;
    }

    void use();

private:
    GLuint name_;
};

} // namespace gxm

#endif