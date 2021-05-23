#ifndef GXM_CORE_SCENE_H
#define GXM_CORE_SCENE_H

#include <memory>

#include <boost/noncopyable.hpp>

#include <gxm/core/object.h>

namespace gxm::core {

class scene : private boost::noncopyable {
public:
    scene();
    ~scene();

private:
    std::shared_ptr<object> root_;
};

}; // namespace gxm::core

#endif