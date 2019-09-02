#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include<pthread.h>

int main(int argc, char*argv[])
{	

	
	int sockid, newSocket;
	struct sockaddr_in addport;

	struct sockaddr_storage sStore;// robert
	socklen_t addr_size;


	// create socket id with our (family, type, protocol)
	// (how we receive and send data, constant strem of characters, default 0)
	sockid = socket(AF_INET, SOCK_STREAM, 0);
	if(sockid == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	addport.sin_family = AF_INET;	// AF_INET = IPV4 internet protocl
	addport.sin_port = htons(8888);	//port number set to 5100 -- htons converts long from host byte order to network byte order
	addport.sin_addr.s_addr = INADDR_ANY;	// s_addr member of the struct in in_addr contains the host interface address in network byte order

	// BIND	
	// run error if bind failed
	if(bind(sockid, (struct sockaddr *) &addport, sizeof(addport)) < 0 )
	{
		perror("Error...\nBind failed...\n");
		return 1;
	}
	puts("Bind successful");

	// listen for connection on port 5100
	if(listen(sockid, 5)==0)
	{
		puts("waiting for incoming connecitons...");	
	}
	else
	{
		pthread_t tid[5];
		
		while(1)
		{
			addr_size = sizeof sStore;
			newSocket = accept(sockid, (struct sockaddr *) &addport, addr_size);

			// create a thread upon client request socketthread


			//join threads

		}
	}



	return 0;
}













