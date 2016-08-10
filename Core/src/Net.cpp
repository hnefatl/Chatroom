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

std::vector<unsigned char> Serialise(const uint32_t Value)
{
    std::vector<unsigned char> Buffer;
    Serialise(Value, Buffer);
    return Buffer;
}
void Serialise(const uint32_t Value, std::vector<unsigned char> &Buffer)
{
    Buffer.push_back(Value);
    Buffer.push_back(Value >> 8);
    Buffer.push_back(Value >> 16);
    Buffer.push_back(Value >> 24);
}

std::vector<unsigned char> Serialise(const int32_t Value)
{
    std::vector<unsigned char> Buffer;
    Serialise(Value, Buffer);
    return Buffer;
}
void Serialise(const int32_t Value, std::vector<unsigned char> &Buffer)
{
    Buffer.push_back(Value);
    Buffer.push_back(Value >> 8);
    Buffer.push_back(Value >> 16);
    Buffer.push_back(Value >> 24);
}

std::vector<unsigned char> Serialise(const std::string &Value)
{
    std::vector<unsigned char> Buffer;
    Serialise(Value, Buffer);
    return Buffer;
}
void Serialise(const std::string &Value, std::vector<unsigned char> &Buffer)
{
    Serialise((uint32_t)Value.size(), Buffer);
    Buffer.insert(Buffer.end(), Value.begin(), Value.end());
}


CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, uint32_t &Out)
{
    std::size_t Start = 0;
    return Deserialise(Buffer, Start, Out);
}
CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, std::size_t &Start, uint32_t &Out)
{
    if (Buffer.size() - Start < 4)
        return false;

    Out |= (Buffer[Start] << 0) | (Buffer[Start + 1] << 8) | (Buffer[Start + 2] << 16) | (Buffer[Start + 3] << 24);
    Start += 4;
    return true;
}

CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, int32_t &Out)
{
    std::size_t Start = 0;
    return Deserialise(Buffer, Start, Out);
}
CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, std::size_t &Start, int32_t &Out)
{
    if (Buffer.size() - Start < 4)
        return false;

    Out |= (Buffer[Start] << 0) | (Buffer[Start + 1] << 8) | (Buffer[Start + 2] << 16) | (Buffer[Start + 3] << 24);
    Start += 4;
    return true;
}

CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, std::string &Out)
{
    std::size_t Start = 0;
    return Deserialise(Buffer, Start, Out);
}
CORE_API bool Deserialise(const std::vector<unsigned char> &Buffer, std::size_t &Start, std::string &Out)
{
    uint32_t Length;
    if (!Deserialise(Buffer, Start, Length))
        return false;

    if (Buffer.size() - Start < Length)
        return false;

    Out = std::string(Buffer.begin() + Start, Buffer.begin() + Start + Length);
    Start += Length;
    return true;
}
