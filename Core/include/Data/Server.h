#ifndef _SERVER_H
#define _SERVER_H

#include "Net/Address.h"

namespace Data
{
	class Server
	{
	public:
		CORE_API static const std::string CreationString;

		Net::Address Address; // Primary key
		std::string Name;
	};
}

#endif
