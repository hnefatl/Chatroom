#ifndef _ENCODABLE_H
#define _ENCODABLE_H

#include "Core.h"

#include <vector>

class CORE_API Encodable
{
public:
    std::vector<unsigned char> Encode() const;
    virtual void Encode(std::vector<unsigned char> &Buffer) const = 0;

    bool Decode(const std::vector<unsigned char> &Buffer);
    virtual bool Decode(const std::vector<unsigned char> &Buffer, std::size_t &Start) = 0;
};

#endif
