#pragma once

template <typename T>
struct StackNode
{
    T v{0};
    StackNode* next{nullptr};

    ~StackNode();
};

template <typename T>
StackNode<T>::~StackNode()
{
    if (this->next != nullptr)
        delete this->next;
}