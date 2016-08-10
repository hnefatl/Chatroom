#include <iostream>

#include <Log.h>
#include <Net.h>

int main (int argc, char *argv[])
{
    LogInit("Log.txt");

    LogWrite("Standard message");
    LogWriteWarning("Warning warning");
    LogWriteError("Error error");

    NetInit();

    std::vector<unsigned char> Bytes;

    Bytes = Serialise((uint32_t)2045858);
    uint32_t a;
    Deserialise(Bytes, a);
    std::cout<<a<<std::endl;

    Bytes = Serialise((int32_t)2045858);
    int32_t b;
    Deserialise(Bytes, b);
    std::cout<<b<<std::endl;

    Bytes = Serialise((int32_t)-2045858);
    int32_t c;
    Deserialise(Bytes, c);
    std::cout<<c<<std::endl;

    Bytes = Serialise("Hello my name is keith");
    std::string d;
    Deserialise(Bytes, d);
    std::cout<<d<<std::endl;

    NetShutdown();

    LogShutdown();
	return 0;
}
