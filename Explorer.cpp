#include "Explorer.h"

#include "Stack.h"
#include "Labyrinth.h"
#include "LabyrinthNode.h"

#include <map>

std::vector<int> Explorer::findPath(Labyrinth& l)
{
    //variables et raccourcis
    Stack<LabyrinthNode*> path; //la variable qui retient le chemin
    std::map<LabyrinthNode*, bool> history; //la variable qui retient tous les nodes visités
    Stack<LabyrinthNode*> toExplore; // nodes à visiter
    LabyrinthNode* end = l.getEnd();

    toExplore.push(l.getStart());

    bool run = true;
    while(run){
        if (toExplore.empty()) break;
        LabyrinthNode* node = toExplore.read();
        toExplore.pop();
        path.push(node);
        history[node] = true;

        //si c'est la fin
        if (node == end)
            run = false;
        else //sinon
        {
            //ajouter les liens commes possibilités de chemin
            for (size_t i{0}; i < node->links.size(); i++){
                if (!history[node->links[i]])
                    toExplore.push(node->links[i]);
            }

            //si aucun node n'a été ajouté
            bool pushedNew = false;
            for (size_t i{0}; i< node->links.size(); i++) {
                if (!history[node->links[i]]) {
                    toExplore.push(node->links[i]);
                    pushedNew = true;
                }
            }
            if (!pushedNew) {
                path.pop();
            }
        }
    }

    //convertir le path en vecteur
    std::vector<LabyrinthNode*> v{path.burn()};
    
    //convertir le nouveau vecteur de pointeurs en vecteur de numéros de cases
    std::vector<int> indexes;
    for (size_t i{0}; i < v.size(); i++){
        indexes.push_back(v[i]->idx);
    }

    return indexes;
}
