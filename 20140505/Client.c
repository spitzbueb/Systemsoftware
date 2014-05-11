#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#include <WinSock.h>
#include <stdint.h>
#include <time.h>

int main()
{
          WSADATA wsa;
          SOCKET s;
          struct sockaddr_in server;
          char *message;
          int rc;
          
          printf("Initializing Winsock...\n");
          if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
          {
                 printf("Failed to Winsock: %d\n", WSAGetLastError());
                 return 1;
          }
          printf("Initialized!\n");
          
          if((s=socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
          {
                 printf("Could not create socket: %d\n", WSAGetLastError());
          }
          printf("SOCKET created!\n");
          
          server.sin_addr.s_addr = inet_addr("127.0.0.1");
          server.sin_family = AF_INET;
          server.sin_port = htons(6666);
          
          if(connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
          {
                        printf("connect error\n");
                        return 1;
          }
          
          printf("Connected\n");
          
          while(1)
          {
                  fgets(message,256,stdin);
                  
                  rc = send(s, message, strlen(message),0);
                  if(rc != 0)
                  {
                        printf("Error sending message\n");
                  }
                  
                  rc = recv(s,message,256,0);
                  if(rc != 0)
                  {
                        printf("Error receiving message\n");
                  }
                  
                  printf("Message was: %s",message);
          }
}
