#ifndef _ENCODABLE_H
#define _ENCODABLE_H

#include "Core.h"

#include <vector>

class CORE_API Encodable
{
public:
    std::vector<unsigned char> Encode(const bool Partial) const;
    void Encode(std::vector<unsigned char> &Buffer, const bool Partial) const;

    bool Decode(const std::vector<unsigned char> &Buffer, const bool Partial);
    bool Decode(const std::vector<unsigned char> &Buffer, std::size_t &Start, const bool Partial);

protected:
    virtual void _Encode(std::vector<unsigned char> &Buffer, const bool Partial) const = 0;
    virtual bool _Decode(const std::vector<unsigned char> &Buffer, std::size_t &Start, const bool Partial) = 0;
};

#endif
