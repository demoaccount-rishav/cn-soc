#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 7500
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 7550

int main() {
    struct sockaddr_in client, server;
    int sd;
    char str[512];

    // Zeroing the client structure
    bzero((char*)&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);
    client.sin_port = htons(CLIENT_PORT);

    // Zeroing the server structure
    bzero((char*)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);


    sd=socket(AF_INET,SOCK_STREAM,0);
    connect(sd,(struct sockaddr*)&server,sizeof(server));
    do{
    	printf("Enter a message:: ");
    	scanf("%s",str);
    	send(sd,str,strlen(str)+1,0);
    }while(strcmp(str,"STOP"));
    close(sd);
    return 0;
}
