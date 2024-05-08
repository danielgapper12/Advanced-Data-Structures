/*****************************************************************************************************************************************
 *                                                                                                                                       *
 *  @author: Ankit Dimri and Daniel Gapper                                                                                                                *
 *  Multithreaded TCP server. Server name 'MISTCP'                                                                                       *
 *  Server recieves a file and displays it. The server connects to each client using TCP protocol in isolted thread for each client      *
 *  I used Ankit's code as the foundation and adjusted it to meet my needs. The majority of the groundwork is Ankit's though.            *
 *****************************************************************************************************************************************/

/* header files */
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <fstream>
#include <string>
#include <cstring>
#include <signal.h>
#include <string>
#include <list>

//using namespace std;
using std::cout;
using std::cin;
using std::string;
using std::mutex;

#include "TopicsHashTable.hpp"

/* Server port number, at which it listens */
#define PORT 1721

pthread_t thread_tcp[100], thread_file[10];
int threadno_tcp = 0;
int mistfd; // server file descriptor


/* message type that will be sent by the client through TCP connection */
struct msg
{
    string command;
    string topic;
    string message;
};

/* Structure to hold the necessary parameters to pass into the threaded function */
struct req
{
    int des;
    socklen_t addlen;
    sockaddr_in clientaddr;
};

void *tcp_connection(void *);

/* Signal handler for ctrl+c to terminate the infinite server properly by closing the socket */
void sig_handler(int signo)
{
    if (signo == SIGINT)
    {
        cout << "\t Exiting..." << '\n';
        close(mistfd);
        exit(1);
    }
}

// global scope
TopicsHashTable globalTopics;

int main(int argc, char const *argv[])
{
    /* server name : Mistcp */
    sockaddr_in mistaddr;   // server address
    sockaddr_in clientaddr; // client address

    socklen_t addrlen = sizeof(clientaddr);

    /* Create socket */
    if ((mistfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        cout << "\n\t Socket creation failed...\n\t Exiting..." << '\n';
        return 0;
    }

    cout << "\n\t Socket created..." << '\n';

    memset((sockaddr *)&mistaddr, 0, sizeof(mistaddr));

    // IPv4 address family
    mistaddr.sin_family = AF_INET;                
    // Give the local machine address
    mistaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    // Port at which server listens to the requests
    mistaddr.sin_port = htons(PORT);              

    /* Bind the IP address and the port number to create the socket */
    if (::bind(mistfd, (sockaddr *)&mistaddr, sizeof(mistaddr)) != 0)
    {
        cout << "\n\t Binding failed...\n\t Exiting..." << '\n';
        return 0;
    }

    cout << "\n\t Binding successful..." << '\n';

    if ((listen(mistfd, 5)) != 0)
    {
        cout << "\n\t Server not listening..." << '\n';
        return 0;
    }

    /* Signal catching */
    signal(SIGINT, sig_handler);
    signal(SIGTSTP, sig_handler);

    cout << "\n\t Server listening..." << '\n';

    /*
     * Infinite Server listening loop
     * which creates a seperate thread for each connection established
     */
    while (1)
    {
        int connfd;
        if ((connfd = accept(mistfd, (sockaddr *)&clientaddr, &addrlen)) < 0)
            cout << "\n\t Client connection declined..." << endl;
        else
            cout << "\n\t Client connection accepted..." << endl;

        /* Filling the parameter values of the threaded function */
        req *r = new req;      // allocate memory
        bzero(r, sizeof(req)); // Clear memory
        r->addlen = addrlen;
        r->clientaddr = clientaddr;
        r->des = connfd;

        pthread_create(&thread_tcp[threadno_tcp++], NULL, tcp_connection, (void *)r);
        if (threadno_tcp == 100)
            threadno_tcp = 0;
    }
}

void *tcp_connection(void *arg)
{
    req sock = *((req *)arg);
    msg buffer;

    // Get client IP and port
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sock.clientaddr.sin_addr), clientIP, INET_ADDRSTRLEN);
    int clientPort = ntohs(sock.clientaddr.sin_port);

    string clientName = string(clientIP) + ":" + to_string(clientPort);

    // create new client from struct
    Client newClient = { clientName, clientIP, clientPort }; 

    while (1)
    {
        /* Read the packet sent by the established client */
        read(sock.des, &buffer, sizeof(buffer));

        string command(buffer.command);
        string topicName(buffer.topic);
        string messageContent(buffer.message);

        if (command == "Create") 
        {
            cout << "Command = \"Create\"" << endl;
            cout << "Number of topics before adding: " << globalTopics.size() << endl;
            globalTopics.addTopic(topicName, clientName);
            globalTopics.printTopic(topicName);
        } else if (command == "Subscribe") 
        {
            cout << "Command = \"Subscribe\"" << endl;
            globalTopics.addSubscriber(topicName, newClient);

            globalTopics.printTopic(topicName);
        } else if (command == "Publish") 
        {
            cout << "Message published by " << clientName << " forwarding to subscribers... " << endl;
            globalTopics.publish(newClient, topicName, messageContent);
        }

        cout << "-------------------------------------------" << endl;
        cout << "\n\t Author (clientName): " << clientName << endl;
        cout << "\n\t Command: " << buffer.command << endl;
        cout << "\n\t Topic: " << buffer.topic << endl;
        cout << "\n\t Message: " << buffer.message << endl;
        cout << "-------------------------------------------" << endl;
        char msg[812]; // size of command, topic and message
        string data = "\n=====File recieved====\n";
        memset(&msg, 0, sizeof(msg)); // clear the buffer
        strcpy(msg, data.c_str());
        send(sock.des, (char *)&msg, strlen(msg), 0);
    }
    // Close the socket when done
    close(sock.des);
    delete (req *)arg;
}


