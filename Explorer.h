#pragma once

#include <vector>

#include "Labyrinth.h"

class Explorer
{
private:

public:
    static std::vector<int> findPath(Labyrinth& l);
};
