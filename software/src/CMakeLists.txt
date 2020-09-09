add_library(miniAES SHARED
        Ciphers/miniAES/MiniAES.cpp
        Ciphers/miniAES/MiniAESKey.cpp
        Ciphers/miniAES/MiniAESSBoxes.cpp
        Ciphers/miniAES/MultiplierAES.cpp
)
add_library(caesar SHARED
        Ciphers/Caesar/Caesar.cpp
        Ciphers/Caesar/CaesarKey.cpp
)
add_library(des SHARED
        Ciphers/DES/DES.cpp
        Ciphers/DES/DESKey.cpp
)
add_library(encryptorFactory SHARED
        DataConverter.cpp
        EncryptionFactory.cpp
        ReturnTypes/EncryptionException.cpp
)
target_link_libraries(encryptorFactory
	miniAES
        caesar
        des
)
add_executable(Ciphers
	main.cpp
)
target_link_libraries(Ciphers
        encryptorFactory
)