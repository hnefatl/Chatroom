#include "Net/Address.h"

#include <sstream>
#include <cstring>

namespace Net
{
	Address::Address()
	{
		Port = 0;
		Family = AF_UNSPEC;
	}
	Address::Address(const sockaddr_in &Address, const unsigned short Port)
	{
		memset(&Addr, 0, sizeof(Addr));
		memcpy(&Addr, &Address, sizeof(Address));
		this->Port = Port;
		Family = AF_INET;
	}
	Address::Address(const sockaddr_in6 &Address, const unsigned short Port)
	{
		memset(&Addr, 0, sizeof(Addr));
		memcpy(&Addr, &Address, sizeof(Address));
		this->Port = Port;
		Family = AF_INET6;
	}

	bool Address::Load(const unsigned short Family, const std::string &IP, const unsigned short Port)
	{
		this->Family = Family;
		this->Port = Port;

		memset(&Addr, 0, sizeof(Addr));
		int Err;
		if (IPv4())
			Err = inet_pton(AF_INET, IP.c_str(), &((sockaddr_in *)&Addr)->sin_addr);
		else
			Err = inet_pton(AF_INET6, IP.c_str(), &((sockaddr_in6 *)&Addr)->sin6_addr);

		if (Err != 1)
			return false;

		return true;
	}

	std::string Address::GetPrintableIP() const
	{
		char Buffer[INET6_ADDRSTRLEN];
		if (IPv4())
			inet_ntop(Family, &((sockaddr_in *)&Addr)->sin_addr, Buffer, INET_ADDRSTRLEN);
		else
			inet_ntop(Family, &((sockaddr_in6 *)&Addr)->sin6_addr, Buffer, INET6_ADDRSTRLEN);
		std::string Result = std::string(Buffer);
		return Result;
	}
	std::string Address::GetPrintableAddress() const
	{
		std::stringstream s;
		char Buffer[INET6_ADDRSTRLEN];
		if (IPv4())
		{
			inet_ntop(AF_INET, &((sockaddr_in *)&Addr)->sin_addr, Buffer, INET_ADDRSTRLEN);
			s << Buffer << ":" << Port;
		}
		else
		{
			inet_ntop(AF_INET6, &((sockaddr_in6 *)&Addr)->sin6_addr, Buffer, INET6_ADDRSTRLEN);
			s << "[" << Buffer << "]" << ":" << Port;
		}

		return s.str();
	}

	bool Address::IPv4() const
	{
		return Family == AF_INET;
	}
	bool Address::IPv6() const
	{
		return Family == AF_INET6;
	}
}
