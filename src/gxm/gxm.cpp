#include <gxm/gxm.h>

namespace {

int run() {
    gxm::script::lua_engine lua;
    lua.run("print('hello gxm!')");
    return 0;
}

}; // namespace

int main() {
    return run();
}