#GTest
include_directories(${HOME_LOC}/deps/googletest-master/googletest/include)
link_directories(${HOME_LOC}/deps/googletest-master/googletest/lib)
#GMock
include_directories(${HOME_LOC}/deps/googletest-master/googlemock/include)
link_directories(${HOME_LOC}/deps/googletest-master/googlemock/lib)

find_package(Threads REQUIRED)

add_executable(CipersTest
	testMain.cpp
)
target_link_libraries(CipersTest
        CaesarCipher
#	MyAES
)
target_link_libraries(CipersTest
        Threads::Threads
        libgmock.a 
        libgmock_main.a 
        libgtest.a 
        libgtest_main.a 
)
