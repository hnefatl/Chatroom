#ifndef _CHATWINDOW_H
#define _CHATWINDOW_H

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
	std::list<std::string>::iterator MessagePosition; // Sort out moving up/down through message *lines*

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
	void PrintLine(const unsigned int Length);
	void RefreshInfo();
	void RefreshContent();
	void RefreshInput();
	void PositionCursor();
	std::string GetTrimmedInput();

	void InputFunc();

public:
	ChatWindow();
	ChatWindow(const char CommandChar);

    void Start(const std::function<void(const std::string &)> OnSend);
	void Stop();

	void Print(const std::string &Text);
};


#endif
