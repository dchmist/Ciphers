#ifndef CAESAR_KEY_H
#define CAESAR_KEY_H

#include "Abstractions/AbstractKey.h"

namespace CaesarCipher{
    class CaesarKey : public AbstractKey{
    public:
        int setInitialKey(const std::string) override;
        int getShift() const;
    private:
        int shift=0;
    };
}
#endif