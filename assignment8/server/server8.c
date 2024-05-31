//server8.c
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<time.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 7550

int main(){
    struct sockaddr_in client,server;
    int sd,nsd,clen=sizeof(client);
    char msg2[]="!! BAD REQUEST !!", msg[512], *ptr;
    time_t ti;

    bzero ((char*)&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = ntohs(SERVER_PORT);

    sd=socket(AF_INET,SOCK_DGRAM,0);
    bind(sd,(struct sockaddr*)&server,sizeof(server));
    
    while(1){
    	do{
    		memset(msg,0*0,512);
    		recvfrom(sd,msg,512,0,(struct sockaddr*)&client,&clen);
		if(!strcmp(msg,"TIME")){
			ti = time(NULL);
			ptr = ctime(&ti);
			sendto(sd,ptr,strlen(ptr)+1,0,(struct sockaddr*)&client,clen);
		}else{
    			sendto(sd,msg2,strlen(msg2)+1,0,(struct sockaddr*)&client,clen);
		}
	}while(strcmp(msg,"STOP"));
    }
    return 0;
}
