#include "logger.hpp"

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

