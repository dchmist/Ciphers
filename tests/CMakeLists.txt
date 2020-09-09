project(CiphersTest)
cmake_minimum_required(VERSION 3.4)
add_definitions( "-Wall -g3 -pthread -std=c++17" )

set(test_dir ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${test_dir}/deps/include)
include_directories(${test_dir}/deps/include/Ciphers)
link_directories(${test_dir}/deps/lib/Ciphers)
link_directories(${test_dir}/deps/lib/gtest)

find_package(Threads REQUIRED)

add_executable(CiphersTest
	testEncryptorFactory.cpp
	testDES.cpp
	testCaesar.cpp
	testMiniAES.cpp
)
target_link_libraries(CiphersTest
	des
	miniAES
	caesar
	encryptorFactory
)
target_link_libraries(CiphersTest
	Threads::Threads
	gmock
	# gmock_main
	gtest
	gtest_main
)
