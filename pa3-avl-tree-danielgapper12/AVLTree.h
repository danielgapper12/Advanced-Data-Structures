#ifndef AVLTREE_H

#include <iostream>
#include "AVLNode.h"

using namespace std;

template<typename T> 
class AVLTree
{
public:
    // necessary constructors
    AVLTree();

    // destructor
    ~AVLTree();

    // determines if the tree is empty 
    int isEmpty(); 

    // returns the height of the node or -1 if a nullptr
    int height();

    // inserts data into the tree following AVL balancing properties
    void insert(const T &value);
    
    // removes a specific item from the tree, then balances
    void remove(const T &value);
    
    // removes all nodes from the tree
    void clear();
    
    // returns the smallest item in the tree
    T findMin();
    
    // returns the largest item in the tree
    T findMax();
    
    // prints the data in the nodes in increasing order
    void printInOrder() const; 
    
    AVLNode<T>* getRoot()
    {
        return root;
    }

    AVLNode<T>* balance(AVLNode<T>* node);

private:
    AVLNode<T>* root;

    // insert
    AVLNode<T>* insert(AVLNode<T>* node, const T& value);

    // remove
    AVLNode<T>* remove(AVLNode<T>* node, const T& value);

    // clear
    void clear(AVLNode<T>* node);

    // height 
    int height(AVLNode<T>* node) const;

    // update height
    void updateHeight(AVLNode<T>* node);

    // get balance
    int getBalance(AVLNode<T>* node) const;

    // rotate left
    AVLNode<T>* rotateLeft(AVLNode<T>* x);

    // rotate right
    AVLNode<T>* rotateRight(AVLNode<T>* y);

    // find minimum node
    AVLNode<T>* findMinNode(AVLNode<T>* node) const;

    // find maximum node
    AVLNode<T>* findMaxNode(AVLNode<T>* node) const;

    // print in order
    void printInOrder(AVLNode<T>* node) const;
};



// necessary constructors
template<typename T>
AVLTree<T>::AVLTree() 
{
    root = nullptr; 
}

// destructor
template<typename T>
AVLTree<T>::~AVLTree()
{
    clear(root);
}

// determines if the tree is empty 
template<typename T>
int AVLTree<T>::isEmpty()
{
    return root == nullptr;
}

// returns the height of the node or -1 if a nullptr 
template<typename T>
int AVLTree<T>::height() 
{
    if (root == nullptr) 
    {
        return -1; 
    } else {
        return 1 + max(height(root->getLeft()), height(root->getRight()));
    }
}

// inserts data into the tree following AVL balancing properties
template<typename T>
void AVLTree<T>::insert(const T &value)
{
    root = insert(root, value);
}

// removes a specific item from the tree then balances tree
template<typename T>
void AVLTree<T>::remove(const T &value)
{
    root = remove(root, value);
}

// removes all nodes from the tree
template<typename T>
void AVLTree<T>::clear()
{
    clear(root);
    root = nullptr;
}

// returns the smallest item in the tree
template<typename T>
T AVLTree<T>::findMin()
{
    if (isEmpty())
    {
        throw runtime_error("Tree is empty!");
    }
    return findMinNode(root)->getData();
}

// returns the largest item in the tree
template<typename T>
T AVLTree<T>::findMax()
{
    if (isEmpty())
    {
        throw runtime_error("Tree is empty!");
    }
    return findMaxNode(root)->getData();
}

// prints the data in the nodes in increasing order
template<typename T>
void AVLTree<T>::printInOrder() const
{
    printInOrder(root);
}


// private functions

// insert
template<typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, const T& value)
{
    if (!node)
    {
        return new AVLNode<T>(value);
    } 
    if (value < node->getData()) 
    {
        node->setLeft(insert(node->getLeft(), value));
    } else if (value > node->getData()) 
    {
        node->setRight(insert(node->getRight(), value));
    } else 
    {
        return node; 
    }

    updateHeight(node);

    return balance(node);
}

