#include <stdio.h>
#include <signal.h>


void TERMhandler(int sig)
{
	printf("Kill wurde ausgeführt\n");
}

void INThandler(int sig)
{
	printf("CTRL + C wurde gedrückt\n");
}

int main()
{
	signal(SIGINT, INThandler);
	signal(SIGTERM, TERMhandler);
	signal(SIGTSTP, SIG_IGN);
	while(1)
		pause();
}

