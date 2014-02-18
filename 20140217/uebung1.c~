#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	struct stat stat_buf;
	int r;
	char *name = "tmp";
	int e;
	
	r = stat(name, &stat_buf);
	
	if(r < 0)
	{
		int myerrno = errno;
		const char *error_string = strerror(myerrno);
		printf("errno=%d\nmessage=%s\n",myerrno,error_string);
		
		/* Ordner erstellen */
		e = mkdir(name,S_IRWXU);
	}
}