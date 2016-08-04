#include "Encodable.h"

std::vector<unsigned char> Encodable::Serialise() const
{
    std::vector<unsigned char> Buffer;
    Serialise(Buffer);
    return Buffer;
}

void Encodable::Deserialise(const std::vector<unsigned char> &Buffer)
{
    Deserialise(Buffer, 0);
}
