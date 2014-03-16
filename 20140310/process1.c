#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>


#define MSGPERM 0600
#define SIZE 20

struct message {
	long type;
	char message;
};

int main(int argc, char *argv[])
{
	struct message message_receive;
	int i, retcode;
	
	key_t key = ftok("./msgref.dat", 0);
	printf("KEY = %ld\n", (long) key);
	
	int id = msgget(key, IPC_CREAT | MSGPERM);
	
	while(1)
	{
		retcode = msgrcv(id, &message_receive, SIZE, 10,0);
		printf("retcode = %d\n",retcode);
		printf("Nachricht:\n");
		printf("%c\n", message_receive.message);
		
		if(message_receive.message == 'q')
		{
			break;
		}
	}
	
	exit(0);
}