#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER PIPE_BUF

int main(int argc, char *argv[])
{
	int result;
	
	result = mkfifo("fifotest1", S_IRUSR | S_IWUSR);
	if(result < 0)
	{
		perror("mknod");
		exit(1);
	}
	
	result = mkfifo("fifotest2", S_IRUSR | S_IWUSR);
	if(result < 0)
	{
		perror("mknod");
		exit(1);
	}
}
