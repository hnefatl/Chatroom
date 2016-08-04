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

    void Serialise(std::vector<unsigned char> &Buffer) const;
    std::size_t Deserialise(const std::vector<unsigned char> &Buffer, const std::size_t Start);

};

#endif
