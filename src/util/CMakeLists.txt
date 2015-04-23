set(Boost_USE_STATIC_LIBS   ON)

#find_package(Boost REQUIRED COMPONENTS log thread system)

set(SRC
    logger.hpp
    logger.cpp
    )

add_library(rubx_util ${SRC})

target_link_libraries(rubx_util
    #    ${Boost_LIBRARIES}
    )
