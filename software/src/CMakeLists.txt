add_library(miniAES SHARED
        Ciphers/miniAES/MiniAES.cpp
        Ciphers/miniAES/MultiplierAES.cpp
)
add_library(caesar SHARED
        Ciphers/Caesar/Caesar.cpp
)
add_library(des SHARED
        Ciphers/DES/DES.cpp
        Ciphers/DES/DESKey.cpp
)
add_executable(Ciphers
	main.cpp
        DataConverter.cpp
        EncryptionFactory.cpp
)
target_link_libraries(Ciphers
	miniAES
        caesar
        des
)