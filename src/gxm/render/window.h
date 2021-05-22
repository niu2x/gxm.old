#ifndef GXM_RENDER_WINDOW_H
#define GXM_RENDER_WINDOW_H

#include <boost/noncopyable.hpp>

namespace gxm::render {

class window : private boost::noncopyable {
public:
    window();
    virtual ~window();
    virtual void show() {}
    virtual void hide() {}
    virtual bool iterate() {
        return true;
    }
};

}; // namespace gxm::render

#endif