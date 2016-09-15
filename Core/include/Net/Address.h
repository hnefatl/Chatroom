#ifndef _ADDRESS_H
#define _ADDRESS_H

#include "Net.h"

#include <string>

namespace Net
{
	class Address
	{
	public:
		sockaddr_storage *Addr;
		unsigned short Family;
		unsigned short Port;

		Address();
		Address(const sockaddr_in Address, const unsigned short Port);
		Address(const sockaddr_in6 Address, const unsigned short Port);
		Address(const unsigned short Family, const std::string &IP, const unsigned short Port);
		~Address();

		std::string GetPrintableIP() const;
		std::string GetPrintableAddress() const;

		bool IPv4() const;
		bool IPv6() const;
	};
}

#endif
