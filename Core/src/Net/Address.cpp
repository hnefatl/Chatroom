#include "Net/Address.h"

#include <sstream>

namespace Net
{
	Address::Address()
	{
		Addr = nullptr;
		Port = 0;
		Family = AF_UNSPEC;
	}
	Address::Address(const sockaddr_in Address, const unsigned short Port)
	{
		this->Addr = (sockaddr_storage *)new sockaddr_in(Address);
		this->Port = Port;
		Family = AF_INET;
	}
	Address::Address(const sockaddr_in6 Address, const unsigned short Port)
	{
		this->Addr = (sockaddr_storage *)new sockaddr_in6(Address);
		this->Port = Port;
		Family = AF_INET6;
	}
	Address::Address(const unsigned short Family, const std::string &IP, const unsigned short Port)
	{
		this->Family = Family;
		this->Port = Port;
		if (IPv4())
			inet_pton(AF_INET, IP.c_str(), &((sockaddr_in *)Addr)->sin_addr);
		else
			inet_pton(AF_INET6, IP.c_str(), &((sockaddr_in6 *)Addr)->sin6_addr);
	}
	Address::~Address()
	{
		delete Addr;
		Addr = nullptr;
	}

	std::string Address::GetPrintableIP() const
	{
		if(Addr == nullptr)
			throw std::exception();

		char Buffer[INET6_ADDRSTRLEN];
		inet_ntop(Family, Addr, Buffer, INET6_ADDRSTRLEN);
		return std::string(Buffer);
	}
	std::string Address::GetPrintableAddress() const
	{
		if(Addr == nullptr)
			throw std::exception();

		std::stringstream s;
		char Buffer[INET6_ADDRSTRLEN];
		if (IPv4())
		{
			inet_ntop(AF_INET, &((sockaddr_in *)Addr)->sin_addr, Buffer, INET_ADDRSTRLEN);
			s << Buffer << ":" << Port;
		}
		else
		{
			inet_ntop(AF_INET6, &((sockaddr_in6 *)Addr)->sin6_addr, Buffer, INET6_ADDRSTRLEN);
			s << "[" << Buffer << "]" << ":" << Port;
		}

		return s.str();
	}

	bool Address::IPv4() const
	{
		if(Addr == nullptr)
			throw std::exception();

		return Family == AF_INET;
	}
	bool Address::IPv6() const
	{
		if(Addr == nullptr)
			throw std::exception();

		return Family == AF_INET6;
	}
}
