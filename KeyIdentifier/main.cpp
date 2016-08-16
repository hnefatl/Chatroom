#include <iostream>

#if defined(_WIN32)

#include <conio.h>

#elif defined(__linux__)

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

#endif

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

int main(int argc, char *argv[])
{
	while (true)
	{
		std::cout << (int)GetChar() << std::endl;
	}

	return 0;
}
