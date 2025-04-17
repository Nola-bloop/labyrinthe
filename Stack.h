#pragma once

#include "StackNode.h"

template <typename T>
struct Stack
{
private:
	StackNode* _root;
public:
	Stack();
	~Stack();

	/// @brief insérer une donnée
	/// @param v La donnée à insérer
	void push(T v);

	/// @brief lire la donnée
	/// @return 
	T read();

	/// @brief enlever la donnée sur le top
	void pop();

    /// @brief regarder si la pile est vide
    /// @return vrai si elle est vide, faux sinon
    bool empty();
};

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
void Stack<T>::push(T v)
{
    StackNode* newNode = new StackNode{v, this->_root};
    if (this->_root == nullptr)
        this->_root = newNode;
    else
        this->_root = newNode;
}

template <typename T>
T Stack<T>::read()
{
    return this->_root->v;
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
    return this->_root == nullptr;
}