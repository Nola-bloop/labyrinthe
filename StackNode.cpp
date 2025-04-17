#include "StackNode.h"

StackNode::~StackNode()
{
    delete this->next;
}
