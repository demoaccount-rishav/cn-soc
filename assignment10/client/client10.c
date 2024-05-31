#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

#define SERVER_PORT 12345

int main()
{
 int client_socket;
 struct sockaddr_in server_addr;
 client_socket=socket(AF_INET,SOCK_STREAM,0);
if(client_socket<0)
{
        printf("Socket creation failed");
        exit(EXIT_FAILURE);
}
 server_addr.sin_family=AF_INET;
 server_addr.sin_port=htons(SERVER_PORT);
 server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
 if(connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        printf("Connection failed");
        exit(EXIT_FAILURE);
}
 printf("Connected to the server:\n");
 char buff[256];
 ssize_t bytes_received;
 while((bytes_received=recv(client_socket,buff,sizeof(buff),0))>0)
  {
   printf("Received = %.*s\n",(int)bytes_received,buff);
   send(client_socket,"ACK",3,0);
  }
 close(client_socket);
 return 0;

}
