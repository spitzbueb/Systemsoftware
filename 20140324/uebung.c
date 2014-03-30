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

#define MAX_THREADS 5
#define MAX_LEN 16384

struct data {
	char *filename;
	int anz_linien;
	char *line[];

};

struct data daten;
int initialized = 0;
pthread_once_t oneTimeInit = PTHREAD_ONCE_INIT;

void initFunction(void)
{
	int x = 0;
	char line[256];
	
	FILE *stream = fopen(daten.filename, "rt");
	
	while(fgets(line, sizeof line, stream) != NULL)
	{
		daten.line[x] = line;
		x++;
	}
	
	daten.anz_linien = x;
	
	printf("%s\n", daten.line[2]);
	
	fclose(stream);
	
	qsort(daten.line, sizeof(daten.line)/sizeof(*daten.line), sizeof(*x));
}

void *someMagic(void *ptr)
{
	int rc;
	
	if(!initialized)
	{
		rc = pthread_once(&oneTimeInit, initFunction);
		
		if(rc < 0)
		{
			printf("Error initializing\n");
			exit(1);
		}
	}
	else
	{
		
	}
}

int main(int argc, char *argv[])
{
	if(argc < 1)
	{
		printf("Bitte Filenamen als Parameter angeben: ./uebung Dateiname\n");
		exit(1);
	}
	
	daten.filename = argv[1];
	int retcode;
	int zaehler;
	pthread_t thread[MAX_THREADS];
	
	printf("Starte Threads!\n");
	
	for(zaehler=0;zaehler<MAX_THREADS;zaehler++)
	{	
		retcode = pthread_create(&thread[zaehler], NULL, someMagic, NULL);
		
		if (retcode < 0)
		{
			printf("Error creating Thread!\n");
			exit(1);
		}
	}
	
	for(zaehler=0;zaehler<MAX_THREADS;zaehler++)
	{
		pthread_join(thread[zaehler],NULL);
		printf("Joining Thread\n");
	}
}