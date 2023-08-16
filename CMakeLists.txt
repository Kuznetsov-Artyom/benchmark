CMAKE_MINIMUM_REQUIRED(VERSION 3.25.0)

project(benchmark)

include_directories(./headers)
include_directories(./sources)

# Timer
set(TIMER_HDR headers/timer.hpp)
set(TIMER_SRC sources/timer.cpp)
add_library(timer_lib ${TIMER_HDR} ${TIMER_SRC})

add_executable(benchmark main.cpp)
target_link_libraries(benchmark timer_lib)