#ifndef GXM_LOG_H
#define GXM_LOG_H

#include <cstdint>

#include <boost/log/trivial.hpp>

#define GXM_LOG_T BOOST_LOG_TRIVIAL(trace)
#define GXM_LOG_D BOOST_LOG_TRIVIAL(debug)
#define GXM_LOG_I BOOST_LOG_TRIVIAL(info)
#define GXM_LOG_W BOOST_LOG_TRIVIAL(warn)
#define GXM_LOG_E BOOST_LOG_TRIVIAL(error)
#define GXM_LOG_F BOOST_LOG_TRIVIAL(fatal)

namespace gxm {

enum class log_level { trace = 0, debug, info, warn, error, fatal };

struct log_utils {
    static void set_log_level(log_level level);
};

} // namespace gxm

#endif