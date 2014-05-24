#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#include <WinSock.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <ws2tcpip.h>


#define DEFAULT_PORT 6666

int main()
{
          WSADATA wsaData;
          int rc;
          
          SOCKET listensocket = INVALID_SOCKET;
          SOCKET clientsocket = INVALID_SOCKET;
          
          struct addrinfo *result = NULL;
          struct addrinfo hints;
          
          char *message;
          char *port = "6666";
          
          rc = WSAStartup(MAKEWORD(2,2), &wsaData);
          if(rc != 0)
          {
                printf("Error WSAStartup\n");
                return 1;
          }
          
          ZeroMemory(&hints, sizeof(hints));
          hints.ai_family = AF_INET;
          hints.ai_socktype = SOCK_STREAM;
          hints.ai_protocol = IPPROTO_TCP;
          hints.ai_flags = AI_PASSIVE;
          
          rc = getaddrinfo(NULL,port,&hints,&result);
          if(rc != 0)
          {
                printf("getaddrinfo failed\n");
                WSACleanup();
                return 1;
          }
          
          listensocket = socket(result->ai_family,result->ai_socktype,result->ai_protocol);
          if(listensocket == INVALID_SOCKET)
          {
                          printf("Error opening listensocket\n");
                          freeaddrinfo(result);
                          WSACleanup();
                          return 1;
          }
          
          rc = bind(listensocket, result->ai_addr, (int)result->ai_addrlen);
          if(rc == SOCKET_ERROR)
          {
                printf("bind failed\n");
                freeaddrinfo(result);
                closesocket(listensocket);
                WSACleanup();
                return 1;
          }
          
          freeaddrinfo(result);
          
          rc = listen(listensocket, SOMAXCONN);
          if(rc == SOCKET_ERROR)
          {
                printf("listen failed\n");
                closesocket(listensocket);
                WSACleanup();
                return 1;
          }
          
          while(1)
          {
                  clientsocket = accept(listensocket,NULL,NULL);
                  
                  if(clientsocket == INVALID_SOCKET)
                  {
                                  printf("error accepting\n");
                                  closesocket(listensocket);
                                  WSACleanup();
                                  return 1;
                  }
                  
                  rc = recv(clientsocket, message, 256,0);
                  if(rc != 0)
                  {
                        printf("Error sending message\n");
                  }
                  
                  printf("Got Message: %s",message);
                  
                  rc = send(clientsocket,message,strlen(message),0);
                  if(rc != 0)
                  {
                        printf("Error receiving message\n");
                  }
          }
}
