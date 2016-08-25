#include <iostream>

#include <Log.h>
#include <Net.h>

#include <Data/Database.h>

void DbTest();

int main(int argc, char *argv[])
{
	LogInit("Log.txt");
	NetInit();

	DbTest();

	NetShutdown();
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
