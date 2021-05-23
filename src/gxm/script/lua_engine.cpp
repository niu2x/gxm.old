#include <gxm/script/lua_engine.h>

#include <iostream>

namespace gxm::script {

lua_engine::lua_engine()
    : lua_state_(nullptr) {
    lua_state_ = luaL_newstate();
    GXM_ASSERT(lua_state_, "alloc lua_state failed.");
    lua_atpanic(lua_state_, panic_handler);
    luaL_openlibs(lua_state_);
}

lua_engine::~lua_engine() {
    if (lua_state_) {
        lua_close(lua_state_);
    }
}

void lua_engine::run(const char *lua_code) {
    if (luaL_dostring(lua_state_, lua_code)) {
        const char *err_msg = luaL_checkstring(lua_state_, -1);
        if (err_msg)
            std::cerr << err_msg << std::endl;
    }
}

int lua_engine::panic_handler(lua_State *L) {
    std::cout << "panic_handler" << std::endl;
    return 0;
}

} // namespace gxm::script
