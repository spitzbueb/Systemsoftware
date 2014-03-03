#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	pid_t child1, child2, status;
	
	child1 = fork();
	
	if(child1 == 0)
	{
		sleep(10);
		printf("Kind 1 %d\n",getpid());
		exit(1);
	}
	
	child2 = fork();
	
	if(child2 == 0)
	{
		sleep(30);
		printf("Kind 2 %d\n",getpid());
		exit(1);
	}
	
	sleep(20);
	printf("Elternprozess %d\n",getpid());
	
	int i;
	
	for(i=0; i<2;i++)
	{
		int pid = wait(&status);
		printf("Einsammeln der Prozesse\n");
		printf("%d\n",pid);
	}
		
	
}
