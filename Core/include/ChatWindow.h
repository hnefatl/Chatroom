#ifndef _CHATWINDOW_H
#define _CHATWINDOW_H

#include <iostream>
#include <mutex>
#include <list>
#include <string>
#include <thread>
#include <condition_variable>
#include <functional>

class ChatWindow
{
protected:
	std::list<std::string> Content;
	unsigned int MaxContent = 500;
	std::list<std::string>::iterator MessagePosition; // Sort out moving up/down through message *lines*

	std::string Input;
	unsigned int CursorPosition;
	char CommandChar;

	std::function<void(const std::string &)> OnSend;

	std::mutex PrintLock;

	std::thread InputThread;
	std::mutex StopLock;
	std::condition_variable StopVar;
	bool StopFlag;

    void Refresh();
	void RefreshContent();
	void RefreshInput();

    void Print(const std::string &Text);

	void InputFunc();

public:
    ChatWindow(const std::function<void(const std::string &)> OnSend);

    void Start();
	void Stop();
};


#endif
