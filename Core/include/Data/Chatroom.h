#ifndef _CHATROOM_H
#define _CHATROOM_H

#include "Core.h"

#include <string>

#include <Net/Address.h>
#include <Nullable.h>

namespace Data
{
	class Chatroom
	{
	public:
		CORE_API static const std::string CreationString;

		std::string Name; // Primary key
		std::string OwnerUsername; // Foreign key
		Net::Address ServerAddress; // Foreign key
		Nullable<std::string> Password;
		Nullable<std::string> Description;
	};
}

#endif
