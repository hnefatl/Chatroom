#ifndef _DATABASE_H
#define _DATABASE_H

#include <string>
#include <vector>
#include <mutex>

#include <sqlite3.h>

#include <Data/User.h>
#include <Data/Chatroom.h>
#include <Data/Server.h>
#include <Net/Address.h>
#include <Nullable.h>
#include <Data/Statement.h>

namespace Data
{
	class Database
	{
	protected:
		sqlite3 *Inner;

		bool _GetUser(Statement &s, User &Out);
		bool _GetServer(Statement &s, Server &Out);
		bool _GetChatroom(Statement &s, Chatroom &Out);

	public:
		CORE_API Database();
		CORE_API ~Database();

		CORE_API bool Open(const std::string &Path);
		CORE_API void Close();

		CORE_API bool GetUsers(std::vector<User> &Users);
		CORE_API bool GetUser(const std::string &Username, User &Out);

		CORE_API bool GetServers(std::vector<Server> &Servers);
		CORE_API bool GetServer(const Net::Address Address, Server &Out);

		CORE_API bool GetChatroom(const std::string &Name, Chatroom &Out);
		CORE_API bool GetChatrooms(std::vector<Chatroom> &Chatrooms);
		CORE_API bool GetChatrooms(const Server &Host, std::vector<Chatroom> &Out);
		CORE_API bool GetChatrooms(const User &Owner, std::vector<Chatroom> &Out);

		CORE_API bool InsertUser(const User &User);
		CORE_API bool InsertServer(const Server &Server);
		CORE_API bool InsertChatroom(const Chatroom &Chatroom);
	};
}

#endif
