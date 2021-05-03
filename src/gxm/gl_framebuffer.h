#ifndef GXM_GL_FRAMEBUFFER_H
#define GXM_GL_FRAMEBUFFER_H

#include <GL/glew.h>
#include <boost/noncopyable.hpp>

#include "common.h"
#include "gl_draw_polygon.h"
#include "gl_program.h"
#include "gl_renderbuffer.h"
#include "gl_texture.h"
#include "glsl.h"

namespace gxm {

class gl_framebuffer : private boost::noncopyable {
public:
    gl_framebuffer(int width, int height);
    gl_framebuffer(const int_size &size);
    ~gl_framebuffer();

    static void push(gl_framebuffer &);
    static void pop();

    void draw();
    // void blit();

    GLuint name() const noexcept {
        return name_;
    }
    int_size size() const noexcept {
        return size_;
    }

    static int_size drawbuffer_size() noexcept;

    gl_texture &color_attachment() noexcept {
        return color_;
    }
    void clear();

    static void setup();
    static void cleanup();

private:
    int_size size_;
    GLuint   name_;

    gl_texture      color_;
    gl_renderbuffer stencil_depth_;

    enum { fb_stack_capacity = 128 };
    static gl_framebuffer *fb_stack_[fb_stack_capacity];
    static int             fb_stack_top_;

    static std::unique_ptr<gl_draw_polygon> draw_;
    static std::unique_ptr<gl_program>      program_;
};

} // namespace gxm

#endif