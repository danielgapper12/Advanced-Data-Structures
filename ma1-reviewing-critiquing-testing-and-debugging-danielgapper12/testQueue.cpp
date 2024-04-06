#include "header.h"
#include "Queue.h"
#include "testQueue.h"

// need one test function
/*
Test ID: 1

Test Description:

Test Steps:

Test Data:

Preconditions:

Postconditions:

Expected Results:

Results:

*/
void TestQueue::testSize()
{
    Queue myQueue;
    cout << myQueue.size() << endl;
    if (myQueue.size() == 0)
    {
        cout << "PASS\nNewly created Queue has size of 0" << endl;
    } else{
        cout << "FAIL\nNewly created Queue does not have size of 0" << endl;
    }

    myQueue.enqueue(10);
    cout << myQueue.size() << endl;
    if (myQueue.size() == 1)
    {
        cout << "PASS\nQueue has size of 1 after 1 addition" << endl;
    } else{
        cout << "FAIL\nQueue does not have size of 1 after 1 addition" << endl;
    }

    myQueue.enqueue(15);
    if (myQueue.size() == 2)
    {
        cout << "PASS\nQueue has size of 2 after 2 additions" << endl;
    } else{
        cout << "FAIL\nQueue does not have size of 2 after 2 additions" << endl;
    }

    myQueue.dequeue();
    if (myQueue.size() == 1)
    {
        cout << "PASS\nQueue has size of 1 after dequeue" << endl;
    } else{
        cout << "FAIL\nQueue does not have size of 1 after dequeue" << endl;
    }

}

/*
Test ID: 2

Test Description:

Test Steps:

Test Data:

Preconditions:

Postconditions:

Expected Results:

Results:

*/
void TestQueue::testIsEmpty()
{
    Queue myQueue;
    if (myQueue.isEmpty())
    {
        cout << "PASS\nisEmpty says Initialized Queue is empty" << endl;
    } else{
        cout << "FAIL\nisEmpty says Initialized Queue is not empty" << endl;
    }
    myQueue.enqueue(12);
    if (myQueue.isEmpty())
    {
        cout << "FAIL\nisEmpty says Queue is empty" << endl;
    } else{
        cout << "PASS \nisEmpty says Queue is not empty" << endl;
    }
    myQueue.dequeue();
    if (myQueue.isEmpty())
    {
        cout << "PASS\nisEmpty says dequeue created empty Queue" << endl;
    } else{
        cout << "FAIL \nisEmpty says dequeue created nonempty Queue" << endl;
    }
}

/*
Test ID:

Test Description:

Test Steps:

Test Data:

Preconditions:

Postconditions:

Expected Results:

Results:

*/
void TestQueue::testIsFull()
{
    Queue myQueue(2); // sets capacity to 2 for testing
    if(myQueue.isFull())
    {
        cout << "FAIL \nisFull() says a newly created Queue is full" << endl;
    } else{
        cout << "PASS \nisFull() says a newly created Queue is not full" << endl;
    }
    myQueue.enqueue(16);
    if(myQueue.isFull())
    {
        cout << "FAIL \nisFull() says a non full Queue is full" << endl;
    } else{
        cout << "PASS \nisFull() says a non full Queue is not full" << endl;
    }
    myQueue.enqueue(7);
    if(myQueue.isFull())
    {
        cout << "PASS \nisFull() says a full Queue is full" << endl;
    } else{
        cout << "FAIL \nisFull() says a full Queue is not full" << endl;
    }

}

// need two test functions
/*
Test ID:

Test Description:

Test Steps:

Test Data:

Preconditions:

Postconditions:

Expected Results:

Results:

*/
void TestQueue::testDequeueEmptyQueue() // could have problem since dequeue() is throwing error and exiting so catch never runs
{
    Queue myQueue;
    try {
        myQueue.dequeue();
        cout << "FAIL \nDequeued from empty queue" << endl;
    } catch (...) {
        cout << "PASS \nThrew exception when dequeueing from empty queue" << endl;
    }
}

/*
Test ID:

Test Description:

Test Steps:

Test Data:

Preconditions:

Postconditions:

Expected Results:

Results:

*/
void TestQueue::testDequeueNonEmptyQueue()
{
    Queue myQueue;
    myQueue.enqueue(10);
    myQueue.enqueue(11);

    try {
        myQueue.dequeue();
        if (myQueue.size() == 1) 
        {
            cout << "PASS \nDequeued successfully from a non empty queue" << endl;
        } else {
            cout << "FAIL \nDequeue did not update queue size correctly" << endl;
        }
    } catch (...) {
        cout << "FAIL: Threw exception when dequeueing from a non empty queue" << endl;
    }
}

/*
Test ID:

Test Description:

Test Steps:

Test Data:

Preconditions:

Postconditions:

Expected Results:

Results:

*/
void TestQueue::testEnqueueEmptyQueue()
{
    Queue q;

    q.enqueue(10);

    if (q.isEmpty() == false)
    {
        cout << "PASS \nEnqueue successfully added element " << endl;
    } else{
        cout << "FAIL \nElement not enqueued after enqueueing one element" << endl;
    }
}

/*
Test ID:

Test Description:

Test Steps:

Test Data:

Preconditions:

Postconditions:

Expected Results:

Results:

*/
void TestQueue::testEnqueueFullQueue()
{
    Queue q(1);

    q.enqueue(10);
    try{
        q.enqueue(9);
        cout << "FAIL \nAble to enqueue an element to a full Queue" << endl;
    
    } catch (...){
        cout << "PASS: Threw exception when enqueueing an element to a full Queue" << endl;
    }
}

/*
Test ID:

Test Description:

Test Steps:

Test Data:

Preconditions:

Postconditions:

Expected Results:

Results:

*/
void TestQueue::testPeekEmptyQueue()
{
    Queue q;
    try{
        q.peek();
        cout << "FAIL \nNo exception thrown when peeking front element of an empty Queue" << endl;
    } catch (...){
        cout << "PASS \nThrew exception when attempting to peek an empty Queue" << endl;
    }
}

/*
Test ID:

Test Description:

Test Steps:

Test Data:

Preconditions:

Postconditions:

Expected Results:

Results:

*/
void TestQueue::testPeekNotEmptyQueue()
{
    Queue q;
    q.enqueue(10);
    q.enqueue(6);

    int front = q.peek();
    cout << "peek() prints" << front << endl;
    if (front == 10)
    {
        cout << "PASS \nPeek successfully got front element from Queue" << endl;
    } else{
        cout << "FAIL \nPeek did not get correct front element from Queue" << endl;
    }
}