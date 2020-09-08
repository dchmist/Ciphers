#ifndef ABSTRACT_KEY_H
#define ABSTRACT_KEY_H

#include <string>

class AbstractKey{
public:
    virtual int setInitialKey(const std::string) = 0;
    
    virtual ~AbstractKey() = default;
};
#endif