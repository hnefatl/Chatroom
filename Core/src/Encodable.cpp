#include "Encodable.h"

std::vector<unsigned char> Encodable::Encode() const
{
    std::vector<unsigned char> Buffer;
    Encode(Buffer);
    return Buffer;
}

bool Encodable::Decode(const std::vector<unsigned char> &Buffer)
{
    std::size_t Start = 0;
    return Decode(Buffer, Start);
}
