#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

int passwort_check(const char *PW_ORIG)
{
	char *passwort;
	char temp;
	int index = 0;
	
	while(temp = getchar())
	{
		printf("*");
		passwort[index++]=temp;
		passwort[index]=='\0';
	}
}

int main()
{
	const static char *PASSWORT_ORIG = "Password";
	int pw_check;
	int tty_fd = open("/dev/tty", O_RDONLY);
	struct termios original;
	struct termios modified;
	
	tcgetattr(tty_fd, &original);
	tcgetattr(tty_fd, &modified);
	modified.c_cflag &= (~ICANON) & (~ECHO);
	modified.c_cc[VTIME] = 0;
	modified.c_cc[VMIN] = 1;
	tcsetattr(tty_fd,TCSANOW, &modified);
	
	printf("Passwort eingeben:\n");
	pw_check = passwort_check(PASSWORT_ORIG);
	
	tcsetattr(tty_fd,TCSANOW, &original);
}