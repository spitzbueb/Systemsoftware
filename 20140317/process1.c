#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock;

void *thread_run(void *ptr)
{
	
	int r = rand() % 20;
	sleep(r);
	char buffer[256];
	
	pthread_mutex_lock(&lock);
	
	printf("%s\n", (char*) ptr);
	printf("Thread %ld\n", pthread_self());
	
	read(STDIN_FILENO, buffer, 256);
	
	write(STDIN_FILENO, buffer, 256);
	
	sleep(10);
	
	pthread_mutex_unlock(&lock);
}

int main(int argc, char *argv[])
{
	int ret_code;
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("Mutex init failed\n");
		exit(3);
	}
	
	printf("Starte Prozesse!\n");
	
	ret_code = pthread_create(&thread1, NULL, thread_run, "Thread 1\n");
	if (ret_code < 0) 
	{
		printf("Error reading from pipe ret_code=%d errno=%d\n", ret_code, errno);
	  	exit(3);
    	}
    	
    	ret_code = pthread_create(&thread2, NULL, thread_run, "Thread 2\n");
	if (ret_code < 0) 
	{
		printf("Error reading from pipe ret_code=%d errno=%d\n", ret_code, errno);
	  	exit(3);
    	}
    	
    	ret_code = pthread_create(&thread3, NULL, thread_run, "Thread 3\n");
	if (ret_code < 0) 
	{
		printf("Error reading from pipe ret_code=%d errno=%d\n", ret_code, errno);
	  	exit(3);
    	}
    	
    	pthread_join(thread1, NULL);
    	pthread_join(thread2, NULL);
    	pthread_join(thread3, NULL);
    	pthread_mutex_destroy(&lock);
}