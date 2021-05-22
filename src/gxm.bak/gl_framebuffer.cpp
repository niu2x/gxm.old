#include "gl_framebuffer.h"

#include "app.h"

namespace gxm {

std::unique_ptr<gl_draw_polygon> gl_framebuffer::draw_    = nullptr;
std::unique_ptr<gl_program>      gl_framebuffer::default_program_ = nullptr;

gl_framebuffer *gl_framebuffer::fb_stack_[128];

int gl_framebuffer::fb_stack_top_ = 0;

void gl_framebuffer::set_program(gl_program *p) {
    program_ = p;
}

gl_framebuffer::gl_framebuffer(const int_size &size)
    : size_(size)
    , program_(nullptr)
    , stencil_depth_(size.width, size.height) {
    glGenFramebuffers(1, &name_);
    assert(name_);

    GXM_LOG_I << "framebuffer: " << size_.width << "," << size_.height;

    glBindFramebuffer(GL_FRAMEBUFFER, name_);
    color_.set_data(size_.width, size_.height, pixel_format::rgba, nullptr);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_.name(), 0);
    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER,
        GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER,
        stencil_depth_.name());

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        GXM_LOG_F << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
        throw exception("create Framebuffer failed");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

gl_framebuffer::gl_framebuffer(int w, int h)
    : gl_framebuffer(int_size{w, h}) {}

gl_framebuffer::~gl_framebuffer() {
    glDeleteFramebuffers(1, &name_);
}

void gl_framebuffer::draw() {
    glClear(0xFFFFFFFF);

    draw_->set_program(program_ ? program_ : default_program_.get());
    draw_->set_texture(0, &color_);
    draw_->draw();
}

void gl_framebuffer::clear() {
    static auto all_bits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
                           GL_STENCIL_BUFFER_BIT;
    glClear(all_bits);
}

// void gl_framebuffer::blit() {
//     glBindFramebuffer(GL_READ_FRAMEBUFFER, name_);
//     auto dst_size = drawbuffer_size();

//     glBlitFramebuffer(
//         0,
//         0,
//         size_.width,
//         size_.height,
//         0,
//         0,
//         dst_size.width,
//         dst_size.height,
//         GL_COLOR_BUFFER_BIT,
//         GL_LINEAR);
//     GXM_CHECK_GL_ERROR();

//     glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
// }

int_size gl_framebuffer::drawbuffer_size() noexcept {
    if (fb_stack_top_ > 0) {
        return fb_stack_[fb_stack_top_ - 1]->size();
    } else {
        return app::main().main_window_size();
    }
}

void gl_framebuffer::setup() {
    assert(!draw_);
    draw_ = std::make_unique<gl_draw_polygon>();

    draw_->reserve_vertex(4);
    draw_->reserve_indice(6);

    draw_->set_vertex(0, gxm::gl_vertex{1, 1, 0, 1, 1, 1, 1, 1, 1});
    draw_->set_vertex(1, gxm::gl_vertex{-1, 1, 0, 1, 1, 1, 1, 0, 1});
    draw_->set_vertex(2, gxm::gl_vertex{-1, -1, 0, 1, 1, 1, 1, 0, 0});
    draw_->set_vertex(3, gxm::gl_vertex{1, -1, 0, 1, 1, 1, 1, 1, 0});

    draw_->set_indice(0, 0);
    draw_->set_indice(1, 1);
    draw_->set_indice(2, 2);
    draw_->set_indice(3, 0);
    draw_->set_indice(4, 2);
    draw_->set_indice(5, 3);

    draw_->set_mode(gl_draw_polygon::mode_t::triangle);

    assert(!default_program_);
    default_program_ = std::make_unique<gl_program>();

    gl_program::source glsl_source;
    glsl_source[gl_program::shader_type::vertex]   = glsl::framebuffer_vert;
    glsl_source[gl_program::shader_type::fragment] = glsl::framebuffer_frag;
    assert(default_program_->init(glsl_source));

    draw_->set_program(default_program_.get());
}
void gl_framebuffer::cleanup() {
    draw_ = nullptr;
}

void gl_framebuffer::push(gl_framebuffer &fb) {
    assert(fb_stack_top_ < fb_stack_capacity);

    auto name = fb.name();

    fb_stack_[fb_stack_top_++] = &fb;

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, name);

    auto size = drawbuffer_size();
    glViewport(0, 0, size.width, size.height);
}

void gl_framebuffer::pop() {
    assert(fb_stack_top_ > 0);

    --fb_stack_top_;
    if (fb_stack_top_ > 0) {
        auto name = fb_stack_[fb_stack_top_ - 1]->name();
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, name);
    } else {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }
    auto size = drawbuffer_size();
    glViewport(0, 0, size.width, size.height);
}

} // namespace gxm