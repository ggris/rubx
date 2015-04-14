#include "util/logger.hpp"
#include "context.hpp"

#include "main.hpp"

int main (int argc, char *argv[])
{
    Logger logger;

    Context context;
    context.run();

    LOG_INFO << "Terminating";
    return 0;
}
