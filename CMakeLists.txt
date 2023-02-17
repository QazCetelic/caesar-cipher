cmake_minimum_required(VERSION 3.0)

project(caesar-cipher LANGUAGES C)

add_executable(caesar-cipher main.c)

install(TARGETS caesar-cipher RUNTIME DESTINATION bin)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
