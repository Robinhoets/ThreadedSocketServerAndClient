#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char*argv[])
{	

	
	int sockid;
	struct sockaddr_in addport;
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
	listen(sockid, 1);	// on that socket, 1 is the number of participants that can wait for a connection
	puts("waiting for incoming connecitons...");

	struct sockaddr_in client;	// client is the active participant
	int socketaddress_size = sizeof(struct sockaddr_in);
	int client_sock = accept(sockid, (struct sockaddr *) &client, (socklen_t*) &socketaddress_size);
	if(client_sock < 0)
	{
		perror("Accept failed...");
		return 1;
	}
	puts("Accept passed... Connection accepted");


	char message_buffer[512];
	// (sockid, where we store message, message length, flags)
	int read;	// returns -1 if fail

	while((read = recv(client_sock, message_buffer, 256, 0)) > 0)
	{
		write(client_sock, message_buffer, strlen(message_buffer));
	}

	if(read == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read == -1)
	{
		perror("recv failed");
	}



	return 0;
}













