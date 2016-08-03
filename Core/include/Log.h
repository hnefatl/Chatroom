#ifndef _LOG_H
#define _LOG_H

#include <string>
#include <fstream>
#include <mutex>

#include "Core.h"

extern std::ofstream Log;
extern std::mutex Lock;

CORE_API bool LogInit(const std::string &LogFile = "Log.txt");
CORE_API void LogShutdown();


std::string GetTimeStamp();
void _LogWrite(const std::string &Message);
CORE_API void LogWrite(const std::string &Message);
CORE_API void LogWriteWarning(const std::string &Message);
CORE_API void LogWriteError(const std::string &Message);

#endif
