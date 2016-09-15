#ifndef _USER_H
#define _USER_H

#include "Core.h"

#include <string>

namespace Data
{
	class CORE_API User
	{
	public:
		static const std::string CreationString;

		std::string Username; // Primary key
		std::string Password;
	};

	const std::string User::CreationString =	"CREATE TABLE User ("
												"  Username TEXT NOT NULL,"
												"  Password TEXT NOT NULL,"
												""
												"  PRIMARY KEY (Username)"
												");";
}

#endif
