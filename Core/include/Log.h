#ifndef _LOG_H
#define _LOG_H

#include <string>
#include <fstream>
#include <mutex>

#include "Core.h"

extern std::ofstream LogFile;
extern std::recursive_mutex Lock;

CORE_API bool LogInit(const std::string &LogPath = "Log.txt");
CORE_API void LogShutdown();


std::string GetTimeStamp();
void _Log(const char *Message);
void _Log(const std::string &Message);
CORE_API bool Log(const char *Message, const bool RetVal = false);
CORE_API bool Log(const std::string &Message, const bool RetVal = false);
CORE_API bool LogWarning(const char *Message, const bool RetVal = false);
CORE_API bool LogWarning(const std::string &Message, const bool RetVal = false);
CORE_API bool LogError(const char *Message, const bool RetVal = false);
CORE_API bool LogError(const std::string &Message, const bool RetVal = false);

#endif
