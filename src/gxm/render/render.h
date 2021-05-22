#ifndef GXM_RENDER_RENDER_H
#define GXM_RENDER_RENDER_H

#include <memory>

#include <boost/noncopyable.hpp>

#include <gxm/render/window.h>

namespace gxm::render {

class render : private boost::noncopyable {
public:
    render();
    virtual ~render();
    virtual std::unique_ptr<window> create_window() = 0;
};

}; // namespace gxm::render

#endif