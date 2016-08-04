#include <iostream>

#include <Log.h>
#include <Net.h>

int main (int argc, char *argv[])
{
    LogInit("Log.txt");

    LogWrite("Standard message");
    LogWriteWarning("Warning warning");
    LogWriteError("Error error");

    NetInit();



    NetShutdown();

    LogShutdown();
	return 0;
}
