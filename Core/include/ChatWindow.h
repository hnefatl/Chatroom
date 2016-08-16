#ifndef _CHATWINDOW_H
#define _CHATWINDOW_H

#include <iostream>
#include <mutex>
#include <list>
#include <string>
#include <thread>
#include <condition_variable>

#if defined(_WIN32)

#include <windows.h>
#include <conio.h>

#elif defined(__linux__)

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

#endif

struct Dimensions
{
    unsigned int Width;
    unsigned int Height;
};
Dimensions GetTerminalDimensions();
void SetCursor(const unsigned int x, const unsigned int y);
void ClearScreen();
char GetChar();

class ChatWindow
{
protected:
	std::list<std::string> Content;
	unsigned int MaxContent = 500;
	std::list<std::string>::iterator MessagePosition; // Sort out moving up/down through message *lines*

	std::string Input;
	unsigned int CursorPosition;
	char CommandChar;

	std::mutex PrintLock;

	std::thread InputThread;
	std::mutex StopLock;
	std::condition_variable StopVar;
	bool StopFlag;

    void Refresh();
    void Print(const std::string &Text);

	void InputFunc();

public:
    ChatWindow();

    void Start();
	void Stop();
};


#endif
