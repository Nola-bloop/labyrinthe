#include "Stack.h"

#include "StackNode.h"

Stack::Stack()
{
    //rien de nécessaire ici
}

Stack::~Stack()
{
    delete this->_root;
}

void Stack::push(int v)
{
    StackNode* newNode = new StackNode{v, this->_root};
    if (this->_root == nullptr)
        this->_root = newNode;
    else
        this->_root = newNode;
}

int Stack::read()
{
    return this->_root->v;
}

void Stack::pop()
{
    if (this->_root == nullptr)
        return;
    else{
        StackNode* old = this->_root;
        this->_root = this->_root->next;
        delete old;
    }
}
