#pragma once

#include "StackNode.h"

#include <vector>

template <typename T>
struct Stack
{
private:
	StackNode<T>* _root{nullptr};
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

    /// @brief bruler le stack et le convertir en vecteur
    /// @param invert : inverser le stack ou non en le brulant
    /// @return le vecteur avec les valeurs du stack
    std::vector<T> burn(bool invert = false);
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
    StackNode<T>* newNode = new StackNode<T>{v, this->_root};
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
        StackNode<T>* old = this->_root;
        this->_root = this->_root->next;
        old->next = nullptr;
        delete old;
    }
}

template <typename T>
bool Stack<T>::empty()
{
    return this->_root == nullptr;
}

template <typename T>
std::vector<T> Stack<T>::burn(bool invert){
    std::vector<T> out;

    while (!this->empty()){
        T toAdd = this->read();
        this->pop();
        if (!invert)
            out.insert(out.begin(), toAdd);
        else
            out.push_back(toAdd);
    }
    return out;
}