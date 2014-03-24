#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>

pthread_mutex_t lock;
long counter = 0L;
pthread_barrier_t barrier;


void *thread_counting(void *ptr)
{
	int fd;
	int i;
	long ending;
	char buffer[16384];
	char *filename = (char*) ptr;
	
	pthread_mutex_lock(&lock);
	
	ending = 0L;
	
	fd = open(filename, O_RDONLY);
	
	if (fd < 0)
	{
		printf("Error reading File\n");
		exit(1);
	}
	
	while(1)
	{
		ssize_t size_read = read(fd, buffer, 16384);
		
		if (size_read == 0)
		{
			break;
		}
		
		for(i=0; i<size_read; i++)
		{
			unsigned char c = buffer[i];
			ending = ending + (int) c;
		}
	}
	
	printf("Summe für File %s ist gleich %ld\n", filename, ending);
	
	pthread_mutex_unlock(&lock);
	
	printf("Thread wartet!\n");
	
	pthread_barrier_wait(&barrier);
	
	pthread_mutex_lock(&lock);
	
	counter = counter + ending;
	
	pthread_mutex_unlock(&lock);
}

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		printf("Dateinamen als Parameter angeben: ./process1 dateiname1 dateiname2\n");
		exit(1);
	}
	
	int zaehler;
	int retcode;
	int ergebnis[argc-1];
	
	pthread_t thread[argc-1];
	
	pthread_barrier_init(&barrier, NULL, argc-1);
	
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("Mutex init failed\n");
		exit(1);
	}
	
	printf("Starte Prozesse!\n");
	
	for(zaehler=1;zaehler<argc;zaehler++)
	{
		printf("Starte Thread %d\n", zaehler);
		retcode = pthread_create(&thread[zaehler], NULL, thread_counting, argv[zaehler]);
		
		if(retcode < 0)
		{
			printf("Error creating thread %d errno=%d, retcode=%d\n", zaehler, errno, retcode);
			exit(1);
		}
	}
	
	for(zaehler=1;zaehler<argc;zaehler++)
	{
		pthread_join(thread[zaehler], NULL);
		printf("Joining Thread %d\n", zaehler);
	}
	
	pthread_mutex_destroy(&lock);
	
	printf("Summe allgemein: %ld\n", counter);
		
}