#include "header.h"

// Node class 
template <typename N>
class Node 
{
    public:
        // constructor
        Node(const N& newData) : data(newData), next(nullptr) {}

        // getters
        N getData() const
        {
            return data;
        }
        Node<N>* getNext() const
        {
            return next;
        }

        // setters
        void setData(N Data)
        {
            data = Data;
        }
        void setNext(Node<N>* Next)
        {
            next = Next;
        }
    
    private:
        // moved from public, need to check setters/getters work
        N data; 
        Node<N>* next;
};