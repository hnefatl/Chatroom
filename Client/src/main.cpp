#include <iostream>

#include <Log.h>

int main (int argc, char *argv[])
{
    LogInit("Out.txt");

    LogWrite("Standard message");
    LogWriteWarning("Warning warning");
    LogWriteError("Error error");

    LogShutdown();
	return 0;
}
