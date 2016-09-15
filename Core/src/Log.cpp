#include "Log.h"

#include <time.h>
#include <sstream>

std::ofstream LogFile;
std::recursive_mutex Lock;

bool LogInit(const std::string &LogPath)
{
    Lock.lock();
    if (LogFile.is_open())
        LogShutdown();

    LogFile.open(LogPath);
    if (!LogFile.good())
    {
        Lock.unlock();
        return false;
    }

    _Log("Log opened at " + LogPath);
    Lock.unlock();
    return true;
}
void LogShutdown()
{
    Lock.lock();
    if(!LogFile.is_open())
        return;

    _Log("Log closed");
    LogFile.close();
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
void _Log(const std::string &Message)
{
	_Log(Message.c_str());
}
void _Log(const char *Message)
{
    if(LogFile.is_open())
        LogFile << "[" << GetTimeStamp() << "] " << Message << std::endl;
}
bool Log(const std::string &Message, const bool RetVal)
{
	return Log(Message.c_str(), RetVal);
}
bool Log(const char *Message, const bool RetVal)
{
	Lock.lock();
    _Log(Message);
    Lock.unlock();
	return RetVal;
}
bool LogWarning(const std::string &Message, const bool RetVal)
{
	return Log(Message.c_str(), RetVal);
}
bool LogWarning(const char *Message, const bool RetVal)
{
    Lock.lock();
    _Log((std::string("Warning: ") + Message).c_str());
    Lock.unlock();
	return RetVal;
}
bool LogError(const std::string &Message, const bool RetVal)
{
	return Log(Message.c_str(), RetVal);
}
bool LogError(const char *Message, const bool RetVal)
{
    Lock.lock();
	_Log((std::string("Error: ") + Message).c_str());
    Lock.unlock();
	return RetVal;
}
