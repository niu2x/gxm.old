#include "log.h"

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

#include "common.h"

namespace gxm {

namespace {

decltype(boost::log::trivial::info) log_level_map[] = {
    boost::log::trivial::trace,
    boost::log::trivial::debug,
    boost::log::trivial::info,
    boost::log::trivial::warning,
    boost::log::trivial::error,
    boost::log::trivial::fatal,
};

} // namespace

void log_utils::set_log_level(log_level level) {
    boost::log::core::get()->set_filter(boost::log::trivial::severity >=
                                        GXM_MAP_ENUM(log_level_map, level));
}

} // namespace gxm
