#include "ChatWindow.h"

#include <algorithm>

#include "ConsoleIO.h"

ChatWindow::ChatWindow()
{
	StopFlag = false;
}

void ChatWindow::Refresh()
{
	RefreshContent();
	RefreshInput();
}
void ChatWindow::RefreshContent()
{
	Dimensions d = GetTerminalDimensions();

	unsigned int MaxHeight = d.Height-1;

	std::list<std::string> Output;

	std::list<std::string>::const_reverse_iterator i = Content.rbegin();
	while (i != Content.rend() && Output.size() < MaxHeight)
	{
		unsigned int Low = d.Width * (i->size() / d.Width - 1);
		unsigned int High = d.Width * (i->size() / d.Width);

		while (High != 0 && Output.size() < MaxHeight)
		{
			Output.push_front(std::string(i->begin()+Low, (High > i->size()) ? i->end() : i->begin() + High));

			Low -= d.Width;
			High -= d.Width;
		}

		i++;
	}

	PrintLock.lock();
	ClearScreen();
	unsigned int y = 0;
	for (std::list<std::string>::const_iterator i = Output.begin(); i != Output.end(); i++, y++)
	{
		SetCursor(0, y);
		std::cout << *i;
	}

	SetCursor(0, d.Height);
	std::cout << Input;

	PrintLock.unlock();
}
void ChatWindow::RefreshInput()
{

}


void ChatWindow::Print(const std::string &Text)
{
	Content.push_back(Text);
	while (Content.size() > MaxContent)
		Content.pop_front();

	Refresh();
}

void ChatWindow::InputFunc()
{
	while (true)
	{
		Key In = GetKey();
		if (!In.Recognised)
			continue;

		Dimensions d = GetTerminalDimensions();

		if (In.Printable)
		{
			Input.insert(Input.begin() + CursorPosition, In.c);
		}
		else if (In.k == SpecialKey::Backspace) // Backspace
		{
			if (CursorPosition > 0)
				Input.erase(Input.begin() + CursorPosition - 1);
		}
		else if (In.k == SpecialKey::Delete) // Delete
		{
			if (CursorPosition < Input.size() - 1)
				Input.erase(Input.begin() + CursorPosition);
		}
		else if (In.k == SpecialKey::Home)
			CursorPosition = 0;
		else if (In.k == SpecialKey::End)
			CursorPosition = Input.size() - 1;
		else if (In.k == SpecialKey::LeftArrow)
		{
			if (CursorPosition > 0)
				CursorPosition--;
		}
		else if (In.k == SpecialKey::RightArrow)
		{
			if (CursorPosition < Input.size() - 1)
				CursorPosition++;
		}
	}

	Stop();
}

void ChatWindow::Start()
{
	if (!StopFlag)
		return;

	InputThread = std::thread(&ChatWindow::InputFunc, this);

	std::unique_lock<std::mutex> Lock(StopLock);
	StopVar.wait(Lock);
}
void ChatWindow::Stop()
{
	std::unique_lock<std::mutex> Lock(StopLock);
	StopFlag = true;
	Lock.unlock();
	StopVar.notify_one();
}
