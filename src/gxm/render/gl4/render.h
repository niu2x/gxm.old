#ifndef GXM_RENDER_GL4_RENDER_H
#define GXM_RENDER_GL4_RENDER_H

#include <gxm/render/render.h>

namespace gxm::render {

class gl4_render : public render {
public:
    gl4_render();
    virtual ~gl4_render();
    virtual std::unique_ptr<window> create_window() override;
};

}; // namespace gxm::render

#endif