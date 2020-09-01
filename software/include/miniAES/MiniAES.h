#ifndef MYAES_H
#define MYAES_H

#include <vector>
#include "Types.h"


//TODO
namespace AES{
    
    typedef std::vector<uint8_t> ByteArray;
    typedef uint32_t Result;
    typedef uint8_t Byte;
    enum AesType{
        AES_128,
        AES_192,
        AES_256
    };
    
    class MyAES {
    public:
        MyAES();
        MyAES(const MyAES& orig);
        virtual ~MyAES();
        
        Result setSecretKey(const ByteArray* a_key);
        Result ecryptText(const ByteArray* a_publicText);
        Result decryptText(const ByteArray* a_encryptedText);
    private:
        ByteArray _secretKey;
        AesType _aesType;
        Byte _intermediateKeys[60][4];
        
        void generate_intermediate_keys();
    };
}
#endif /* MYAES_H */

