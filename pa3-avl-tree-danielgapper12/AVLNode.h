#ifndef AVLNODE_H
using namespace std;

template <typename T>
class AVLNode
{
public:
    // necessary constructors
    AVLNode();
    explicit AVLNode(const T &newData);

    // destructor
    ~AVLNode();

    // setters
    void setData(T newData);
    void setLeft(AVLNode<T>* node);
    void setRight(AVLNode<T>* node);
    void setHeight(int newHeight);

    // getters
    T getData() const;
    AVLNode<T>* getLeft() const;
    AVLNode<T>* getRight() const;
    int getHeight() const;

private:

    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;

};

// necessary constructors
template<typename T>
AVLNode<T>::AVLNode()
{
    data = T();
    left = nullptr;
    right = nullptr;
    height = 0;

}


template<typename T>
AVLNode<T>::AVLNode(const T &newData)
{
    data = newData;
    left = nullptr;
    right = nullptr;
    height = 1;
}

// destructor
template<typename T>
AVLNode<T>::~AVLNode()
{

}

// setters
template<typename T>
void AVLNode<T>::setData(T newData)
{
    data = newData;
}
template<typename T>
void AVLNode<T>::setLeft(AVLNode<T>* node)
{
    left = node;
}
template<typename T>
void AVLNode<T>::setRight(AVLNode<T>* node)
{
    right = node;
}
template<typename T>
void AVLNode<T>::setHeight(int newHeight)
{
    height = newHeight;
}


// getters
template<typename T>
T AVLNode<T>::getData() const
{
    return data;
}
template<typename T>
AVLNode<T>* AVLNode<T>::getLeft() const
{
    return left;
}
template<typename T>
AVLNode<T>* AVLNode<T>::getRight() const
{
    return right;
}
template<typename T>
int AVLNode<T>::getHeight() const
{
    return height;
}

#endif