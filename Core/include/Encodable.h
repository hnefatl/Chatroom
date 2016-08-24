#ifndef _ENCODABLE_H
#define _ENCODABLE_H

#include "Core.h"

#include <vector>

class Encodable
{
public:
    CORE_API std::vector<unsigned char> Encode(const bool Partial) const;
    CORE_API void Encode(std::vector<unsigned char> &Buffer, const bool Partial) const;

    CORE_API bool Decode(const std::vector<unsigned char> &Buffer, const bool Partial);
    CORE_API bool Decode(const std::vector<unsigned char> &Buffer, std::size_t &Start, const bool Partial);

protected:
    virtual void _Encode(std::vector<unsigned char> &Buffer, const bool Partial) const = 0;
    virtual bool _Decode(const std::vector<unsigned char> &Buffer, std::size_t &Start, const bool Partial) = 0;
};

#endif
