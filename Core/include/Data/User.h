#ifndef _USER_H
#define _USER_H

#include "Core.h"

#include <string>

namespace Data
{
	class User
	{
	public:
		CORE_API static const std::string CreationString;

		std::string Username; // Primary key
		std::string Password;
	};
}

#endif
