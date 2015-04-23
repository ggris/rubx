#ifndef LOGGER_HPP
#define LOGGER_HPP
/*
#include <boost/log/trivial.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/expressions.hpp>
*/
#include <iostream>
#include <string>
#include <sstream>
/*
#define LOG_TRACE std::cout << "\nTRACE : "
#define LOG_DEBUG std::cout << "\nDEBUG : "
#define LOG_INFO std::cout << "\nINFO : "
#define LOG_WARNING std::cout << "\nWARNING : "
#define LOG_ERROR std::cout << "\nERROR : "
#define LOG_FATAL std::cout << "\nFATAL : "
*/
struct Logger
{
};


/*
Logger& operator<<(Logger &logger, const std::string &val);

Logger& operator<<(Logger &logger, const int &val);
*/

void operator+=(Logger logger, const std::ostream &log);

#define BOOST_LOG_TRIVIAL(level) std::cerr << #level << " : "; Logger() += std::cout

#define LOG_TRACE BOOST_LOG_TRIVIAL(trace)
#define LOG_DEBUG BOOST_LOG_TRIVIAL(debug)
#define LOG_INFO BOOST_LOG_TRIVIAL(info)
#define LOG_WARNING BOOST_LOG_TRIVIAL(warning)
#define LOG_ERROR BOOST_LOG_TRIVIAL(error)
#define LOG_FATAL BOOST_LOG_TRIVIAL(fatal)


    /*
class Logger
{
    public:
        Logger();

    private:
        void setFilter(boost::log::trivial::severity_level level);
};

*/

#endif
