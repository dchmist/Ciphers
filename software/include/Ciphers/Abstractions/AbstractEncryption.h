#ifndef ABSTRACT_ENCRYPTION_H
#define ABSTRACT_ENCRYPTION_H

#include "Abstractions/AbstractKey.h"
#include <cstdint>
#include <vector>
#include <memory>

class AbstractEncryption{
public:
    AbstractEncryption() = default;
    virtual std::vector<uint8_t> encode(const std::vector<uint8_t>&) const = 0;
    virtual std::vector<uint8_t> decode(const std::vector<uint8_t>&) const = 0;

    virtual void setKey(const std::shared_ptr<AbstractKey>&) = 0;

    virtual ~AbstractEncryption() = default;
};
#endif