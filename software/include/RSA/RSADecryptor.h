#ifndef RSADECRYPTOR_H
#define RSADECRYPTOR_H

#include "Types.h"
#include <vector>

namespace RSA{
    typedef long int l_int;
    
    class RSADecryptor {
    public:
        RSADecryptor();
        RSADecryptor(const RSADecryptor& orig);
        virtual ~RSADecryptor();
        
        uint32_t decrypt(std::vector<l_int> &a_encryptedData);
        MYTYPES::PUBKEY getPublicKey();

    private:
        l_int _n, _phi;
        l_int _keyNumber;                           // random number, needed to draw an one key pair 
        std::vector<l_int> _e, _d;
        
        uint32_t generateKeys();                    // overall this method generate stuff needed to RSA ( p, q, n, phi, key pairs) and additionally keyNumber
        bool isPrime(l_int a_var );                 // this method check that an a_var is a prime number
        void computeEandD(l_int a_e, l_int a_phi);  // this method calculate key pairs
    };
}   // RSA
#endif // RSADECRYPTOR_H

