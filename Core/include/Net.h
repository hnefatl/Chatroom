#ifndef _NET_H
#define _NET_H

#include "Core.h"
#include "Log.h"

CORE_API bool NetInit();
CORE_API void NetShutdown();

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WS2tcpip.h>
#include <WinSock2.h>

bool NetInit()
{
	WSAData Version;
	int Result = WSAStartup(MAKEWORD(2, 0), &Version);
	if (Result != 0)
	{
        LogWriteError("Failed to start WSA, code " + Result);
		return false;
	}

	LogWrite("WSA started");
}
void NetShutdown()
{
	WSACleanup();
	LogWrite("WSA stopped");
}

#else defined(__linux__)

#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

bool NetInit()
{
    return true;
}
void NetShutdown()
{
}

#endif

#endif
