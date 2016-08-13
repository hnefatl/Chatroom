#include "Encodable.h"

#include "Net.h"

std::vector<unsigned char> Encodable::Encode(const bool Partial) const
{
    std::vector<unsigned char> Buffer;
    Encode(Buffer, Partial);
    return Buffer;
}
void Encodable::Encode(std::vector<unsigned char> &Buffer, const bool Partial) const
{
    Serialise(Partial, Buffer);
}

bool Encodable::Decode(const std::vector<unsigned char> &Buffer, const bool Partial)
{
    std::size_t Start = 0;
    return Decode(Buffer, Start, Partial);
}
bool Encodable::Decode(const std::vector<unsigned char> &Buffer, std::size_t &Start, const bool Partial)
{
    bool ReceivedPartial;
    if (!Deserialise(Buffer, Start, ReceivedPartial))
        return false;

    if (Partial != ReceivedPartial) // Asked for partial, received full or vice versa
        return false;

    return true;
}
