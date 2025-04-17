#pragma once

#include "StackNode.h"

struct Stack
{
private:
	StackNode* _root;
public:
	Stack();
	~Stack();
	void push(int v);
	int read();
	void pop();
};
