#include <gxm/app.h>

int main(int argc, char *argv[]) {
    gxm::app my_app;

    my_app.setup(argc, argv);
    my_app.set_window_title("empty window");
    my_app.run();
    my_app.cleanup();

    return 0;
}
