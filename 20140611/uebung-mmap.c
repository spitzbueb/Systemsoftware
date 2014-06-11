#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[])
{
	
	if(argc < 3)
	{
		printf("USAGE: ./uebung-mmap source destination\n");
		exit(1);
	}
	
	int retcode;
	int fd;
	void *speicherbereich;
	struct stat attr;
	
	fd = open(argv[1], O_RDWR);
	
	if(fd<0)
	{
		printf("ERROR OPENING FILE 1\n");
		exit(1);
	}
	
	
	retcode = fstat(fd,&attr);
	
	if(retcode < 0)
	{
		printf("ERROR STATUS FILE\n");
		exit(1);
	}
	
	speicherbereich = mmap(0,attr.st_size, PROT_READ, MAP_SHARED, fd, 0);
	
	if(speicherbereich < 0)
	{
		printf("ERROR MMAP\n");
		exit(1);
	}
	
	close(fd);
	
	fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);
	
	if(fd<0)
	{
		printf("ERROR OPENING FILE 2\n");
		exit(1);
	}
	
	
	write(fd, speicherbereich, attr.st_size);
	
	close(fd);
	exit(0);
	
}
