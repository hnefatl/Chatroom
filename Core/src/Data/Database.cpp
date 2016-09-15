#include "Data/Database.h"

#include <Log.h>

namespace Data
{
	Database::Database()
	{
		Inner = nullptr;
	}
	Database::~Database()
	{
		Close();
	}

	bool Database::Open(const std::string &Path)
	{
		if (Inner != nullptr)
			Close();

		int Err;
		if ((Err = sqlite3_initialize()) != SQLITE_OK)
			return LogError(sqlite3_errstr(Err), false);

		if (Err = sqlite3_open_v2(Path.c_str(), &Inner, SQLITE_OPEN_READWRITE, nullptr) != SQLITE_OK)
		{
			if (Err = sqlite3_open_v2(Path.c_str(), &Inner, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr) != SQLITE_OK)
				return LogError(sqlite3_errstr(Err), false);

			std::vector<std::string> TableStrings;
			TableStrings.push_back(User::CreationString);
			TableStrings.push_back(Server::CreationString);
			TableStrings.push_back(Chatroom::CreationString);

			for (unsigned int x = 0; x < TableStrings.size(); x++)
			{
				Statement s;
				if (!s.Prepare(Inner, TableStrings[x]))
					return false;
				if (!s.Execute())
					return false;
			}
		}
		return true;
	}
	void Database::Close()
	{
		sqlite3_close(Inner);
		Inner = nullptr;
	}

	bool Database::_GetUser(Statement &s, User &Out)
	{
		Nullable<std::string> Username;
		Nullable<std::string> Password;

		if (!s.GetString("Username", Username) || !s.GetString("Password", Password))
			return false;

		if (Username.Null || Password.Null)
			return false;

		Out.Username = Username.Value;
		Out.Password = Password.Value;
		return true;
	}
	bool Database::GetUser(const std::string &Username, User &Out)
	{
		const std::string Query = "SELECT * FROM User WHERE Username = :Username";

		Statement s;
		if (!s.Prepare(Inner, Query))
			return false;

		if (!s.Bind(":Username", Username.c_str()))
			return false;

		if (!s.Execute())
			return false;

		if (!_GetUser(s, Out))
			return false;

		return true;
	}
	bool Database::GetUsers(std::vector<User> &Users)
	{
		Users.clear();
		const std::string Query = "SELECT * FROM User";

		Statement s;
		if (!s.Prepare(Inner, Query))
			return false;

		bool MoreData = true;
		while (MoreData)
		{
			if (!s.Step(MoreData))
				return false;

			User u;
			if (!_GetUser(s, u))
				return false;
			Users.push_back(u);
		}

		return true;
	}


	bool Database::_GetServer(Statement &s, Server &Out)
	{
		Nullable<std::string> Name;
		Nullable<int> Family;
		Nullable<std::string> IP;
		Nullable<int> Port;

		if (!s.GetString("Name", Name) || !s.GetInt("Family", Family) || !s.GetString("IP", IP) || !s.GetInt("Port", Port))
			return false;

		if (Family.Null || IP.Null || Port.Null || Name.Null)
			return false;

		Out.Address = Net::Address(Family.Value, IP.Value, Port.Value);
		Out.Name = Name.Value;

		return true;
	}
	bool Database::GetServer(const Net::Address Address, Server &Out)
	{
		const std::string Query = "SELECT * FROM Server WHERE Family = :Family AND IP = :IP AND Port = :Port";

		Statement s;
		if (!s.Prepare(Inner, Query))
			return false;

		if (!s.Bind(":Family", Address.Family) || !s.Bind(":IP", Address.GetPrintableIP()) || !s.Bind(":Port", Address.Port))
			return false;

		if (!s.Execute())
			return false;

		if (!_GetServer(s, Out))
			return false;

		return true;
	}
	bool Database::GetServers(std::vector<Server> &Servers)
	{
		Servers.clear();
		const std::string Query = "SELECT * FROM Server";

		Statement s;
		if (!s.Prepare(Inner, Query))
			return false;

		bool MoreData = true;
		while (MoreData)
		{
			if (!s.Step(MoreData))
				return false;

			Server Out;
			if (!_GetServer(s, Out))
				return false;
			Servers.push_back(Out);
		}

		return true;
	}

