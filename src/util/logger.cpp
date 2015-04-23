#include "logger.hpp"
#include <sstream>

Log& operator<<(Log &log, const std::string &val)
{
    log.content_ << val ;
    return log;
}

Log& operator<<(Log &log, const int &val)
{
    log.content_ << val ;
    return log;
}

Logger& operator<<(Logger &logger, const Log &log)
{
    std::cout << log.content_ << std::endl;
    return logger;
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


