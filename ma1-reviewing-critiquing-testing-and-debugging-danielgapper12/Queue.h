#ifndef QUEUE_H
#define QUEUE_H

#include "header.h"

// Class for queue
class Queue // capitalized class name
{
private: // added private for better practice
	int* arr;		// array to store queue elements
	int capacity;	// maximum capacity of the queue
	int front;		// front points to front element in the queue (if any)
	int rear;		// rear points to last element in the queue
	int count;		// current size of the queue

public:
	// Queue(int size = SIZE); 	// constructor
    // Constructor to initialize queue
    Queue(int size = SIZE)
    {
        arr = new int[size];
        capacity = size;
        front = 0;
        rear = -1;
        count = 0;
    }
	// ~Queue();   				// destructor
    // Destructor to free memory allocated to the queue
    ~Queue()
    {
        delete[] arr; // you are not required to test this function; // added [] 
                    // however, are there issues with it? // yes that is why I added []
    }

	void dequeue();
	void enqueue(int item); // changed from int x to be more specific
	int peek();
	int size();
	bool isEmpty();
	bool isFull();
};


#endif