project(Ciphers)
cmake_minimum_required(VERSION 3.4)
add_definitions( "-Wall -g3 -pthread -std=c++17" )

set(HOME_LOC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${HOME_LOC}/software/include)

add_subdirectory(software)

