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

	const std::string Chatroom::CreationString =	"CREATE TABLE Chatroom ("
													"  Name TEXT NOT NULL,"
													"  OwnerUsername TEXT NOT NULL,"
													"  ServerIP TEXT NOT NULL,"
													"  ServerPort INTEGER NOT NULL,"
													"  ServerFamily INTEGER NOT NULL,"
													"  Password TEXT,"
													"  Description TEXT,"
													""
													"  PRIMARY KEY (Name),"
													"  FOREIGN KEY (OwnerUsername) REFERENCES User,"
													"  FOREIGN KEY (ServerIP, ServerPort) REFERENCES Server"
													");";
}

#endif
