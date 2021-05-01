#include "app.h"
#include "exception.h"
#include "gl_buffer.h"
#include "gl_context.h"
#include "log.h"

int main(int argc, char *argv[]) {
    gxm::app my_app;

    my_app.setup(argc, argv);
    my_app.run();
    my_app.cleanup();

    return 0;
}
