#ifndef GXM_SCRIPT_LUA_ENGINE_H
#define GXM_SCRIPT_LUA_ENGINE_H

#include <boost/noncopyable.hpp>
#include <lua.hpp>

#include <gxm/common.h>

namespace gxm::script {

class lua_engine : private boost::noncopyable {
public:
    lua_engine();
    ~lua_engine();
    void run(const char *lua_code);

private:
    lua_State *lua_state_;
    static int panic_handler(lua_State *L);
};

} // namespace gxm::script

#endif