#include <iostream>

#include <Console.h>

int main(int argc, char *argv[])
{
	Console Term;
	Term.Start();
	while (true)
	{
		char In = Term.GetChar();
		if (In == 9)
			Term.ClearScreen();
		else
			std::cout << (int)In << std::endl;
	}
	Term.Stop();

	return 0;
}
