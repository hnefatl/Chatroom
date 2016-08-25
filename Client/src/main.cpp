#include <iostream>

#include <Log.h>
#include <Net/Net.h>
#include <ChatWindow.h>

int main (int argc, char *argv[])
{
    LogInit("Log.txt");

    Log("Standard message");
    LogWarning("Warning warning");
    LogError("Error error");

    Net::NetInit();

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

    Net::NetShutdown();

    LogShutdown();
	return 0;
}
