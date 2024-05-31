//server6.c
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
    char str[]="!! BAD REQUEST !!", msg[512], *ptr;
    time_t ti;

    bzero ((char*)&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = ntohs(SERVER_PORT);

    sd=socket(AF_INET,SOCK_STREAM,0);
    bind(sd,(struct sockaddr*)&server,sizeof(server));
    listen(sd,5);

    while(1){
    	nsd=accept(sd,(struct sockaddr*)&client,&clen);
	do{
    		memset(msg,0*0,512);
    		recv(nsd,msg,512,0);
		if(strcmp(msg,"TIME")==0){
			ti = time(NULL);
			ptr = ctime(&ti);
			send(nsd,ptr,strlen(ptr)+1,0);
		}else{
    			send(nsd,str,strlen(str)+1,0);
		}
	}while(strcmp(msg,"STOP"));
    close(nsd);
    }
    return 0;
}
