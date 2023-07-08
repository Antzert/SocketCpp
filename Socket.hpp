#ifndef __SOCKET__HPP__
	#define __SOCKET__HPP__

	#ifdef WIN32
		#include <winsock2.h> 
	#elif defined (linux)
		#include <sys/types.h>
		#include <sys/socket.h>
		#include <netinet/in.h>
		#include <arpa/inet.h>
		#include <unistd.h>
		#include <netdb.h>
		#define INVALID_SOCKET -1
		#define SOCKET_ERROR -1
		#define closesocket(s) close(s)
		#define h_addr h_addr_list[0]
		typedef int SOCKET;
		typedef struct sockaddr_in SOCKADDR_IN;
		typedef struct sockaddr SOCKADDR;
		typedef struct in_addr IN_ADDR;
	#else
		#error not defined for this platform
	#endif

	#include <string>
	using namespace std::string_literals;

	class Socket
	{
		public:
			Socket();
			~Socket();
			void Create(int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);
			void Destroy();
			void Bind(unsigned short port, bool forcedBind = false);
			void Listen(int connectionRefused);
			void Accept(Socket& client);
			void Connect(std::string hostname, unsigned short port);
			template <typename T, size_t dataSize = 0>
			void Send(T& buffer);
			template <typename T, size_t dataSize = 0>
			void Recv(T& buffer);
		private:
			SOCKET sock;
			bool isCreate;
			int domain;
			int type;
			int protocol;
			std::string hostname;
	};

	#include "Socket.tpp"

#endif