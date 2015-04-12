#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <boost/log/trivial.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/expressions.hpp>

#define LOG_TRACE BOOST_LOG_TRIVIAL(trace)
#define LOG_DEBUG BOOST_LOG_TRIVIAL(debug)
#define LOG_INFO BOOST_LOG_TRIVIAL(info)
#define LOG_WARNING BOOST_LOG_TRIVIAL(warning)
#define LOG_ERROR BOOST_LOG_TRIVIAL(error)
#define LOG_FATAL BOOST_LOG_TRIVIAL(fatal)

class Logger
{
    public:
        Logger();

    private:
        void setFilter(boost::log::trivial::severity_level level);
};

#endif
