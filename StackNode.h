#pragma once

struct StackNode
{
    int v{0};
    StackNode* next{nullptr};

    ~StackNode();
};
