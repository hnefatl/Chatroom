#ifndef _CHATWINDOW_H
#define _CHATWINDOW_H

#include "Core.h"

#include <iostream>
#include <mutex>
#include <list>
#include <string>
#include <thread>
#include <condition_variable>
#include <functional>

#include "Signal.h"
#include "Console.h"

class ChatWindow
{
protected:
	std::list<std::string> Content;
	std::mutex ContentLock;
	unsigned int MaxContent = 500;
	unsigned int MessagePosition;

	std::string Input;
	std::mutex InputLock;
	unsigned int StartPosition;
	unsigned int CursorPosition;
	char CommandChar = '/';
	char LineChar = '=';

	std::function<void(const std::string &)> OnSend;

	std::mutex PrintLock;
	Console Term;

	std::thread InputThread;
	Signal StopSignal;

    void Refresh();
	void RefreshLines();
	void RefreshInfo();
	void RefreshContent();
	void RefreshInput();
	void PositionCursor();
	std::string GetTrimmedInput();

	void InputFunc();

public:
	CORE_API ChatWindow();

	CORE_API void Start(const std::function<void(const std::string &)> OnSend);
	CORE_API void Stop();

	CORE_API void Print(const std::string &Text);
};


#endif
