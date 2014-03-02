#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#define BACKSPACE 127

void echo_funktion(int tty_fd)
{
	while(1)
	{
		FILE *tty_file = fdopen(tty_fd, "r");
		char temp = getc(tty_file);
		
		
		if(temp == '\n')
		{
			printf("Eingabe: ABBRUCH\n");
			break;
		}
		else
		{
			printf("Eingabe: %c\n", temp);
			fflush(stdout);
		}
	}
}

int passwort_check(const char *PW_ORIG)
{
	char passwort[128];
	char temp;
	int index = 0;
	
	while((temp = getchar()) != '\n')
	{
		if(temp == BACKSPACE)
		{
			if(index > 0)
			{
				index--;
				printf("\b \b");
			}
		}
		else
		{
		passwort[index]=temp;
		printf("*");
		index++;
		}
	}
	
	
	printf("\n");
	passwort[index]='\0';
	
	if(strcmp(passwort,PW_ORIG) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	const static char *PASSWORT_ORIG = "password";
	int pw_check;
	int tty_fd = open("/dev/tty", O_RDONLY);
	struct termios original;
	struct termios modified;
	
	tcgetattr(tty_fd, &original);
	tcgetattr(tty_fd, &modified);
	modified.c_lflag &= ~ECHO || ~ECHOCTL;
	tcsetattr(tty_fd,TCSANOW, &modified);
	
	printf("Passwort eingeben:\n");
	pw_check = passwort_check(PASSWORT_ORIG);
	
	if(pw_check == 1)
	{
		tcsetattr(tty_fd, TCSANOW, &original);
		modified = original;
		modified.c_lflag &= (~ICANON) || (~ECHO);
		modified.c_cc[VTIME] = 0;
		modified.c_cc[VMIN] = 1;
		tcsetattr(tty_fd, TCSANOW, &modified);
		echo_funktion(tty_fd);
	}
	else
	{
		printf("Falsches Passwort\n");
	}
	
	tcsetattr(tty_fd,TCSANOW, &original);
}