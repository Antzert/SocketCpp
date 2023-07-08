#include "SocketException.hpp"
#include <string.h>
#include <stdlib.h>

socketException::socketException(std::string message) : message(message)
{

}
const char* socketException::what() const noexcept
{
    return this->message.c_str();
}