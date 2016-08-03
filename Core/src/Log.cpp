#include "Log.h"

#include <time.h>
#include <sstream>

std::ofstream Log;
std::mutex Lock;

CORE_API bool LogInit(const std::string &LogFile)
{
    Lock.lock();
    if(Log.is_open())
        return true;

    Log.open(LogFile);
    if(!Log.good())
    {
        Lock.unlock();
        return false;
    }

    _LogWrite("Log opened");
    Lock.unlock();
    return true;
}
CORE_API void LogShutdown()
{
    Lock.lock();
    if(!Log.is_open())
        return;

    _LogWrite("Log closed");
    Log.close();
    Lock.unlock();
}

std::string GetTimeStamp()
{
    time_t Raw = time(nullptr);
    tm *Time = localtime(&Raw);

    std::stringstream Formatted;

    Formatted << Time->tm_mday << "/"<<Time->tm_mon + 1 <<"/"<<Time->tm_year+1900<<" "<<Time->tm_hour<<":"<<Time->tm_min<<":"<<Time->tm_sec;

    return Formatted.str();
}
void _LogWrite(const std::string &Message)
{
    if(Log.is_open())
        Log << "[" << GetTimeStamp() << "] "<<Message<<std::endl;
}
CORE_API void LogWrite(const std::string &Message)
{
    Lock.lock();
    _LogWrite(Message);
    Lock.unlock();
}
CORE_API void LogWriteWarning(const std::string &Message)
{
    Lock.lock();
    _LogWrite("Warning: " + Message);
    Lock.unlock();
}
CORE_API void LogWriteError(const std::string &Message)
{
    Lock.lock();
    _LogWrite("Error: " + Message);
    Lock.unlock();
}
