#ifndef _NET_H
#define _NET_H

#include "Core.h"
#include "Log.h"

#include <vector>
#include <string>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WS2tcpip.h>
#include <WinSock2.h>

#elif defined(__linux__)

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#endif

CORE_API bool NetInit();
CORE_API void NetShutdown();

CORE_API uint32_t HtoN(const uint32_t i);
CORE_API int32_t HtoN(const int32_t i);

CORE_API uint32_t NtoH(const uint32_t i);
CORE_API int32_t NtoH(const int32_t i);


CORE_API std::vector<unsigned char> GetBytes(const uint32_t Value);
CORE_API void GetBytes(const uint32_t Value, std::vector<unsigned char> &Buffer);

CORE_API std::vector<unsigned char> GetBytes(const int32_t Value);
CORE_API void GetBytes(const int32_t Value, std::vector<unsigned char> &Buffer);

CORE_API std::vector<unsigned char> GetBytes(const std::string &Value);
CORE_API void GetBytes(const std::string &Value, std::vector<unsigned char> &Buffer);


CORE_API uint32_t GetUInt32(const std::vector<unsigned char> &Buffer);
CORE_API uint32_t GetUInt32(const std::vector<unsigned char> &Buffer, std::size_t &Start);

CORE_API int32_t GetInt32(const std::vector<unsigned char> &Buffer);
CORE_API int32_t GetInt32(const std::vector<unsigned char> &Buffer, std::size_t &Start);

CORE_API std::string GetString(const std::vector<unsigned char> &Buffer);
CORE_API std::string GetString(const std::vector<unsigned char> &Buffer, std::size_t &Start);

#endif
