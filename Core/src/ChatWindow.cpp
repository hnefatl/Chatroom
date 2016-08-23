#include "ChatWindow.h"

#include <algorithm>
#include <iomanip>

#include "ConsoleIO.h"

ChatWindow::ChatWindow()
{
	CursorPosition = 0;
	StartPosition = 0;
}

void ChatWindow::Refresh()
{
	RefreshContent();
	RefreshInfo();
	RefreshInput();
	RefreshLines();
}
void ChatWindow::RefreshLines()
{
	Dimensions d = GetTerminalDimensions();
	PrintLock.lock();

	SetCursor(0, 1);
	PrintLine(d.Width);

	SetCursor(0, d.Height - 2);
	PrintLine(d.Width);

	PositionCursor();
	PrintLock.unlock();
}
void ChatWindow::PrintLine(const unsigned int Length)
{
	std::cout << std::setfill('=') << std::setw(Length) << "" << std::setfill(' ');
}
void ChatWindow::RefreshInfo()
{
	Dimensions d = GetTerminalDimensions();
	PrintLock.lock();

	SetCursor(0, 0);

	PositionCursor();
	PrintLock.unlock();
}
void ChatWindow::RefreshContent()
{
	Dimensions d = GetTerminalDimensions();

	unsigned int MaxHeight = d.Height - 3;

	std::list<std::string> Output;

	std::list<std::string>::const_reverse_iterator i = Content.rbegin();
	while (i != Content.rend() && Output.size() < MaxHeight)
	{
		unsigned int Low = d.Width * (i->size() / d.Width);
		unsigned int High = d.Width * (i->size() / d.Width + 1);

		while (High != 0 && Output.size() < MaxHeight)
		{
			Output.push_front(std::string(i->begin() + Low, (High > i->size()) ? i->end() : i->begin() + High));

			Low -= d.Width;
			High -= d.Width;
		}

		i++;
	}

	PrintLock.lock();
	unsigned int y = 2;
	for (std::list<std::string>::const_iterator i = Output.begin(); i != Output.end(); i++, y++)
	{
		SetCursor(0, y);
		std::cout << std::setw(d.Width) << std::setfill(' ') << *i;
	}

	PositionCursor();
	PrintLock.unlock();
}
void ChatWindow::RefreshInput()
{
	Dimensions d = GetTerminalDimensions();
	std::lock(PrintLock, InputLock);
	SetCursor(0, d.Height);
	std::cout << std::left << std::setw(d.Width - 1) << GetTrimmedInput();

	PositionCursor();
	PrintLock.unlock();
	InputLock.unlock();

}
void ChatWindow::PositionCursor()
{
	Dimensions d = GetTerminalDimensions();
	SetCursor(CursorPosition - StartPosition, d.Height);
}
std::string ChatWindow::GetTrimmedInput()
{
	Dimensions d = GetTerminalDimensions();
	unsigned int End = Input.size() < d.Width - 1 ? Input.size() : StartPosition + d.Width - 1;
	return std::string(Input.begin() + StartPosition, Input.begin() + End);
}


void ChatWindow::InputFunc()
{
	while (true)
	{
		Key In = GetKey();
		if (!In.Recognised)
			continue;

		Dimensions d = GetTerminalDimensions();

		InputLock.lock();
		if (In.Printable)
		{
			Input.insert(Input.begin() + CursorPosition, In.c);
			CursorPosition++;
			if (CursorPosition > d.Width - 2)
				StartPosition = CursorPosition - d.Width + 1;
		}
		else if (In.k == SpecialKey::Backspace)
		{
			if (CursorPosition > 0)
			{
				Input.erase(Input.begin() + CursorPosition - 1);
				CursorPosition--;
				if (CursorPosition < StartPosition)
					StartPosition = CursorPosition;
				if (CursorPosition > d.Width - 2)
					StartPosition--;
			}
		}
		else if (In.k == SpecialKey::Delete)
		{
			if (CursorPosition < Input.size())
				Input.erase(Input.begin() + CursorPosition);
			if (CursorPosition >= Input.size() && CursorPosition != 0)
				CursorPosition = Input.size() - 1;
		}
		else if (In.k == SpecialKey::Home)
		{
			CursorPosition = 0;
			StartPosition = 0;
		}
		else if (In.k == SpecialKey::End)
		{
			if (Input.size() > 0)
			{
				CursorPosition = Input.size() - 1;
				if (Input.size() < d.Width)
					StartPosition = 0;
				else
					StartPosition = Input.size() - d.Width - 1;
			}
			else
				CursorPosition = 0;
		}
		else if (In.k == SpecialKey::LeftArrow)
		{
			if (CursorPosition > 0)
				CursorPosition--;
			if (StartPosition > CursorPosition)
				StartPosition = CursorPosition;
		}
		else if (In.k == SpecialKey::RightArrow)
		{
			if (CursorPosition < Input.size())
				CursorPosition++;
			if (CursorPosition > StartPosition + d.Width - 1)
				StartPosition = CursorPosition - d.Width;
		}
		else if (In.k == SpecialKey::Enter)
		{
			if (Input.size() > 0)
			{
				OnSend(Input);
				Input.clear();
				StartPosition = 0;
				CursorPosition = 0;
			}
		}
		InputLock.unlock();

		RefreshInput();
	}

	Stop();
}

void ChatWindow::Start(const std::function<void(const std::string &)> OnSend)
{
	if (StopSignal.Triggered())
		return;

	this->OnSend = OnSend;

	PositionCursor();
	RefreshLines();

	InputThread = std::thread(&ChatWindow::InputFunc, this);

	StopSignal.Wait();
}
void ChatWindow::Stop()
{
	StopSignal.Set();
}


void ChatWindow::Print(const std::string &Text)
{
	std::lock(PrintLock, ContentLock);
	Content.push_back(Text);
	while (Content.size() > MaxContent)
		Content.pop_front();

	PrintLock.unlock();
	ContentLock.unlock();

	Refresh();
}
