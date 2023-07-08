#include "Socket.hpp"
#include "SocketException.hpp"
#include <iostream>
#include <cstring>


Socket::Socket()
{
    errno = 0;
    this->isCreate = false;
}
Socket::~Socket()
{
    std::cout << "Destruction du socket\n";
    closesocket(this->sock);
    this->isCreate = false;
    #ifdef WIN32
        WSACleanup();
    #endif
}
void Socket::Create(int domain, int type, int protocol)
{
    this->domain = domain;
    this->type = type;
    this->protocol = protocol;
    if(this->isCreate)
        this->Destroy();
    std::cout << "Creation du socket\n";
    this->isCreate = true;
    #ifdef WIN32
        WSADATA wsa;
        int err = WSAStartup(MAKEWORD(2, 2), &wsa);
        if(err < 0)
        {
            puts("WSAStartup failed !");
            exit(EXIT_FAILURE);
        }
    #endif
    this->sock = socket(domain, type, protocol);
    if(this->sock == INVALID_SOCKET)
        throw socketException("Erreur dans la fonction socket() : "s + strerror(errno));
}
void Socket::Destroy()
{
    this->~Socket();
}
void Socket::Bind(unsigned short port, bool forcedBind)
{
    std::cout << "Bind du socket\n";
    int yes = 1; 
    if(forcedBind)
    {
        if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
            throw socketException("Erreur dans la fonction setsockopt() : "s + strerror(errno));
    }
    SOCKADDR_IN sin{};
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    if(bind(this->sock, (SOCKADDR *) &sin, sizeof(sin)) == SOCKET_ERROR)
        throw socketException("Erreur dans la fonction bind() : "s + strerror(errno));

}
void Socket::Listen(int connectionRefused)
{
    std::cout << "Listen du socket\n";
    if(listen(this->sock, connectionRefused) == SOCKET_ERROR)
        throw socketException("Erreur dans la fonction listen() : "s + strerror(errno));
}
void Socket::Accept(Socket& client)
{
    std::cout << "Accept du socket\n";
    SOCKADDR_IN csin{};
    socklen_t sinsize = sizeof(csin);
    client.sock = accept(this->sock, (SOCKADDR *)&csin, &sinsize);

    if(client.sock == INVALID_SOCKET)
        throw socketException("Erreur dans la fonction accept() : "s + strerror(errno));
}
void Socket::Connect(std::string hostname, unsigned short port)
{
    std::cout << "Connect du socket\n";
    struct hostent* hostinfo = NULL;
    SOCKADDR_IN sin{};

    hostinfo = gethostbyname(hostname.c_str());
    if(hostinfo == NULL)
        throw socketException("Unknown host "s + hostname);

    sin.sin_addr = *(IN_ADDR *)hostinfo->h_addr;
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;

    if(connect(this->sock, (SOCKADDR*)&sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
        throw socketException("Erreur dans la fonction connect() : "s + strerror(errno));
}