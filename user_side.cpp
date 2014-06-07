#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#define PROTOPORT 1532	/* default protocol port number */
char localhost[] = "localhost";	/* default host name */
char recvBuf[1024];

/* It opens a connection to the host name rhost that is listening on the 
specified port. It returns the socket descriptor, or -1 in case of failure. */
int user_socket(const char *rhost, unsigned short port);

int main(int argc, char* argv[])
{
	int cs;			/* user/client socket */
	int port;		/* protocol port number */
	char* host;		/* pointer to host name */
	int n = 0;		/* number of char read in line */
	char c;

	/* Checks command-line for arguments else makes default protoport as port number. */
	if(argc < 2)
	{
		port = atoi(argv[2]);	/* if protocol port is specified */
	}
	else
	{
		port = PROTOPORT;
	}
	if(port <= 0)
	{
		fprintf(stderr, "Bad port number %s\n", argv[2]);
		exit(1);
	}
	/* Check host argument and assign host name */
	if(argc > 1)
	{
		host = argv[1];			/* if host name is specified */
	}
	else
	{
		host = localhost;
	}
	/* initialize the user/client socket structure by connecting to server */
	if((cs = user_socket(host, port)) < 0)
	{
		fprintf(stderr, "Cannot connect to server\n");
		exit(1);
	}
////==========================================================================\\\\

	int bytesSent = 0;
	int bytesRecv = recv(cs, recvBuf, sizeof(recvBuf), 0);
	printf("Established connection with DataCenter...initiate contact!\n\n");
	string sendStr = "";
	string recvStr = "";

	while(true)
	{
		getline(cin, sendStr);

		bytesSent = send(cs, sendStr.c_str(), sendStr.length(), 0);
		bytesRecv = recv(cs, recvBuf, sizeof(recvBuf), 0);

		recvBuf[bytesRecv] = '\0';
		cout<<recvBuf<<"\n";

		if( (sendStr == "exit") || (sendStr == "end") )
		{
			break;
		}
	}

	close(cs);
	printf("Closed connection with DataCenter...ending program!\n\n");
	return 0;
}

/* It opens a connection to the host name rhost that is listening on the 
specified port. It returns the socket descriptor, or -1 in case of failure. */
int user_socket(const char *rhost, unsigned short port)
{
	struct hostent *ptrh;  /* pointer to a host table entry     */
	struct sockaddr_in sad;/* structure to hold server's address*/
	int    fd;             /* socket descriptor                 */

	memset((char *)&sad, 0, sizeof(sad)); /* clear sockaddr structure */
	sad.sin_family = AF_INET;  /* set family to Internet */
	sad.sin_port = htons((u_short)port); 

	/* Convert host name to equivalent IP address and copy sad */
	ptrh = gethostbyname(rhost);
	if (((char *)ptrh) == NULL)
	{
		fprintf(stderr, "invalid host: %s\n", rhost);
		return (-1);
	}
	memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length);
	/* Create a socket */
	fd = socket(PF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		fprintf(stderr, "socket creation failed\n");
		return (-1);;
	}
	/* Connect the socket to the specified server */
	if (connect(fd, (struct sockaddr *)&sad, sizeof(sad)) < 0)
	{
		fprintf(stderr, "connect failed\n");
		return (-1);
	}

	return fd;
}
