#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

int main()
{
	int cs,ns,fd,n;
	int bufsize=1024;
	char *buffer=malloc(bufsize);
	struct sockaddr_in address;    // inbuilt structure in library and we are using address as its object
	char fname[255];
	address.sin_family=AF_INET;    // AF_IPv4 can also be used(check)
				       // inbuilt variables of object of the above structure and we r assigning values to it
	address.sin_port=htons(15000); // htons-hexadecimal to numericals and 15000 is the value
	address.sin_addr.s_addr=INADDR_ANY; // we can use any available address by giving value INADDR_ANY
	
	cs=socket(AF_INET,SOCK_STREAM,0); //socket creates endpoint for communication
					// 0-protocol value indicates that it can use any underlying protocol not specific(can use TCP or UDP)
	bind(cs,(struct sockaddr *)&address,sizeof(address));
	listen(cs,3);
	ns=accept(cs,(struct sockaddr *)NULL,NULL);  //accept accepts or links the server and client (used to identify the client for communication)
	recv(ns,fname,255,0); 		//receive a message from a socket
					//recv(int sockfd, void *buf, size_t len, int flags);
	fd=open(fname,O_RDONLY);        // File descriptor
	n=read(fd,buffer,bufsize);      // read from buffer
	send(ns,buffer,n,0);
	close(ns);
	return close(cs);
}


