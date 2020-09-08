project(CiphersTest)
cmake_minimum_required(VERSION 3.4)
add_definitions( "-Wall -g3 -pthread -std=c++17" )

set(test_dir ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${test_dir}/deps/include)
link_directories(${test_dir}/deps/lib/Ciphers)
link_directories(${test_dir}/deps/lib/gtest)

find_package(Threads REQUIRED)

add_executable(CipersTest
	testMain.cpp
)
target_link_libraries(CipersTest
	des
	miniAES
	caesar
	encryptorFactory
)
target_link_libraries(CipersTest
	Threads::Threads
	gmock
	# gmock_main
	gtest
	gtest_main
)
