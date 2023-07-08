#include "SocketException.hpp"
#include <cstring>
#include <iostream>

template <typename T, size_t dataSize = 0>
void Socket::Send(T& buffer)
{
    std::cout << "Envoie de la donnée\n";
    if(send(this->sock, &buffer, dataSize == 0?sizeof(T):dataSize, 0) < 0)
        throw socketException("Erreur dans la fonction send() : "s + strerror(errno));
}
template <typename T, size_t dataSize = 0>
void Socket::Recv(T& buffer)
{
    std::cout << "Accepte la donnée\n";
    if(recv(this->sock, &buffer, dataSize == 0?sizeof(T):dataSize, 0) < 0)
        throw socketException("Erreur dans la fonction recv() : "s + strerror(errno));
}