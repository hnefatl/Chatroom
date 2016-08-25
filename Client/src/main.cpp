#include <iostream>

#include <Log.h>
#include <Net.h>
#include <ChatWindow.h>

int main (int argc, char *argv[])
{
    LogInit("Log.txt");

    Log("Standard message");
    LogWarning("Warning warning");
    LogError("Error error");

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
