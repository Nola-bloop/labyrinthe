#include "Labyrinth.h"

#include "LabyrinthNode.h"
#include "Stack.h"
#include "TraitementTexte.h"
#include "FileManager.h"
#include "Explorer.h"

#include <map>
#include <string>
#include <iostream>

//implémentation de l'interface
void Labyrinth::afficherLiens()
{
    std::cout<<"Liens:\n";
    std::cout<<this->toString()<<"\n";
}

void Labyrinth::afficherSolution()
{
    std::vector<int> sol = Explorer::findPath(*this);
    std::string out;

    for (size_t i{0}; i < sol.size(); i++){
        out += std::to_string(sol[i]);
        if (i != sol.size()-1){
            out += " - ";
        }
    }

    std::cout << out;
}

void Labyrinth::lireLabyrinthe(std::string path){
    *this = Labyrinth::loadFromPath(path);
}

void Labyrinth::ecrireSolution(std::string path){
    this->save(path);
}





void Labyrinth::insertEmptyNodes(const std::map<int, std::string>& data)
{
    std::map<int, std::string>::const_iterator it{data.begin()};
    for (it = data.begin(); it != data.end(); it++){
        LabyrinthNode* newNode {new LabyrinthNode};
        newNode->idx = it->first;
        this->nodes.insert(this->nodes.end(), newNode);
    }
}

void Labyrinth::addLinkToNode(int add, int to)
{
    if (to < 0 || to >= this->nodes.size())
        return;


    int fromIndex = this->idxToIndex(add); // will throw if invalid

    LabyrinthNode* target{this->nodes[this->idxToIndex(add)]};
    this->nodes[to]->links.insert(this->nodes[to]->links.begin(), target);
}

void Labyrinth::fillNodes(const std::map<int, std::string>& data)
{

    for (size_t i = 0; i < this->nodes.size(); ++i) {
        int currentIdx = this->nodes[i]->idx;

        auto it = data.find(currentIdx);
        if (it == data.end()) {
            continue;
        }
        Stack<int> s = TraitementTexte::stos(it->second);

        while (!s.empty()) {
            int linkIdx = s.read();
            this->addLinkToNode(linkIdx, i);
            s.pop();
        }
    }
}

int Labyrinth::idxToIndex(int idx)
{
    int out{0};
    for (size_t i{0}; i < this->nodes.size(); i++){
        if (this->nodes.at(i)->idx == idx)
            out = i;
    }
    return out;
}

Labyrinth::Labyrinth(const std::map<int, std::string>& data, int start, int end)
{
    //créer les nodes vides
    this->insertEmptyNodes(data);

    //remplir les nodes vides
    this->fillNodes(data);

    //start et end sont les numéros des cases et non des indexes. Je dois donc les convertirs en indexes et ensuite retrouver son pointeur.
    this->start = this->nodes[this->idxToIndex(start)];
    this->end = this->nodes[this->idxToIndex(end)];
}

Labyrinth Labyrinth::loadFromPath(std::string filePath)
{
    return FileManager::parse(filePath);
}

Labyrinth::~Labyrinth()
{
    //Je crois que le destructeur des vecteurs se charge déjà de faire un delete de tous mes pointeurs
    //ce qui fait un Segmentation Fault si je laisse ce code décommenté à cause des nodes[?].links, qui est un vecteur avec les mêmes pointeurs

    /*
    for (size_t i{0}; i < this->nodes.size(); i++){
        delete this->nodes[i];
    }
    */
}

void Labyrinth::save(std::string path)
{
    FileManager::save(path, this);
}

LabyrinthNode *Labyrinth::getStart()
{
    return this->start;
}

LabyrinthNode* Labyrinth::getEnd()
{
    return this->end;
}

std::vector<LabyrinthNode *>& Labyrinth::getNodes()
{
    return this->nodes;
}

std::string Labyrinth::toString()
{
    std::string out {""};
    for (size_t i{0}; i < this->nodes.size(); i++){
        out += std::to_string(this->nodes[i]->idx) + " (";
        for (size_t j{0}; j < this->nodes[i]->links.size(); j++){
            out += std::to_string(this->nodes[i]->links[j]->idx);
            
            if (j != this->nodes[i]->links.size() - 1)
                out += ", ";
        }
        out += ")\n";
    }
    return out;
}
