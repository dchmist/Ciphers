#ifndef ABSTRACT_ENCRYPTION_H
#define ABSTRACT_ENCRYPTION_H

#include <cstdint>
#include <vector>

class AbstractEncryption{
public:
    virtual std::vector<uint8_t> encode(const std::vector<uint8_t>&) const = 0;
    virtual std::vector<uint8_t> decode(const std::vector<uint8_t>&) const = 0;
};

#endif