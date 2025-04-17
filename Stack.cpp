#include "Stack.h"

#include "StackNode.h"

template <typename T>
Stack<T>::Stack()
{
    //rien de nécessaire ici
}

template <typename T>
Stack<T>::~Stack()
{
    delete this->_root;
}

template <typename T>
void Stack<T>::pop()
{
    if (this->_root == nullptr)
        return;
    else{
        StackNode* old = this->_root;
        this->_root = this->_root->next;
        delete old;
    }
}

template <typename T>
bool Stack<T>::empty()
{
    return false;
}
