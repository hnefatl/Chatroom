#ifndef _NET_H
#define _NET_H

#include "Core.h"

#include <vector>
#include <string>

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WS2tcpip.h>
#include <WinSock2.h>

#elif defined(__linux__)

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef int SOCKET;

#endif

namespace Net
{
	CORE_API bool NetInit();
	CORE_API void NetShutdown();

	CORE_API uint32_t HtoN(const uint32_t i);
	CORE_API int32_t HtoN(const int32_t i);

	CORE_API uint32_t NtoH(const uint32_t i);
	CORE_API int32_t NtoH(const int32_t i);


	CORE_API void Serialise(const uint32_t Value, std::vector<unsigned char> &Buffer);

	CORE_API void Serialise(const int32_t Value, std::vector<unsigned char> &Buffer);

	CORE_API void Serialise(const bool Value, std::vector<unsigned char> &Buffer);

	CORE_API void Serialise(const std::string &Value, std::vector<unsigned char> &Buffer);


	CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, uint32_t &Out);
	CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, std::size_t &Start, uint32_t &Out);

	CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, int32_t &Out);
	CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, std::size_t &Start, int32_t &Out);

	CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, bool &Out);
	CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, std::size_t &Start, bool &Out);

	CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, std::string &Out);
	CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, std::size_t &Start, std::string &Out);
}

#endif