	bool Database::_GetChatroom(Statement &s, Chatroom &Out)
	{
		Nullable<std::string> Name;
		Nullable<std::string> OwnerUsername;
		Nullable<std::string> Password;
		Nullable<std::string> Description;
		Nullable<int> ServerFamily;
		Nullable<std::string> ServerIP;
		Nullable<int> ServerPort;

		if (!s.GetString("Name", Name) || !s.GetString("OwnerUsername", OwnerUsername) || !s.GetString("Password", Password) ||
				!s.GetString("Description", Description) || !s.GetInt("ServerFamily", ServerFamily) ||
				!s.GetString("ServerIP", ServerIP) || !s.GetInt("ServerPort", ServerPort))
			return false;

		if (Name.Null || OwnerUsername.Null || ServerIP.Null || ServerFamily.Null || ServerPort.Null)
			return false;

		Out.Name = Name.Value;
		Out.OwnerUsername = OwnerUsername.Value;
		Out.ServerAddress = Net::Address(ServerFamily.Value, ServerIP.Value, ServerPort.Value);
		Out.Password = Password;
		Out.Description = Description;

		return true;
	}
	bool Database::GetChatroom(const std::string &Name, Chatroom &Out)
	{
		const std::string Query = "SELECT * FROM Chatroom WHERE Name = :Name:";

		Statement s;
		if (!s.Prepare(Inner, Query))
			return false;

		if (!s.Bind(":Name", Name))
			return false;

		if (!s.Execute())
			return false;

		if (!_GetChatroom(s, Out))
			return false;

		return true;
	}
	bool Database::GetChatrooms(std::vector<Chatroom> &Chatrooms)
	{
		Chatrooms.clear();
		const std::string Query = "SELECT * FROM Chatroom";

		Statement s;
		if (s.Prepare(Inner, Query))
			return false;

		bool MoreData = true;
		while (MoreData)
		{
			if (!s.Step(MoreData))
				return false;

			Chatroom c;
			if (!_GetChatroom(s, c))
				return false;
			Chatrooms.push_back(c);
		}

		return true;
	}
	bool Database::GetChatrooms(const Server &Host, std::vector<Chatroom> &Out)
	{
		Out.clear();
		const std::string Query = "SELECT * FROM Chatroom WHERE ServerIP = :ServerIP' AND ServerPort = :ServerPort AND ServerFamily = :ServerFamily";

		Statement s;
		if (s.Prepare(Inner, Query))
			return false;

		if (!s.Bind(":ServerIP", Host.Address.GetPrintableIP()) || !s.Bind(":ServerPort", Host.Address.Port) || !s.Bind(":ServerFamily", Host.Address.Family))
			return false;

		bool MoreData = true;
		while (MoreData)
		{
			if (!s.Step(MoreData))
				return false;

			Chatroom c;
			if (!_GetChatroom(s, c))
				return false;
			Out.push_back(c);
		}

		return true;
	}
	bool Database::GetChatrooms(const User &Owner, std::vector<Chatroom> &Out)
	{
		Out.clear();
		const std::string Query = "SELECT * FROM Chatroom WHERE OwnerUsername = :OwnerUsername";

		Statement s;
		if (s.Prepare(Inner, Query))
			return false;

		if (!s.Bind(":OwnerUsername", Owner.Username))
			return false;

		bool MoreData = true;
		while (MoreData)
		{
			if (!s.Step(MoreData))
				return false;

			Chatroom c;
			if (!_GetChatroom(s, c))
				return false;
			Out.push_back(c);
		}

		return true;
	}

	bool Database::InsertUser(const User &User)
	{
		const std::string Query = "INSERT OR REPLACE INTO User VALUES (:Username, :Password)";

		Statement s;
		if (!s.Prepare(Inner, Query))
			return false;

		if (!s.Bind(":Username", User.Username) || !s.Bind(":Password", User.Password))
			return false;

		if (!s.Execute())
			return false;

		return true;
	}
	bool Database::InsertServer(const Server &Server)
	{
		const std::string Query = "INSERT OR REPLACE INTO Server VALUES (:IP, :Port, :Family, :Name)";

		Statement s;
		if (!s.Prepare(Inner, Query))
			return false;

		if (!s.Bind(":IP", Server.Address.GetPrintableIP()) || !s.Bind(":Port", Server.Address.Port) || !s.Bind(":Family", Server.Address.Port) || !s.Bind(":Name", Server.Name))
			return false;

		if (!s.Execute())
			return false;

		return true;
	}
	bool Database::InsertChatroom(const Chatroom &Chatroom)
	{
		const std::string Query = "INSERT OR REPLACE INTO Chatroom VALUES (:Name, :OwnerUsername, :ServerIP, :ServerPort, :ServerFamily, :Password, :Description)";

		Statement s;
		if (!s.Prepare(Inner, Query))
			return false;

		if (!s.Bind(":Name", Chatroom.Name) || !s.Bind(":OwnerUsername", Chatroom.OwnerUsername) || !s.Bind(":ServerIP", Chatroom.ServerAddress.GetPrintableIP()) ||
				!s.Bind(":ServerPort", Chatroom.ServerAddress.Port) || !s.Bind(":ServerFamily", Chatroom.ServerAddress.Family))
			return false;

		if (!Chatroom.Password.Null)
		{
			if (!s.Bind(":Password", Chatroom.Password.Value))
				return false;
		}
		else
		{
			if (!s.BindNull(":Password"))
				return false;
		}

		if (!Chatroom.Description.Null)
		{
			if (!s.Bind(":Description", Chatroom.Description.Value))
				return false;
		}
		else
		{
			if (!s.BindNull(":Description"))
				return false;
		}

		if (!s.Execute())
			return false;

		return true;
	}
}
