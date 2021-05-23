#ifndef GXM_COER_OBJECT_H
#define GXM_COER_OBJECT_H

#include <boost/noncopyable.hpp>

namespace gxm::core {

class object : private boost::noncopyable {
public:
    object();
    ~object();

    void on_add_to_parent();
    void on_remove_from_parent();

    void on_add_to_scene();
    void on_remove_from_scene();

private:
};

}; // namespace gxm::core

#endif