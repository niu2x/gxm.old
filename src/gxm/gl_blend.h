#ifndef GXM_GL_BLEND_H
#define GXM_GL_BLEND_H

#include <GL/glew.h>

#include "common.h"

namespace gxm {

class gl_blend {
public:
    GLenum src_factor;
    GLenum dst_factor;

    static const gl_blend normal;
};

} // namespace gxm

#endif