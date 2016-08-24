#include "Entities/User.h"

#include <algorithm>

#include "Net.h"

namespace Entities
{
	User::User()
	{
	}

	void User::SerialiseInfo(std::vector<unsigned char> &Buffer) const
	{
		Serialise(Guest, Buffer);
		Serialise(Username, Buffer);
	}
	void User::SerialiseFull(std::vector<unsigned char> &Buffer) const
	{
		SerialiseInfo(Buffer);
		Serialise(Password, Buffer);
	}

	bool User::DeserialiseInfo(const std::vector<unsigned char> &Buffer, std::size_t Start)
	{
		if (!Deserialise(Buffer, Start, Guest) || !Deserialise(Buffer, Start, Username))
			return false;
		return true;
	}
	bool User::DeserialiseFull(const std::vector<unsigned char> &Buffer, std::size_t Start)
	{
		if (!DeserialiseInfo(Buffer, Start) || !Deserialise(Buffer, Start, Password))
			return false;
		return true;
	}

	bool User::IsGuest() const
	{
		return Guest;
	}
	void User::SetGuest(const bool Guest)
	{
		this->Guest = Guest;
	}

	std::string User::GetUsername() const
	{
		return Username;
	}
	bool User::SetUsername(const std::string &Username)
	{
		if (Username.length() > MaxUsernameLength)
			return false;

		for (unsigned int x = 0; x < Username.size(); x++)
		{
			if (!((Username[x] >= 'a' && Username[x] <= 'z') || (Username[x] >= 'A' && Username[x] <= 'Z') || (Username[x] >= '0' && Username[x] <= '9') || Username[x] == '_'))
				return false;
		}

		this->Username = Username;
		return true;
	}

	std::string User::GetPassword() const
	{
		return Password;
	}
	bool User::SetPassword(const std::string &Password)
	{
		if (Password.length() > MaxPasswordLength)
			return false;

		for (unsigned int x = 0; x < Password.size(); x++)
		{
			if (!((Password[x] >= '!' && Password[x] <= '~')))
				return false;
		}

		this->Password = Password;
		return true;
	}
}
