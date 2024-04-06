#ifndef TESTQUEUE_H
#define TESTQUEUE_H

#include "header.h"

class TestQueue
{
    public:
    // need one test function
    void testSize();
    void testIsEmpty();
    void testIsFull();

    // need two test functions
    void testDequeueEmptyQueue();
    void testDequeueNonEmptyQueue();
    void testEnqueueEmptyQueue();
    void testEnqueueFullQueue();
    void testPeekEmptyQueue();
    void testPeekNotEmptyQueue();
};

#endif