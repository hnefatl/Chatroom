#include "Data/User.h"

namespace Data
{
	extern const std::string User::CreationString =	"CREATE TABLE User ("
													"  Username TEXT NOT NULL,"
													"  Password TEXT NOT NULL,"
													""
													"  PRIMARY KEY (Username)"
													");";
}
