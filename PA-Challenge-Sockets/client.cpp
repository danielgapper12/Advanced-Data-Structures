/*****************************************************************************************************************************************
 *                                                                                                                                       *
 *  @author: Ankit Dimri and Daniel Gapper                                                                                               *
 *  TCP client which sends the file name and the file to the server                                                                      *
 *  I used Ankit's code as the foundation and adjusted it to meet my needs. The majority of the groundwork is Ankit's though.            *
 *****************************************************************************************************************************************/

/* header files */
#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fstream>
#include <thread>
#include <functional>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <fstream>
#include <string>
#include <string>
#include <list>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <iostream>

using namespace std;

/* port at which the server operates */
#define PORT 1721
#define SA sockaddr

/* Socket file descriptor */
int sockfd;

/* Structure of the message that will be sent to the server */
struct msg
{
	string command;
    string topic;
    string message;
};

/* Signal handler for ctrl+c to terminate the infinite client properly by closing the socket */
void sig_handler(int signo)
{

	/* signal handler */
	if (signo == SIGINT)
	{
		cout << "\t Exiting..." << '\n';
		close(sockfd);
		exit(1);
	}
}

/* Function called once the connection with the server is established */
void connection(int sockfd)
{
	msg buffer;

	/* Signal catching */
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);

	/* Infinite loop */
	while (1)
	{
		string temp;
		cout << "\"Create\", \"Subscribe\", and \"Publish\" are the only valid commands. \nEnter any letter and press enter to enter a command..." << endl;
        cin >> temp;
		cout << "-------------------------------------------" << endl;
		cout << "Enter the command: ";
		getline(cin, temp);
        getline(cin, buffer.command); // Read the command

        cout << "\nEnter the topic: ";
        getline(cin, buffer.topic); // Read the topic

        if (buffer.command == "Publish")
        {
            cout << "\nEnter the message: ";
            getline(cin, buffer.message); // Read the message
        }
		cout << "-------------------------------------------" << endl;

		write(sockfd, &buffer, sizeof(buffer));

		cout << "\n Command: " << buffer.command << endl;
		cout << "\n Topic: " << buffer.topic << endl;
		cout << "\n Message: " << buffer.message << endl;

		cout << "Awaiting server response..." << endl;
		
		if (buffer.command == "Subscribe")
        {
            cout << "\nWaiting for messages... " << endl;
        }
		char msg[812]; // size of command, topic and message
		memset(&msg, 0, sizeof(msg)); 
		recv(sockfd, (char *)&msg, sizeof(msg), 0);
		cout << "Server: " << msg << endl;
	}
}

void* handleIncomingMessages(void* arg) 
{
    int clientSockfd = *((int*)arg);
    char buffer[1024];
    while (true) 
	{
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSockfd, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            close(clientSockfd);
            break;
        }
        cout << "Message received: " << buffer << endl;
    }
    return NULL;
}

void* startListening(void* arg) 
{
    int port = *((int*)arg);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
	{
        cerr << "Failed to create socket for listening." << endl;
        return NULL;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (::bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) != 0) 
	{
        cerr << "Bind failed on port: " << port << endl;
        close(sockfd);
        return NULL;
    }

    if (listen(sockfd, 5) < 0) 
	{
        cerr << "Listen failed on port: " << port << endl;
        close(sockfd);
        return NULL;
    }

    while (true) 
	{
        int clientSockfd = accept(sockfd, NULL, NULL);
        if (clientSockfd < 0) 
		{
            cerr << "Failed to accept connection." << endl;
            continue;
        }
        pthread_t thread;
        pthread_create(&thread, NULL, handleIncomingMessages, (void*)&clientSockfd);
        pthread_detach(thread);
    }
    return NULL;
}



int findFreePort() 
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
	{
        cerr << "Failed to create socket." << endl;
        return -1;
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = 0;  

    if (::bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) != 0) 
	{
        cerr << "Failed to bind socket." << endl;
        close(sockfd);
        return -1;
    }

    socklen_t addr_len = sizeof(addr);
    if (getsockname(sockfd, (struct sockaddr*)&addr, &addr_len) < 0) 
	{
        cerr << "Failed to get socket name." << endl;
        close(sockfd);
        return -1;
    }

    int freePort = ntohs(addr.sin_port);
    close(sockfd);  
    return freePort;
}



int main(int argc, char const *argv[])
{
    int listeningPort = findFreePort();
	pthread_t listenerThread;
	sockaddr_in servaddr, clientaddr;

	pthread_create(&listenerThread, NULL, startListening, (void*)&listeningPort);
	pthread_detach(listenerThread);  

	/* socket create and varification */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(PORT);

	/* connect the client socket to server socket */
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
	{
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	connection(sockfd);
}
