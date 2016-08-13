#include "User.h"

#include "Net.h"

User::User()
{

}

void User::_Encode(std::vector<unsigned char> &Buffer, const bool Partial) const
{
    Encodable::Encode(Buffer, Partial);

    Serialise(Username, Buffer);
    if (!Partial)
        Serialise(Password, Buffer);
}
bool User::_Decode(const std::vector<unsigned char> &Buffer, std::size_t &Start, const bool Partial)
{
    if (!Encodable::Decode(Buffer, Partial))
        return false;

    if (!Deserialise(Buffer, Start, Username))
        return false;

    if (!Partial)
    {
        if (!Deserialise(Buffer, Start, Password))
            return false;
    }

    return true;
}
