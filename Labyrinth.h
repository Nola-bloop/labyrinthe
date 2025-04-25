#pragma once

#include <vector>
#include <map>
#include <string>

#include "LabyrinthNode.h"

class Labyrinth
{
private:
    LabyrinthNode* start{nullptr};
    LabyrinthNode* end{nullptr};
    std::vector<LabyrinthNode*> nodes;

    /// @brief remplir le labyrinthe de nodes vides
    /// @param map la map au format brut exemple: [0] = "2,6,7,3"
    void insertEmptyNodes(const std::map<int, std::string>& map);

    /// @brief ajouter un lien à un node
    /// @param add : Node->idx of the node to add
    /// @param to : Labyrinth::nodes[?] of the node to add
    void addLinkToNode(int add, int to);

    /// @brief remplir les nodes vides de liens
    /// @param data la map à utiliser
    void fillNodes(const std::map<int, std::string>& data);
public:
    /// @brief Créer un labyrinthe avec des valeurs spécifiques
    /// @param map le mapping de donnés à utiliser
    /// @param start la case de départ
    /// @param end la case finale
    Labyrinth(const std::map<int, std::string>& map, int start, int end);

    /// @brief destructeur du labyrinthe (il sert pas à grand chose...)
    ~Labyrinth();

    /// @brief Créer une Labyrinthe avec le FileManager en utilisant un filepath
    /// @param filePath l'emplacement du fichier du labyrinthe
    static Labyrinth loadFromPath(std::string filePath);
    
    /// @brief save the labyrinth with the solution in a designated path
    /// @param path where to save the labyrinth
    void save(std::string path);

    LabyrinthNode* getStart();
    LabyrinthNode* getEnd();
    std::vector<LabyrinthNode*>& getNodes();

    /// @brief Convertis un numéro de case en indexe
    /// @param idx le numéro de la case
    /// @return l'indexe de la case
    int idxToIndex(int idx);

    std::string toString();
};
