#pragma once

#include <vector>

struct LabyrinthNode
{
    int idx{0};
    std::vector<LabyrinthNode*> links;

    /// @brief checks if a certain tile is within the links
    /// @param idx tile to find amongst the links
    /// @return true if found, false if not.
    bool linksContains(int idx){
        for (size_t i{0}; i < this->links.size(); i++){
            if (this->links[i]->idx == idx)
                return true;
        }
        return false;
    }
};
