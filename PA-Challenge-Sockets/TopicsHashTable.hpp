#pragma once

#include <map>
#include <string>
#include <list>
#include <iostream>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

mutex topicsMutex;

using namespace std;

struct Client
{
    string name;
    string IP;
    int port;

    string getAddress() const 
    {
        return IP + ":" + to_string(port);
    }
};

class TopicData
{
public:
    string author;
    vector<Client> subscribers;

    // Default constructor
    TopicData() {}

    // Constructor that accepts author and a vector of Clients that are subscribers
    TopicData(const string& authorName, const vector<Client>& subs)
        : author(authorName), subscribers(subs) {}

    // Copy constructor
    TopicData(const TopicData& other) = default;
};

class TopicsHashTable
{
public:
    void addTopic(const string& topicName, const string& author) 
    {
        lock_guard<mutex> guard(topicsMutex); 
        topics[topicName] = TopicData(author, vector<Client>()); 
    }

    void addSubscriber(const string& topicName, const Client& subscriber)
    {
        lock_guard<mutex> guard(topicsMutex);
        auto it = topics.find(topicName);
        if (it != topics.end()) 
        {
            it->second.subscribers.push_back(subscriber);
        } else 
        {
            cout << "Topic not found!" << endl;
        }
    }

    void printTopic(const string& topicName) 
    {
        lock_guard<mutex> guard(topicsMutex); 
        if (topics.find(topicName) != topics.end()) 
        {
            cout << "Topic: " << topicName << endl;
            cout << "Author: " << topics[topicName].author << endl;
            cout << "Subscribers: ";
            for (const auto& subscriber : topics[topicName].subscribers) 
            {
                cout << subscriber.name << " ";
            }
            cout << endl;
        } else {
            cout << "Topic not found!" << endl;
        }
    }

    void publish(const Client &client, const string& topicName, const string& message) 
    {
        lock_guard<mutex> guard(topicsMutex); // for thread synchronization

        if (topics.find(topicName) != topics.end())
        {
            TopicData& currentTopic = topics[topicName];
            // Check that the client is the author
            if(currentTopic.author != client.name) 
            {
                cout << "You aren't the author of this topic.\n\nExiting publish command..." << endl;
            }
            else
            {
                // Iterate over the list of subscribers for the topic
                for (const auto& subscriber : topics[topicName].subscribers) 
                {
                    // Send message to each subscriber 
                    sendMessage(subscriber, message);
                }
            }
        } 
        else 
        {
            cout << "Topic not found!" << endl;
        }
    }

   void sendMessage(const Client& subscriber, const string& message) 
   {
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0) {
            cerr << "Error: Could not create socket." << endl;
            return;
        }

        sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(subscriber.port-1); 

        if(inet_pton(AF_INET, subscriber.IP.c_str(), &serverAddr.sin_addr) <= 0) 
        {
            cerr << "Error: Invalid IP address format." << endl;
            close(sockfd);
            return;
        }

        if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) 
        {
            cerr << "Error: Could not connect to subscriber at " << subscriber.getAddress() 
                 << ". System Error: " << strerror(errno) << endl;
            close(sockfd);
            return;
        }
        int bytesSent = send(sockfd, message.c_str(), message.length(), 0);
        if (bytesSent < 0) 
        {
            cerr << "Error: Could not send message to subscriber." << endl;
        }else{
            //cout << "Successfully sent message size " << bytesSent << endl;
        }

        close(sockfd);
    }

    // Function to get the number of topics
    size_t size() const
    {
        return topics.size();
    }

private:
    unordered_map<string, TopicData> topics;
};