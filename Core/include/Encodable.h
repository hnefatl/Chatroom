#ifndef _ENCODABLE
#define _ENCODABLE

#include "Core.h"

CORE_API class Encodable
{
public:
    std::vector<unsigned char> Serialise() const;
    virtual void Serialise(std::vector<unsigned char> &Buffer) const = 0;

    void Deserialise(const std::vector<unsigned char> &Buffer);
    virtual size_t Deserialise(const std::vector<unsigned char> &Buffer, const size_t Start) = 0;
};

#endif
