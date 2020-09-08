#ifndef ENCRYPTION_EXCEPTION_H
#define ENCRYPTION_EXCEPTION_H

#include "ReturnTypes/ErrorCodes.h"
#include <stdexcept>
#include <string>
class EncryptionException : public std::exception{
public:
    explicit EncryptionException(const char* message, ERROR_CODE errCode);
    explicit EncryptionException(const std::string message, ERROR_CODE errCode);
    const char* what() const noexcept override;
    int errorCode() const noexcept;
private:
    std::string error;
    int errCodeVal;
};
#endif