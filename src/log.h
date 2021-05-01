#ifndef GXM_LOG_H
#define GXM_LOG_H

#include <boost/log/trivial.hpp>

#define LOG_T BOOST_LOG_TRIVIAL(trace)
#define LOG_I BOOST_LOG_TRIVIAL(info)
#define LOG_D BOOST_LOG_TRIVIAL(debug)
#define LOG_W BOOST_LOG_TRIVIAL(warn)
#define LOG_E BOOST_LOG_TRIVIAL(error)
#define LOG_F BOOST_LOG_TRIVIAL(fatal)

#endif