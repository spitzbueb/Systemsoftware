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
long counter[256];

void *thread_counting(void *ptr)
{
	int fd;
	int i;
	int ending;
	char buffer[16384];
	char *filename = (char*) ptr;
	
	pthread_mutex_lock(&lock);
	
	for(i=0;i<257;i++)
	{
		counter[i] = 0L;
	}
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error reading File errno=%d file=%s\n", errno, filename);
		exit(1);
	}
	
	while (1)
	{
		ssize_t size_read = read(fd, buffer, 16384);
		
		if (size_read == 0 )
		{
			break;
		}
		
		for(i=0; i<size_read; i++)
		{
			unsigned char c = buffer[i];
			counter[c]++;
		}
	}
	
	printf("---------------------------------------------------------------\n");
	printf("Filename: %s\n", filename);
	printf("---------------------------------------------------------------\n");
	
	for(i=0; i<256; i++)
	{
		long val = counter[i];
		
		if (! (i & 007)) 
		{
			printf("\n");
			fflush(stdout);
		}
		
		if ((i & 0177) < 32 || i == 127) 
		{
			printf("\\%03o: %10ld ", i, val);
		} 
		else 
		{
			printf("%4c: %10ld ", (char) i, val);
		}
	}
	printf("\n\n");
	
	pthread_mutex_unlock(&lock);
}

int main(int argc, char *argv[])
{
	
	if(argc <= 1)
	{
		printf("Dateinamen als Parameter angeben. Beispiel: ./uebung datei.txt\n");
		exit(1);
	}
	
	int zaehler;
	int retcode;
	pthread_t thread[argc-1];
	
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("Mutex init failed\n");
		exit(3);
	}
	
	printf("Starte Prozesse!\n");
	
	for(zaehler=1;zaehler<argc;zaehler++)
	{
		printf("Starte Thread %d\n", zaehler);
		retcode = pthread_create(&thread[zaehler], NULL, thread_counting, argv[zaehler]);
		if(retcode < 0)
		{
			printf("Error reading from pipe retcode=%d errno=%d thread=%d\n", retcode, errno, zaehler);
			exit(3);
		}
	}
	
	
	
	for(zaehler=1;zaehler<argc;zaehler++)
	{
		pthread_join(thread[zaehler], NULL);
		printf("Joining Thread %d\n", zaehler);
	}
	
	pthread_mutex_destroy(&lock);
	
	
}