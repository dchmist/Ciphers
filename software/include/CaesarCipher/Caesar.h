#ifndef CAESAR_H
#define CAESAR_H
#include <functional>
#include <vector>
#include <algorithm>

namespace CaesarCipher{

    class Caesar {
    public:
        Caesar();
        Caesar(const Caesar& orig);
        virtual ~Caesar();


        uint32_t encrypt(std::vector<uint8_t> &a_publicData);
        uint32_t decrypt(std::vector<uint8_t> &a_encryptedData);

    private:
        std::function<void(uint8_t&)> _encryptor;
        std::function<void(uint8_t&)> _decryptor;
    };
}
#endif /* CAESAR_H */

