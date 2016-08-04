#include <iostream>

#include <Log.h>
#include <Net.h>

int main (int argc, char *argv[])
{
    LogInit("Log.txt");
    NetInit();



    NetShutdown();
    LogShutdown();
	return 0;
}
