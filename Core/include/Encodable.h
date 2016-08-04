#ifndef _ENCODABLE_H
#define _ENCODABLE_H

#include "Core.h"

#include <vector>

class CORE_API Encodable
{
public:
    std::vector<unsigned char> Serialise() const;
    virtual void Serialise(std::vector<unsigned char> &Buffer) const = 0;

    void Deserialise(const std::vector<unsigned char> &Buffer);
    virtual std::size_t Deserialise(const std::vector<unsigned char> &Buffer, const std::size_t Start) = 0;
};

#endif
