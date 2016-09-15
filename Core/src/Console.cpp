#include "Console.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

Console::Console()
{
}
Console::~Console()
{
	Stop();
}

void Console::Start()
{
#ifdef __linux__
	initscr();
	cbreak();
#endif
}
void Console::Stop()
{
#ifdef __linux__
	endwin();
#endif
}

void Console::Print(const std::string &Text)
{
#if defined(_WIN32)
	std::cout << Text;
#elif defined (__linux__)
	printw(Text.c_str());
	refresh();
#endif
}
void Console::PrintLine(const char Character)
{
	Dimensions d = GetDimensions();
	std::string Line;
	Line.resize(d.Width);
	std::fill(Line.begin(), Line.end(), Character);
	Print(Line);
}

Dimensions Console::GetDimensions()
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
void Console::SetCursor(const unsigned int x, const unsigned int y)
{
#if defined(_WIN32)
	COORD Coord;

	Coord.X = x;
	Coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coord);
#elif defined(__linux__)
	move(y, x); // NCurses uses y,x not x,y
	refresh();
#endif
}

char Console::GetChar()
{
#if defined(_WIN32)
	return (char)_getch();
#elif defined(__linux__)
	nodelay(stdscr, false);
	return (char)getch();
#endif
}
Nullable<char> Console::GetChar(const unsigned int TimeoutMs, const unsigned int Jump)
{
#if defined(__linux__)
	nodelay(stdscr, true);
#endif
	auto Start = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds WaitDuration(TimeoutMs);
	while (std::chrono::high_resolution_clock::now() - Start < WaitDuration)
	{
#if defined(_WIN32)
		if (kbhit())
			return Nullable<char>((char)_getch());
#elif defined(__linux__)
		int ch = getch();
		if (ch != ERR)
			return Nullable<char>((char)ch);
#endif
		std::this_thread::sleep_for(std::chrono::milliseconds(Jump));
	}
	return Nullable<char>();
}

void Console::ClearScreen()
{
#if defined(_WIN32)
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE)
		return;

	Dimensions d = GetDimensions();
	DWORD Cells = d.Height * d.Width;

	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', Cells, homeCoords, &count))
		return;

	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, Cells, homeCoords, &count))
		return;
#elif defined(__linux__)
	clear();
	refresh();
#endif
}
void Console::ClearSection(const unsigned int Row, const unsigned int Lines)
{
#if defined(_WIN32)
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	COORD homeCoords = { 0, (SHORT)Row };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE)
		return;

	Dimensions d = GetDimensions();
	DWORD Cells = Lines * d.Width;

	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', Cells, homeCoords, &count))
		return;
	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, Cells, homeCoords, &count))
		return;
#elif defined(__linux__)
	for(unsigned int y = 0; y < Lines; y++)
	{
		move(Row + y, 0);
		clrtoeol();
	}
	refresh();
#endif
}

Key Console::MapKey(char c)
{
	if (c >= ' ' && c <= '~') // Space through to ~ are all printable characters
		return Key(c);
	else if (c == 127 || c == 8)
		return Key(SpecialKey::Backspace);
	else if (c == 10 || c == 13)
		return Key(SpecialKey::Enter);
	else if (c == 9)
		return Key(SpecialKey::Tab);
#if defined(_WIN32)
	else if (c == -32)
	{
		c = GetChar();
		if (c == 83)
			return Key(SpecialKey::Delete);
		else if (c == 71)
			return Key(SpecialKey::Home);
		else if (c == 79)
			return Key(SpecialKey::End);
		else if (c == 72)
			return Key(SpecialKey::UpArrow);
		else if (c == 80)
			return Key(SpecialKey::DownArrow);
		else if (c == 75)
			return Key(SpecialKey::LeftArrow);
		else if (c == 77)
			return Key(SpecialKey::RightArrow);
	}
#elif defined(__linux__)
	else if (c == 27 && GetChar() == 91)
	{
		c = GetChar();
		if (c == 51 && GetChar() == 126)
			return Key(SpecialKey::Delete);
		else if (c == 70)
			return Key(SpecialKey::End);
		else if (c == 72)
			return Key(SpecialKey::Home);
		else if (c == 65)
			return Key(SpecialKey::UpArrow);
		else if (c == 66)
			return Key(SpecialKey::DownArrow);
		else if (c == 68)
			return Key(SpecialKey::LeftArrow);
		else if (c == 67)
			return Key(SpecialKey::RightArrow);
	}
#endif

	return Key();

	/*
	 * Linux
	 * Backspace:	127
	 * Delete:		27  91  51  126
	 * Enter:		10
	 * Home:		27  91  72
	 * End:			27  91  70
	 * Tab:			9
	 * UpArrow:		27  91  65
	 * DownArrow:	27  91  66
	 * LeftArrow:	27  91  68
	 * RightArrow:	27  91  67
	 *
	 * Windows
	 * Backspace:	8
	 * Delete:		-32 83
	 * Enter:		13
	 * Home:		-32 71
	 * End:			-32 79
	 * Tab:			9
	 * UpArrow:		-32 72
	 * DownArrow:	-32 80
	 * LeftArrow:	-32 75
	 * RightArrow:	-32 77
	*/
}

Key Console::GetKey()
{
	return MapKey(GetChar());
}
Nullable<Key> Console::GetKey(const unsigned int TimeoutMs, const unsigned int Jump)
{
	Nullable<char> c = GetChar(TimeoutMs, Jump);
	if (c.Null)
		return Nullable<Key>();

	return Nullable<Key>(MapKey(c.Value));
}

Key::Key()
{
}
Key::Key(const char c)
{
	Recognised = true;
	Printable = true;
	this->c = c;
}
Key::Key(const SpecialKey k)
{
	Recognised = true;
	Printable = false;
	this->k = k;
}
