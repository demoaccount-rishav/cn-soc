//Server10
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

#define SERVER_PORT 12345
#define WINDOW_SIZE 3

int main()
{
  int server_socket,client_socket;
  struct sockaddr_in server_addr,client_addr;
  socklen_t client_addr_len=sizeof(client_addr);
  server_socket = socket(AF_INET,SOCK_STREAM,0);
  if(server_socket < 0)
  {
        printf("Socket connection failed");
        exit(EXIT_FAILURE);
  }
  server_addr.sin_family=AF_INET;
  server_addr.sin_port=htons(SERVER_PORT);
  server_addr.sin_addr.s_addr=INADDR_ANY;
  if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        printf("Bind failed");
        exit(EXIT_FAILURE);
}
 if(listen(server_socket,1) < 0){
        printf("Listen failed");
        exit(EXIT_FAILURE);
}
  printf("Server is listening....\n");
  client_socket=accept(server_socket,(struct sockaddr*)&client_addr,&client_addr_len);
if(client_socket<0)
{
        printf("Accept failure");
        exit(EXIT_FAILURE);
}
  printf("Connection established with client\n");
  char data[]="abcdefghijklmnopqrstuvwxyz";
  int start=0;
while(start<strlen(data))
    {
      int end=start+WINDOW_SIZE<strlen(data)?start+WINDOW_SIZE:strlen(data);
      send(client_socket,data+start,end-start,0);
      printf("Sent %.*s\n",end-start,data+start);
      start+=WINDOW_SIZE;
    }
  close(client_socket);
  close(server_socket);
  return 0;
}
