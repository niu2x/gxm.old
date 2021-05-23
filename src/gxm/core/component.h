#ifndef GXM_CORE_COMPONENT_H
#define GXM_CORE_COMPONENT_H

#include <boost/noncopyable.hpp>

namespace gxm::core {

class component : private boost::noncopyable {
public:
    component();
    virtual ~component();
    virtual private:
};

}; // namespace gxm::core

#endif