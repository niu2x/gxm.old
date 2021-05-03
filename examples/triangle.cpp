#include <stdio.h>
#include <unistd.h>

#include <gxm/app.h>
#include <gxm/gl_draw_polygon.h>
#include <gxm/gl_program.h>

size_t file_size(FILE *fp) {
    assert(fp);

    auto old_pos = ftell(fp);
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, old_pos, SEEK_SET);
    return size;
}

std::string read_file(const char *pathname) {
    FILE *fp = fopen(pathname, "rb");
    assert(fp);
    std::string sz;
    auto        size = file_size(fp);
    sz.resize(size);
    fread(sz.data(), 1, size, fp);
    fclose(fp);
    return sz;
}

int main(int argc, char *argv[]) {
    gxm::app my_app;

    auto glsl_vert = read_file("../res/glsl/default.vert");
    auto glsl_frag = read_file("../res/glsl/default.frag");

    gxm::gl_program::source glsl_source;
    glsl_source[gxm::gl_program::shader_type::vertex]   = glsl_vert.c_str();
    glsl_source[gxm::gl_program::shader_type::fragment] = glsl_frag.c_str();

    my_app.setup(argc, argv);
    my_app.set_window_title("triangle");
    gxm::gl_context::instance().set_clear_color(gxm::color::black);
    gxm::gl_context::instance();

    gxm::gl_program program;
    assert(program.init(glsl_source));

    gxm::gl_draw_polygon triangle;
    triangle.reserve_vertex(3);
    triangle.reserve_indice(6);

    triangle.set_vertex(0, gxm::gl_vertex{0.9, 0.9, 0.1, 1, 0, 0, 1, 0, 0});
    triangle.set_vertex(1, gxm::gl_vertex{-0.9, 0.9, 0.1, 0, 1, 0, 1, 0, 0});
    triangle.set_vertex(2, gxm::gl_vertex{0, -0.9, 0.1, 0, 0, 1, 1, 0, 0});

    triangle.set_indice(0, 0);
    triangle.set_indice(1, 1);
    triangle.set_indice(2, 1);
    triangle.set_indice(3, 2);
    triangle.set_indice(4, 2);
    triangle.set_indice(5, 0);

    triangle.set_mode(gxm::gl_draw_polygon::mode_t::line);
    triangle.set_program(&program);
    my_app.set_update([&triangle]() {
        triangle.draw();
    });
    my_app.run();
    my_app.cleanup();

    return 0;
}
