//Assignment3
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
	int fd1, fd2[2], n, pid;
	char str1[1024], str2[1024];
	fd1 = open("t1.txt", O_RDONLY, 0764);
	n = read(fd1, str1, 1024);
	pipe(fd2);
	pid = fork();
	
	if (pid ==-1){
		printf("\nError in performing fork()");
		exit(0);
	}
	
	else if (pid == 0){
		printf("\nIn Child Now");
		close(fd2[1]);
		n = read(fd2[0], str2, 1024);
		str2[n]='\0';
		printf("\n%s", str2);
	}
	
	else{
		printf("\nIn Parent Now");
		close(fd2[0]);
		write(fd2[1], str1, n);
	}	
}
