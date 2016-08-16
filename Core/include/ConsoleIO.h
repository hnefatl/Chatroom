#ifndef _CONSOLEIO_H
#define _CONSOLEIO_H

#if defined(_WIN32)

#include <windows.h>
#include <conio.h>

#elif defined(__linux__)

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

#endif

class Dimensions
{
public:
    unsigned int Width;
    unsigned int Height;
};
Dimensions GetTerminalDimensions();
void SetCursor(const unsigned int x, const unsigned int y);
void ClearScreen();
char GetChar();

enum SpecialKey
{
	Backspace,
	Delete,
	Enter,
	Home,
	End,
	Tab,
	BackTab,
	UpArrow,
	DownArrow,
	LeftArrow,
	RightArrow,
};
class Key
{
public:
	Key();
	Key(const char c);
	Key(const SpecialKey k);

	bool Recognised;
	bool Printable;
	SpecialKey k;
	char c;
};

Key GetKey();

#endif
