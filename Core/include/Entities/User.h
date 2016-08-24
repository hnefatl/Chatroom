#ifndef _USER_H
#define _USER_H

#include "Core.h"

#include <string>
#include <vector>

namespace Entities
{
	class User
	{
	protected:
		const unsigned int MaxUsernameLength = 20;
		const unsigned int MaxAliasLength = 20;
		const unsigned int MaxPasswordLength = 30;

		bool Guest;
		std::string Username;
		std::string Password;

	public:
		CORE_API User();

		CORE_API void SerialiseInfo(std::vector<unsigned char> &Buffer) const;
		CORE_API void SerialiseFull(std::vector<unsigned char> &Buffer) const;

		CORE_API bool DeserialiseInfo(const std::vector<unsigned char> &Buffer, std::size_t Start = 0);
		CORE_API bool DeserialiseFull(const std::vector<unsigned char> &Buffer, std::size_t Start = 0);

		CORE_API bool IsGuest() const;
		CORE_API void SetGuest(const bool Guest);

		CORE_API std::string GetUsername() const;
		CORE_API bool SetUsername(const std::string &Username);

		CORE_API std::string GetPassword() const;
		CORE_API bool SetPassword(const std::string &Password);
	};
}

#endif
