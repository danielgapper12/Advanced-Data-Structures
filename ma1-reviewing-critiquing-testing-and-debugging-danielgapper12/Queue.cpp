#include "header.h"
#include "Queue.h"
#include "testQueue.h"

// Utility function to remove front element from the queue
void Queue::dequeue()
{
	// check for queue underflow
	if (isEmpty())
	{
		throw runtime_error("Underflow Exception: Tried to dequeue an element from an empty queue");
		// cout << "UnderFlow\nProgram Terminated" << endl;
		// exit(EXIT_FAILURE);
	}

	cout << "Removing " << arr[front] << endl;

	front = (front + 1) % capacity;
	count--;
}

// Utility function to add an item to the queue
void Queue::enqueue(int item)
{
	// check for queue overflow
	if (isFull())
	{
		throw runtime_error("Overflow Exception: Tried to enqueue to a full queue");
		// cout << "OverFlow\nProgram Terminated" << endl;
		// exit(EXIT_FAILURE);
	}

	cout << "Inserting " << item << '\n';

	rear = (rear + 1) % capacity;
	arr[rear] = item; // changed from arr[rear] = size();
	count++;
}

// Utility function to return front element in the queue
int Queue::peek()
{
	if (isEmpty())
	{
		throw runtime_error("Underflow Exception: Tried to peek front element from an empty queue");
	
		// cout << "UnderFlow\nProgram Terminated" << endl;
		// system("pause");
		// exit(EXIT_FAILURE);
	}
	return arr[front]; // changed from returing arr[rear] to arr[front]
}

// Utility function to return the size of the queue
int Queue::size()
{
	return count; // changed from count + 1
}

// Utility function to check if the queue is empty or not
bool Queue::isEmpty()
{
	return (size() == 0);
}

// Utility function to check if the queue is full or not
bool Queue::isFull()
{
	return (capacity == size()); // changed size() - 1 to size()
}