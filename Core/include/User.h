#ifndef _USER_H
#define _USER_H

#include <string>

#include "Encodable.h"

class User
    : public Encodable
{
protected:
    std::string Username;
    std::string Password;

    virtual void _Encode(std::vector<unsigned char> &Buffer, const bool Partial) const;
    virtual bool _Decode(const std::vector<unsigned char> &Buffer, std::size_t &Start, const bool Partial);

public:
    User();

};

#endif
