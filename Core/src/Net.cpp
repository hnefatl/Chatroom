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

	return true;
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

void Serialise(const uint32_t Value, std::vector<unsigned char> &Buffer)
{
    Buffer.push_back(Value);
    Buffer.push_back(Value >> 8);
    Buffer.push_back(Value >> 16);
    Buffer.push_back(Value >> 24);
}

void Serialise(const int32_t Value, std::vector<unsigned char> &Buffer)
{
    Buffer.push_back(Value);
    Buffer.push_back(Value >> 8);
    Buffer.push_back(Value >> 16);
    Buffer.push_back(Value >> 24);
}

void Serialise(const bool Value, std::vector<unsigned char> &Buffer)
{
    Buffer.push_back(Value ? 1 : 0);
}

void Serialise(const std::string &Value, std::vector<unsigned char> &Buffer)
{
    Serialise((uint32_t)Value.size(), Buffer);
    Buffer.insert(Buffer.end(), Value.begin(), Value.end());
}


bool Deserialise(const std::vector<unsigned char> &Buffer, uint32_t &Out)
{
    std::size_t Start = 0;
    return Deserialise(Buffer, Start, Out);
}
bool Deserialise(const std::vector<unsigned char> &Buffer, std::size_t &Start, uint32_t &Out)
{
    if (Buffer.size() - Start < 4)
        return false;

    Out |= (Buffer[Start] << 0) | (Buffer[Start + 1] << 8) | (Buffer[Start + 2] << 16) | (Buffer[Start + 3] << 24);
    Start += 4;
    return true;
}

bool Deserialise(const std::vector<unsigned char> &Buffer, int32_t &Out)
{
    std::size_t Start = 0;
    return Deserialise(Buffer, Start, Out);
}
bool Deserialise(const std::vector<unsigned char> &Buffer, std::size_t &Start, int32_t &Out)
{
    if (Buffer.size() - Start < 4)
        return false;

    Out |= (Buffer[Start] << 0) | (Buffer[Start + 1] << 8) | (Buffer[Start + 2] << 16) | (Buffer[Start + 3] << 24);
    Start += 4;
    return true;
}

bool Deserialise(const std::vector<unsigned char> &Buffer, bool &Out)
{
    std::size_t Start = 0;
    return Deserialise(Buffer, Start, Out);
}
bool Deserialise(const std::vector<unsigned char> &Buffer, std::size_t &Start, bool &Out)
{
    if (Buffer.size() - Start < 1)
        return false;

    Out = Buffer[Start] != 0 ? true : false;
    Start += 1;
    return true;
}

bool Deserialise(const std::vector<unsigned char> &Buffer, std::string &Out)
{
    std::size_t Start = 0;
    return Deserialise(Buffer, Start, Out);
}
bool Deserialise(const std::vector<unsigned char> &Buffer, std::size_t &Start, std::string &Out)
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
