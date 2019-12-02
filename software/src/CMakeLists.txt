add_executable(Ciphers
	main.cpp
)
target_link_libraries(Ciphers
#	MyAES
        CaesarCipher
        RSA
)

