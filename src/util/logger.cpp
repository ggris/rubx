#include "logger.hpp"
#include <sstream>
/*
Logger& operator<<(Logger &logger, const std::string &val)
{
    logger.ss_ << val;
    return logger;
}

Logger& operator<<(Logger &logger, const int &val)
{
    logger.ss_ << val;
    return logger;
}
*/

void operator+=(Logger logger, const std::ostream &log)
{
    std::cerr << std::endl;
}

/*

Logger::Logger()
{
    setFilter(boost::log::trivial::trace);
}

void Logger::setFilter(boost::log::trivial::severity_level level)
{
    boost::log::core::get()->set_filter
        (
         boost::log::trivial::severity >= level
        );
    LOG_INFO << "Log level : " << level;
}

*/


