#include "Net.h"

#ifdef _WIN32

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

#elif defined(__linux__)

bool NetInit()
{
    return true;
}
void NetShutdown()
{
}

#endif

uint32_t HtoN(const uint32_t i)
{
    return htonl(i);
}
int32_t HtoN(const int32_t i)
{
    return (int32_t)HtoN((uint32_t)i);
}

uint32_t NtoH(const uint32_t i)
{
    return ntohl(i);
}
int32_t NtoH(const int32_t i)
{
    return (int32_t)NtoH((uint32_t)i);
}

std::vector<unsigned char> GetBytes(const uint32_t Value)
{
    std::vector<unsigned char> Buffer;
    GetBytes(Value, Buffer);
    return Buffer;
}
void GetBytes(const uint32_t Value, std::vector<unsigned char> &Buffer)
{
    Buffer.reserve(Buffer.size() + sizeof(Value));
    Buffer.push_back(Value & 0xFF);
    Buffer.push_back(Value & 0xFF00);
    Buffer.push_back(Value & 0xFF0000);
    Buffer.push_back(Value & 0xFF000000);
}

std::vector<unsigned char> GetBytes(const int32_t Value)
{
    return GetBytes((uint32_t)Value);
}
void GetBytes(const int32_t Value, std::vector<unsigned char> &Buffer)
{
    GetBytes((uint32_t)Value, Buffer);
}

std::vector<unsigned char> GetBytes(const std::string &Value)
{
    std::vector<unsigned char> Buffer;
    GetBytes(Value, Buffer);
    return Buffer;
}
void GetBytes(const std::string &Value, std::vector<unsigned char> &Buffer)
{
    GetBytes((uint32_t)Value.size(), Buffer);
    Buffer.insert(Buffer.end(), Value.begin(), Value.end());
}


uint32_t GetUInt32(const std::vector<unsigned char> &Buffer)
{

}
uint32_t GetUInt32(const std::vector<unsigned char> &Buffer, std::size_t &Start);

int32_t GetInt32(const std::vector<unsigned char> &Buffer);
int32_t GetInt32(const std::vector<unsigned char> &Buffer, std::size_t &Start);

std::string GetString(const std::vector<unsigned char> &Buffer);
std::string GetString(const std::vector<unsigned char> &Buffer, std::size_t &Start);
