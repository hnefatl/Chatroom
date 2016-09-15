#ifndef _ADDRESS_H
#define _ADDRESS_H

#include "Core.h"
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

		CORE_API Address();
		CORE_API Address(const sockaddr_in Address, const unsigned short Port);
		CORE_API Address(const sockaddr_in6 Address, const unsigned short Port);
		CORE_API Address(const unsigned short Family, const std::string &IP, const unsigned short Port);
		CORE_API ~Address();

		CORE_API std::string GetPrintableIP() const;
		CORE_API std::string GetPrintableAddress() const;

		CORE_API bool IPv4() const;
		CORE_API bool IPv6() const;

		CORE_API void operator =(const Address &Rhs);
	};
}

#endif
