CMAKE_MINIMUM_REQUIRED(VERSION 3.25.0)

project(benchmark)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./headers)
include_directories(./sources)

add_executable(benchmark main.cpp)
