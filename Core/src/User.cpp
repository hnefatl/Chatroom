#include "User.h"

#include "Net.h"

User::User()
{

}

void User::Encode(std::vector<unsigned char> &Buffer) const
{
    Serialise(Id, Buffer);
    Serialise(Username);
}
bool User::Decode(const std::vector<unsigned char> &Buffer, std::size_t &Start)
{
    if(!Deserialise(Buffer, Start, Id))
        return false;
    if(!Deserialise(Buffer, Start, Username))
        return false;

    return true;
}
