#include <iostream>

#include <Log.h>
#include <Net.h>
#include <ChatWindow.h>

int main (int argc, char *argv[])
{
    LogInit("Log.txt");

    LogWrite("Standard message");
    LogWriteWarning("Warning warning");
    LogWriteError("Error error");

    NetInit();

	ChatWindow Wnd;
	Wnd.Start([&Wnd] (const std::string &Message)
		{
			if (Message == "exit")
				Wnd.Stop();
			else
				Wnd.Print(Message);
		}
	);

	Wnd.Stop();

    NetShutdown();

    LogShutdown();
	return 0;
}
