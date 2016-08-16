#include "ChatWindow.h"

#include <algorithm>

Dimensions GetTerminalDimensions()
{
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    Dimensions Result;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    Result.Width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    Result.Height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return Result;

#elif defined(__linux__)

    winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    Dimensions Result;
    Result.Height = w.ws_row;
    Result.Width = w.ws_col;

    return Result;
#endif
}

void SetCursor(const unsigned int x, const unsigned int y)
{
#if defined(_WIN32)
	COORD Coord;

	Coord.X = x;
	Coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
#elif defined(__linux__)
	printf("\033[%d;%dH", x+1, y+1);
#endif
}

char GetChar()
{
#if defined(_WIN32)
	return (char)_getch();
#elif defined(__linux__)
	termios Old, New;
	char Input;
	tcgetattr(STDIN_FILENO, &Old);
	New = Old;
	New.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &New);
	Input = (char)getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &Old);
	return Input;
#endif
}

void ClearScreen()
{
#if defined(_WIN32)
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE) return;
	Dimensions d=GetTerminalDimensions();
	DWORD Cells = d.Height * d.Width;

	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count))
		return;

	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
		return;
#elif defined(__linux__)
	// TODO: Find native efficient method - use ncurses?
	system("clear");
#endif
}


ChatWindow::ChatWindow()
{
	StopFlag = false;
}

void ChatWindow::Refresh()
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
		char In = GetChar();
		Dimensions d = GetTerminalDimensions();

		if (In == 0x0E) // Arrow key
		{
			In = GetChar();
		}
		else if (In == 0) // Backspace
		{
			if (CursorPosition > 0)
				Input.erase(Input.begin() + CursorPosition - 1);
		}
		else if (In == 0) // Delete
		{
			if (CursorPosition > 0)
				Input.erase(Input.begin() + CursorPosition);
		}
		else if (In >= ' ' && In <= '~') // Displayable character
		{

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
