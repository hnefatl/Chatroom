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
	Wnd.Start();

	while (true)
	{
		std::string Input = Wnd.UserInput.Pop();
		if (Input == "exit")
			break;
		Wnd.Print(Input);
	}

	Wnd.Stop();

    Net::NetShutdown();

    LogShutdown();
	return 0;
}
