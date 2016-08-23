#ifndef _CONSOLEIO_H
#define _CONSOLEIO_H

#include "Core.h"

#if defined(_WIN32)

#include <windows.h>
#include <conio.h>

#elif defined(__linux__)

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

#endif

class CORE_API Dimensions
{
public:
    unsigned int Width;
    unsigned int Height;
};
CORE_API Dimensions GetTerminalDimensions();
CORE_API void SetCursor(const unsigned int x, const unsigned int y);
CORE_API void ClearScreen();
CORE_API char GetChar();

enum CORE_API SpecialKey
{
	None,
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

CORE_API Key GetKey();

#endif
