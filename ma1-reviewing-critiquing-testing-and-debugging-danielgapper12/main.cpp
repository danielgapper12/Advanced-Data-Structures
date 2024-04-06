/*
ATTRIBUTES
- The overall file management was poor. Having all of the code in just main.cpp makes it cluttered 
and hard to navigate. Breaking up each class into its own .h and .cpp file is much better practice
- Another issue relating to the classes was using lowercases for the class name "queue". This is bad practice
and doesn't follow the standard CamelCase notation for class names
- Having an arrary (int* arr;) to store queue elements works, but is not as efficient as a linked list
since you have to shift elements in an array, this would be important for dequeue
- Another poor attribute was the parameter naming, specifically, enqueue(int item) which I changed 
from int x to int item to be more specific
- Error handling was poor as it often used "cout" followed by "system("pause")" and "exit(EXIT_FAILURE)",
when it would have been better to throw an exception with "throw runtime_error()" as this allows the code
to continue to run and our testCases to be integrated better

*/

#include "header.h"
#include "Queue.h"
#include "testQueue.h"

// main function
int main()
{
	TestQueue test;
	// call your test functions here!

    test.testSize();
    test.testIsEmpty();
    test.testIsFull();
	test.testDequeueEmptyQueue(); 
    test.testDequeueNonEmptyQueue();
    test.testEnqueueEmptyQueue();
    test.testEnqueueFullQueue(); 
    test.testPeekEmptyQueue();
    test.testPeekNotEmptyQueue();


 

	return 0;
}

