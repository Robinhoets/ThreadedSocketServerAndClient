/*
	Robert Smith's Client
*/
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


void * sock_thread(void *arg)
{

}




int main(int argc, char *argv[])
{
	int sock;
	sock= socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		printf("Could not create socket...");
	}
	puts("Socket created\n");

	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("Connection failed...");
		return 1;
	}
	puts("Connected\n");

	char message[256];
	char server_reply[256];
	while(1)
	{
		printf("Type message. Press Enter: ");
		scanf(" %256[^\n]", message);

		// send the message
		if(send(sock, message, strlen(message), 0) < 0)
		{
			printf("Send message failed...");
			return 1;
		}

		// Receive a reply
		if( recv(sock, server_reply, 512, 0) < 0)
		{
			printf("recv failed");
			break;
		}
		printf("message (%s) received!\n", message);
		//puts(server_reply);
	}

	close(sock);

	return 0;
}


