#include <iostream>

#include <Log.h>
#include <Net/Net.h>

#include <Data/Database.h>

void DbTest();

int main(int argc, char *argv[])
{
	LogInit("Log.txt");
	Net::NetInit();

	DbTest();

	Net::NetShutdown();
	LogShutdown();
	return 0;
}

void DbTest()
{
	Data::Database d;
	if (!d.Open("Data.db"))
	{
		std::cout << "Failed to open database." << std::endl;
		return;
	}
}
