#ifndef DES_CODER_H
#define DES_CODER_H

#include "Types.h"
#include "AbstractEncryption.h"

namespace DESCipher{
    class DES : public AbstractEncryption{
    public:
        DES();

        std::vector<uint8_t> encode(const std::vector<uint8_t>&) const override;
        std::vector<uint8_t> decode(const std::vector<uint8_t>&) const override;

        
    private:

    };
}// DES

#endif /* DES_H */