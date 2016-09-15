#include "Data/Chatroom.h"

namespace Data
{
	extern const std::string Chatroom::CreationString =	"CREATE TABLE Chatroom ("
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