// remove
template<typename T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* node, const T& value)
{
    if (!node) 
    {
        return node;
    }

    // if the to be deleted node's value < node's value then node in left subtree
    if (value < node->getData()) 
    {
        node->setLeft(remove(node->getLeft(), value));
    }
    // otherwise if > then in right subtree
    else if (value > node->getData()) 
    {
        node->setRight(remove(node->getRight(), value));
    }

    // if = then this is the node to delete!
    else {
        // node with one or no child
        if ((node->getLeft() == nullptr) || (node->getRight() == nullptr)) 
        {
            AVLNode<T>* temp;
            if (node->getLeft() != nullptr) 
            {
                temp = node->getLeft();
            } else {
                temp = node->getRight();
            }

            // no child
            if (temp == nullptr) 
            {
                temp = node;
                node = nullptr;
            }
            else { // one child
                *node = *temp; // copy contents of the non-empty child
                delete temp;
            }
        }
        else {
            // node has two children, get smallest in the right subtree
            AVLNode<T>* temp = findMinNode(node->getRight());

            node->setData(temp->getData());

            node->setRight(remove(node->getRight(), temp->getData()));
        }
    }

    if (node == nullptr) 
    {
        return node;
    }

    // update height
    node->setHeight(1 + max(height(node->getLeft()), height(node->getRight())));

    // get balance to check if node unbalanced now
    int balance = getBalance(node);

    // left left
    if (balance > 1 && getBalance(node->getLeft()) >= 0) 
    {
        return rotateRight(node);
    }

    // left right
    if (balance > 1 && getBalance(node->getLeft()) < 0) 
    {
        node->setLeft(rotateLeft(node->getLeft()));
        return rotateRight(node);
    }

    // right right
    if (balance < -1 && getBalance(node->getRight()) <= 0) 
    {
        return rotateLeft(node);
    }

    // right left
    if (balance < -1 && getBalance(node->getRight()) > 0) 
    {
        node->setRight(rotateRight(node->getRight()));
        return rotateLeft(node);
    }
    return node;
}

// clear
template<typename T>
void AVLTree<T>::clear(AVLNode<T>* node)
{
    if (node) 
    {
        clear(node->getLeft());
        clear(node->getRight());
        delete node;
        node = nullptr;
    }
}

// height 
template<typename T>
int AVLTree<T>::height(AVLNode<T>* node) const
{
    int height;
    if (node != nullptr) 
    {
        height = node->getHeight();
    } else {
        height = 0;
    }
    return height;
}

// update height
template<typename T>
void AVLTree<T>::updateHeight(AVLNode<T>* node) 
{
    node->setHeight(1 + max(height(node->getLeft()), height(node->getRight())));
}

// get balance
template<typename T>
int AVLTree<T>::getBalance(AVLNode<T>* node) const
{
    if (node == nullptr)
     {
        return 0;
    }
    return height(node->getLeft()) - height(node->getRight());
}

// rotate left
template<typename T>
AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T>* x)
{
    AVLNode<T>* y = x->getRight();
    AVLNode<T>* T2 = y->getLeft();

    y->setLeft(x);
    x->setRight(T2);
    x->setHeight(max(height(x->getLeft()), height(x->getRight())) + 1);
    y->setHeight(max(height(y->getLeft()), height(y->getRight())) + 1);

    return y;
}

// rotate right
template<typename T>
AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T>* y)
{
    AVLNode<T>* x = y->getLeft();
    AVLNode<T>* T2 = x->getRight();

    x->setRight(y);
    y->setLeft(T2);
    y->setHeight(max(height(y->getLeft()), height(y->getRight())) + 1);
    x->setHeight(max(height(x->getLeft()), height(x->getRight())) + 1);

    return x;
}

// find minimum node
template<typename T>
AVLNode<T>* AVLTree<T>::findMinNode(AVLNode<T>* node) const
{
    AVLNode<T>* current = node;
    while (current->getLeft() != nullptr) 
    {
        current = current->getLeft();
    }
    return current;
}

// find maximum node
template<typename T>
AVLNode<T>* AVLTree<T>::findMaxNode(AVLNode<T>* node) const
{
    AVLNode<T>* current = node;
    while (current->getRight() != nullptr) 
    {
        current = current->getRight();
    }
    return current;
}

// print in order
template<typename T>
void AVLTree<T>::printInOrder(AVLNode<T>* node) const
{
    if (node != nullptr) 
    {
        printInOrder(node->getLeft());
        cout << node->getData() << " ";
        printInOrder(node->getRight());
    }
}


// balance tree
template<typename T>
AVLNode<T>* AVLTree<T>::balance(AVLNode<T>* node) 
{
    node->setHeight(1 + max(height(node->getLeft()), height(node->getRight())));

    int balanceFactor = getBalance(node);

    // Left Left Case
    if (balanceFactor > 1 && getBalance(node->getLeft()) >= 0) {
        return rotateRight(node);
    }

    // Left Right Case
    if (balanceFactor > 1 && getBalance(node->getLeft()) < 0) {
        node->setLeft(rotateLeft(node->getLeft()));
        return rotateRight(node);
    }

    // Right Right Case
    if (balanceFactor < -1 && getBalance(node->getRight()) <= 0) {
        return rotateLeft(node);
    }

    // Right Left Case
    if (balanceFactor < -1 && getBalance(node->getRight()) > 0) {
        node->setRight(rotateRight(node->getRight()));
        return rotateLeft(node);
    }

    return node;
}



#endif