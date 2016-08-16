#include <iostream>

#include <ConsoleIO.h>

int main(int argc, char *argv[])
{
	while (true)
	{
		char In = GetChar();
		if (In == 9)
			ClearScreen();
		else
			std::cout << (int)In << std::endl;
	}

	return 0;
}
