#ifndef _CHATWINDOW_H
#define _CHATWINDOW_H

#include "Core.h"

#include <iostream>
#include <mutex>
#include <list>
#include <vector>
#include <string>
#include <thread>
#include <condition_variable>
#include <functional>

#include "Signal.h"
#include "Console.h"
#include "InputQueue.h"

class ChatWindow
{
protected:
	std::list<std::string> Content; // All the "messages"
	std::mutex ContentLock;
	unsigned int MaxMessages = 500; // Cap on number of messages
	std::list<std::string>::iterator MessagePosition; // Current message at the bottom of the box

	std::string Input; // Buffer holding current input string
	std::mutex InputLock;
	unsigned int StartPosition; // Index in the input string of the left-most character printed
	unsigned int CursorPosition; // Index in the input string of the currently selected character
	char CommandChar = '/';
	char LineChar = '=';

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
	InputQueue UserInput;

	CORE_API ChatWindow();

	CORE_API void Start();
	CORE_API void Stop();

	CORE_API void Print(const std::string &Text);
};


#endif
