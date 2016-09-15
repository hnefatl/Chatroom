#include <iostream>

#include <Log.h>
#include <Net/Net.h>

#include <Data/Database.h>
#include <Data/User.h>
#include <Data/Server.h>
#include <Data/Chatroom.h>

void DbTest();

int main(int argc, char *argv[])
{
	std::cout<<argv[0]<<std::endl;
	LogInit("Log.txt");
	Net::NetInit();

	DbTest();

	Net::NetShutdown();
	LogShutdown();
	return 0;
}

void DbTest()
{
	Data::User TestUser;
	TestUser.Username = "hnefatl";
	TestUser.Password = "blahpass";

	Data::Server TestServer;
	TestServer.Name = "Seeeeerver test";
	TestServer.Address = Net::Address(AF_INET, "192.168.1.1", 25565);

	Data::Chatroom TestChatroom;
	TestChatroom.Name = "Test chatroom";
	TestChatroom.Description = "Blah blah test";
	TestChatroom.OwnerUsername = "hnefatl";
	TestChatroom.ServerAddress = Net::Address(AF_INET, "192.168.1.1", 25565);
	TestChatroom.Password = "pass";

	Data::Database d;
	if (!d.Open("Data.db"))
	{
		std::cout << "Failed to open database." << std::endl;
		return;
	}
	if (!d.InsertUser(TestUser))
	{
		std::cout << "Failed to insert User." << std::endl;
		return;
	}
	if (!d.InsertServer(TestServer))
	{
		std::cout << "Failed to insert Server." << std::endl;
		return;
	}
	if (!d.InsertChatroom(TestChatroom))
	{
		std::cout << "Failed to insert Chatroom." << std::endl;
		return;
	}

	TestUser = Data::User();
	TestServer = Data::Server();
	TestChatroom = Data::Chatroom();

	if (!d.GetUser("hnefatl", TestUser))
	{
		std::cout << "Failed to read User." << std::endl;
		return;
	}
	if (!d.GetServer(Net::Address(AF_INET, "192.168.1.1", 25565), TestServer))
	{
		std::cout << "Failed to read Server." << std::endl;
		return;
	}
	if (!d.GetChatroom("Test chatroom", TestChatroom))
	{
		std::cout << "Failed to read Chatroom." << std::endl;
		return;
	}
	return;
}
