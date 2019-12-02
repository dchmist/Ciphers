cmake_minimum_required(VERSION 3.4)

set(HOME_LOC ${CMAKE_CURRENT_SOURCE_DIR})

add_definitions( "-Wall -g3 -pthread -std=c++11" )

include_directories(${HOME_LOC}/software/include)
include_directories(${HOME_LOC}/software/DES/include)

#CaesarCipher
include_directories(${HOME_LOC}/deps/CaesarCipher/include)
link_directories(${HOME_LOC}/deps/CaesarCipher/lib)
#RSA
include_directories(${HOME_LOC}/deps/RSA/include)
link_directories(${HOME_LOC}/deps/RSA/lib)

add_subdirectory(software)
#add_subdirectory(tests)
