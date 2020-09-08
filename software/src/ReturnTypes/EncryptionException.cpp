#include "ReturnTypes/EncryptionException.h"

EncryptionException::EncryptionException(const char* message, ERROR_CODE errCode):
error(message),
errCodeVal(static_cast<int>(errCode))
{

}
EncryptionException::EncryptionException(const std::string message, ERROR_CODE errCode):
error(message),
errCodeVal(static_cast<int>(errCode))
{

}
const char* EncryptionException::what() const noexcept
{
    return error.c_str();
}
int EncryptionException::errorCode() const noexcept
{
    return errCodeVal;
}