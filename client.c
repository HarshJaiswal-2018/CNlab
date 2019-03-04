#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

int main(int ardc,char **argv)
{
	int cs,n;
	int bufsize=1024;
	char *buffer=malloc(bufsize);	//Buffer for storing file content
	struct sockaddr_in address;
	char fname[255];
	address.sin_family=AF_INET;
	address.sin_port=htons(15000);
	
	inet_pton(AF_INET,argv[1],&address.sin_addr);	//pton-port number to numerical
	cs=socket(AF_INET,SOCK_STREAM,0);
	
	connect(cs,(struct sockaddr *)&address,sizeof(address));	// send connection request to the socket(cs) in the server
	printf("\nEnter the file name: ");			// create a file or use other existing file
	scanf("%s",fname);
	
	send(cs,fname,255,0);	//sending the file data to the buffer
	while((recv(cs,buffer,bufsize,0))>0)
	printf("%s",buffer);
	printf("\nEOF\n");
	return close(cs);
}

