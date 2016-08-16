#include "ConsoleIO.h"

#include <iostream>

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
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE)
		return;

	Dimensions d = GetTerminalDimensions();
	DWORD Cells = d.Height * d.Width;

	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', Cells, homeCoords, &count))
		return;

	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, Cells, homeCoords, &count))
		return;
#elif defined(__linux__)
	// TODO: Find native efficient method - use ncurses?
	system("clear");
#endif
}

Key::Key()
{
	Recognised = false;
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

Key GetKey()
{
	char Input = GetChar();
	if (Input >= ' ' && Input <= '~') // Space through to ~ are all printable characters
		return Key(Input);
	else if (Input == 127 || Input == 8)
		return Key(SpecialKey::Backspace);
	else if (Input == 10)
		return Key(SpecialKey::Enter);
	else if (Input == 9)
		return Key(SpecialKey::Tab);
#if defined(_WIN32)
#error Rewrite on windows
#elif defined(__linux__)
	else if (Input == 27 && GetChar() != 91)
	{
		Input = GetChar();
		if (Input == 51 && GetChar() == 126)
			return Key(SpecialKey::Delete);
		else if (Input == 70)
			return Key(SpecialKey::End);
		else if (Input == 72)
			return Key(SpecialKey::Home);
		else if (Input == 90)
			return Key(SpecialKey::BackTab);
		else if (Input == 65)
			return Key(SpecialKey::UpArrow);
		else if (Input == 66)
			return Key(SpecialKey::DownArrow);
		else if (Input == 68)
			return Key(SpecialKey::LeftArrow);
		else if (Input == 67)
			return Key(SpecialKey::RightArrow);
	}
#endif

	return Key();
}
/*
 * Linux
 * Backspace:	127
 * Delete:		27  91  51  126
 * Enter:		10
 * Home:		27  91  72
 * End:			27  91  70
 * Tab:			8
 * BackTab:		27  91  90
 * UpArrow:		27  91  65
 * DownArrow:	27  91  66
 * LeftArrow:	27  91  68
 * RightArrow:	27  91  67
 *
 * Windows
 * Backspace:
 * Delete:
 * Enter:
 * Home:
 * End:
 * Tab:
 * BackTab:
 * UpArrow:
 * DownArrow:
 * LeftArrow:
 * RightArrow:
*/
