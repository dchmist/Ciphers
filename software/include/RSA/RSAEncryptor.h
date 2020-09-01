#ifndef RSAENCRYPTOR_H
#define RSAENCRYPTOR_H

#include "Types.h"
#include <vector>

namespace RSA{
    typedef long int l_int;
    
    class RSAEncryptor {
    public:
        RSAEncryptor();
        RSAEncryptor(const RSAEncryptor& orig);
        virtual ~RSAEncryptor();
        uint32_t encrypt(std::vector<l_int> &a_publicData);
        uint32_t setKey(MYTYPES::PUBKEY a_key);
    private:
        l_int _n,_e;
        
    };
}// RSA

#endif /* RSAENCRYPTOR_H */

