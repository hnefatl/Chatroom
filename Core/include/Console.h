#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "Core.h"

#include <string>

#include <Nullable.h>

#if defined(_WIN32)

#include <windows.h>
#include <conio.h>

#elif defined(__linux__)

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>

#endif

class CORE_API Dimensions
{
public:
    unsigned int Width;
    unsigned int Height;
};

enum SpecialKey
{
	None,
	Backspace,
	Delete,
	Enter,
	Home,
	End,
	Tab,
	UpArrow,
	DownArrow,
	LeftArrow,
	RightArrow,
};
class CORE_API Key
{
public:
	Key();
	Key(const char c);
	Key(const SpecialKey k);

	bool Recognised = false;
	bool Printable = false;
	SpecialKey k = SpecialKey::None;
	char c = 0;
};

class CORE_API Console
{
protected:
	Key MapKey(char c);

public:
	Console();
	~Console();

	void Start();
	void Stop();

	void Print(const std::string &Text);
	void PrintLine(const char Character);

	Dimensions GetDimensions();
	void SetCursor(const unsigned int x, const unsigned int y);
	void ClearScreen();
	void ClearSection(const unsigned int Row, const unsigned int Lines);
	char GetChar();
	Nullable<char> GetChar(const unsigned int TimeoutMs, const unsigned int Jump = 10);

	Key GetKey();
	Nullable<Key> GetKey(const unsigned int TimeoutMs, const unsigned int Jump = 10);
};



#endif
