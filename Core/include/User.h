#ifndef _USER_H
#define _USER_H

#include <string>

#include "Encodable.h"

class User
    : public Encodable
{
protected:
    uint32_t Id;
    std::string Username;

public:
    User();

    void Encode(std::vector<unsigned char> &Buffer) const;
    bool Decode(const std::vector<unsigned char> &Buffer, std::size_t &Start);

};

#endif
