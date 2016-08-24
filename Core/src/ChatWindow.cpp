#include "ChatWindow.h"

#include <algorithm>
#include <iomanip>

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
	Dimensions d = Term.GetDimensions();
	PrintLock.lock();

	Term.SetCursor(0, 1);
	Term.PrintLine(LineChar);

	Term.SetCursor(0, d.Height - 2);
	Term.PrintLine(LineChar);

	PositionCursor();
	PrintLock.unlock();
}
void ChatWindow::RefreshInfo()
{
	Dimensions d = Term.GetDimensions();
	PrintLock.lock();

	Term.SetCursor(0, 0);

	PositionCursor();
	PrintLock.unlock();
}
void ChatWindow::RefreshContent()
{
	Dimensions d = Term.GetDimensions();

	unsigned int MaxHeight = d.Height - 4;

	std::list<std::string> Output;

	std::list<std::string>::const_iterator i = MessagePosition;
	while (i != Content.end() && Output.size() < MaxHeight)
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
	Term.ClearSection(2, MaxHeight);
	unsigned int y = 3;
	for (std::list<std::string>::const_reverse_iterator i = Output.rbegin(); i != Output.rend(); i++, y++)
	{
		Term.SetCursor(0, d.Height - y);
		Term.Print(*i);
	}

	PositionCursor();
	PrintLock.unlock();
}
void ChatWindow::RefreshInput()
{
	Dimensions d = Term.GetDimensions();
	std::lock(PrintLock, InputLock);
	Term.SetCursor(0, d.Height - 1);
	Term.ClearSection(d.Height - 1, 1);
	Term.Print(GetTrimmedInput());

	PositionCursor();
	PrintLock.unlock();
	InputLock.unlock();
}
void ChatWindow::PositionCursor()
{
	Dimensions d = Term.GetDimensions();
	Term.SetCursor(CursorPosition - StartPosition, d.Height - 1);
}
std::string ChatWindow::GetTrimmedInput()
{
	Dimensions d = Term.GetDimensions();
	unsigned int End = Input.size() < d.Width - 1 ? Input.size() : StartPosition + d.Width - 1;
	return std::string(Input.begin() + StartPosition, Input.begin() + End);
}


void ChatWindow::InputFunc()
{
	while (true)
	{
		Key In = Term.GetKey();
		if (!In.Recognised)
			continue;

		Dimensions d = Term.GetDimensions();

		if (In.Printable)
		{
			InputLock.lock();
			Input.insert(Input.begin() + CursorPosition, In.c);
			CursorPosition++;
			if (CursorPosition > d.Width - 2)
				StartPosition = CursorPosition - d.Width + 1;
			InputLock.unlock();
		}
		else if (In.k == SpecialKey::Backspace)
		{
			InputLock.lock();
			if (CursorPosition > 0)
			{
				Input.erase(Input.begin() + CursorPosition - 1);
				CursorPosition--;
				if (CursorPosition < StartPosition)
					StartPosition = CursorPosition;
				if (CursorPosition > d.Width - 2)
					StartPosition--;
			}
			InputLock.unlock();
		}
		else if (In.k == SpecialKey::Delete)
		{
			InputLock.lock();
			if (CursorPosition < Input.size())
				Input.erase(Input.begin() + CursorPosition);
			if (CursorPosition >= Input.size() && CursorPosition != 0)
				CursorPosition = Input.size();
			InputLock.unlock();
		}
		else if (In.k == SpecialKey::Home)
		{
			InputLock.lock();
			CursorPosition = 0;
			StartPosition = 0;
			InputLock.unlock();
		}
		else if (In.k == SpecialKey::End)
		{
			InputLock.lock();
			if (Input.size() > 0)
			{
				CursorPosition = Input.size();
				if (Input.size() < d.Width)
					StartPosition = 0;
				else
					StartPosition = Input.size() - d.Width - 1;
			}
			else
				CursorPosition = 0;
			InputLock.unlock();
		}
		else if (In.k == SpecialKey::LeftArrow)
		{
			InputLock.lock();
			if (CursorPosition > 0)
				CursorPosition--;
			if (StartPosition > CursorPosition)
				StartPosition = CursorPosition;
			InputLock.unlock();
		}
		else if (In.k == SpecialKey::RightArrow)
		{
			InputLock.lock();
			if (CursorPosition < Input.size())
				CursorPosition++;
			if (CursorPosition > StartPosition + d.Width - 1)
				StartPosition = CursorPosition - d.Width;
			InputLock.unlock();
		}
		else if (In.k == SpecialKey::UpArrow)
		{
			if (MessagePosition != Content.end())
			{
				MessagePosition++;
				RefreshContent();
			}
		}
		else if (In.k == SpecialKey::DownArrow)
		{
			if (MessagePosition != Content.begin())
			{
				MessagePosition--;
				RefreshContent();
			}
		}
		else if (In.k == SpecialKey::Tab)
		{
			Refresh();
		}
		else if (In.k == SpecialKey::Enter)
		{
			InputLock.lock();
			if (Input.size() > 0)
			{
				OnSend(Input);
				Input.clear();
				StartPosition = 0;
				CursorPosition = 0;
				RefreshContent();
			}
			MessagePosition = Content.begin();
			InputLock.unlock();
		}

		RefreshInput();
	}

	Stop();
}

void ChatWindow::Start(const std::function<void(const std::string &)> OnSend)
{
	if (StopSignal.IsSet())
		return;

	this->OnSend = OnSend;

	Term.Start();

	PositionCursor();
	RefreshLines();

	InputThread = std::thread(&ChatWindow::InputFunc, this);

	StopSignal.Wait();
}
void ChatWindow::Stop()
{
	Term.Stop();

	StopSignal.Set();
}


void ChatWindow::Print(const std::string &Text)
{
	std::lock(PrintLock, ContentLock);
	Content.push_front(Text);
	if (Content.size() == 1)
		MessagePosition = Content.begin();

	while (Content.size() > MaxMessages)
	{
		if (Content.end() == MessagePosition)
			MessagePosition--;
		Content.pop_back();
	}

	PrintLock.unlock();
	ContentLock.unlock();

	RefreshContent();
}
