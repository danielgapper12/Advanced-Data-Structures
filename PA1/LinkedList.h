#include "header.h"
#include "Node.h"

// Linked list class
template <typename N>
class LinkedList 
{
private:
    Node<N>* head;

public:
    // constructor
    LinkedList() : head(nullptr) {}

    // destructor
    ~LinkedList() 
    {
        while (head != nullptr) 
        {
            Node<N>* temp = head;
            head = head->getNext(); 
            delete temp;
        }
    }

    Node<N>* getHead()
    {
        return head;
    }

    // insert at the front of the list
    void insertAtFront(const N& newData);

    // display all commands
    void displayAllCommands() const;

    bool isEmpty() const;

    int size() const;

    bool searchCommand(const string& cmd) const;

    N getRandomCommand(const LinkedList<N>& commandsList);
    
    N getElementAtIndex(int index) const;

    void remove(const string& commandToRemove);

};

// insert at the front of the list
template <typename N>
void LinkedList<N>::insertAtFront(const N& newData) 
{
    Node<N>* newNode = new Node<N>(newData);
    newNode->setNext(head); 
    head = newNode;
}

template <typename N>
void LinkedList<N>::displayAllCommands() const 
{
    Node<N>* current = head;
    while (current != nullptr) 
    {
        current->getData().display();
        current = current->getNext();
    }
}

template <typename N>
bool LinkedList<N>::isEmpty() const 
{
    return head == nullptr;
}

template <typename N>
int LinkedList<N>::size() const
{
    int count = 0;
    Node<N>* current = head;
    while (current != nullptr) 
    {
        current = current->getNext();
        count++;
    }
    return count;
}

template <typename N>
bool LinkedList<N>::searchCommand(const string& cmd) const 
{
        Node<N>* current = head;

        while (current != nullptr) 
        {
            if (current->getData().getCommand() == cmd) 
            {
                return true;
            }
            current = current->getNext();
        }
        return false;
    }

template <typename N>
N LinkedList<N>::getRandomCommand(const LinkedList<N>& commandsList)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int randomIndex = rand() % commandsList.size();

    return commandsList.getElementAtIndex(randomIndex);
}

template <typename N>
N LinkedList<N>::getElementAtIndex(int index) const
{
    Node<N>* current = head;
    int currentIndex = 0;

    while (current != nullptr && currentIndex < index) 
    {
        current = current->getNext(); 
        currentIndex++;
    }

    // checks if index is out of bounds
    if (current == nullptr) 
    {
        throw out_of_range("Index out of bounds");
    }

    return current->getData();
}

// removeNode function
template <typename N>
void LinkedList<N>::remove(const string& commandToRemove)
{
    if (head == nullptr)
    {
        cout << "List is empty. No commands to remove." << endl;
        return;
    }

    Node<N>* current = head;
    Node<N>* previous = nullptr;

    // goes through list to find the node with the specified command
    while (current != nullptr && current->getData().getCommand() != commandToRemove)
    {
        previous = current;
        current = current->getNext();
    }

    if (current == nullptr)
    {
        cout << "Command '" << commandToRemove << "' not found in the list." << endl;
    }
    else
    {
        if (previous == nullptr)
        {
            head = current->getNext();
        }
        else
        {
            previous->setNext(current->getNext());
        }

        delete current;
        cout << "Command '" << commandToRemove << "' has been removed." << endl;
    }
}