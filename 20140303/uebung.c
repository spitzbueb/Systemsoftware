#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void my_handler(int signum)
{
	printf("SIGUSR1 erhalten. Beende Dämon!\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	int fork_result;
	int pipes[2];
	char buff[1024];
	int ret_code;
	int process = 0;
	
	printf("Start Parent!\n");
	
	ret_code = pipe(pipes);
	
	if (ret_code != 0)
	{
		printf("Error creating pipe");
		exit(1);
	}
	
	fork_result = fork();
	
	if (fork_result == 0) 
	{
		printf("Childish Activity!\n");
		fork_result = fork();
		
		if (fork_result != 0)
		{
			printf("Exiting Child! %i\n", fork_result);
			exit(0);
		}
		
		printf("In Grandchild!\n");
		
		pid_t pid;
		
		pid = getpid();
		
		process = (int) pid;
		
		close(pipes[0]);
		ret_code=write(pipes[1], &process, sizeof(process));
			
		if (ret_code < 0)
		{
			printf("Error writing to pipe!\n");
			exit(2);
		}
		sleep(30);
		signal(SIGUSR1, my_handler);
		while(1)
		{
			printf("Waiting for Signal\n");
			sleep(5);
			pause();
		}
	}
	
	close(pipes[1]);
	int status;
	printf("Parent waiting for Child!\n");
	wait(&status);
	printf("Child terminated\n");
	
	ret_code = read(pipes[0], &process, sizeof(process));
	
	close(pipes[0]);
	
	printf("Process of Daemon: %d\n", process);
	
	kill(process, SIGUSR2);
	
	printf("Parent Done!\n");
		
}