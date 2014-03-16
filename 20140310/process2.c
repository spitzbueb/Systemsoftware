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
	struct message message_send;
	int i, retcode;
	
	key_t key = ftok("./msgref.dat", 0);
	printf("KEY = %ld\n", (long) key);
	
	int id = msgget(key, IPC_CREAT | MSGPERM);
		
	message_send.type = 10;
	
	while(1)
	{
		
		message_send.message = fgetc(stdin);
	
	
		retcode = msgsnd(id, &message_send, SIZE, 0);
		printf("retcode: %d\n", retcode);
		
		if(message_send.message == 'q')
		{
			break;
		}
	}
	
	exit(0);
}