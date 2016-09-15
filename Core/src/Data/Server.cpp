#include "Data/Server.h"

namespace Data
{
	const std::string Server::CreationString =	"CREATE TABLE Server ("
												"  IP TEXT NOT NULL,"
												"  Port INTEGER NOT NULL,"
												"  Family INTEGER NOT NULL,"
												"  Name TEXT NOT NULL,"
												""
												"  PRIMARY KEY (IP, Port)"
												");";
}
