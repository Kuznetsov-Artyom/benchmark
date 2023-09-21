CMAKE_MINIMUM_REQUIRED(VERSION 3.25.0)

project(
    benchmark
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./headers)
include_directories(./sources)

add_executable(${PROJECT_NAME} main.cpp)
