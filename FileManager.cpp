#include "FileManager.h"

#include "FileBinStructures.h"
#include "Labyrinth.h"
#include "LabyrinthNode.h"
#include "Explorer.h"

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstdint>

File FileManager::readFile(std::string path)
{
    File file;

    std::ifstream stream{ path, std::ios::in | std::ios::binary };
    if (stream.is_open()){

        stream.read((char*)&file.headers, sizeof(file.headers));

        file.steps.resize(file.headers.taille_labyrinthe/sizeof(Step));

        stream.seekg(file.headers.offset, stream.beg);
        stream.read((char*)file.steps.data(), file.steps.size()*sizeof(Step));
    }

    return file;
}

std::map<int, std::string> FileManager::getMap(std::vector<Step> steps)
{
    std::map<int, std::string> map;
    for (size_t i {0}; i < steps.size(); i++){
        //map[i] += std::to_string(steps[i].case_a) + "," + std::to_string(steps[i].case_b);
        map[steps[i].case_a] += std::to_string(steps[i].case_b) + ",";
        map[steps[i].case_b] += std::to_string(steps[i].case_a) + ",";
    }
    return map;
}

Labyrinth FileManager::parse(File file)
{
    return Labyrinth(FileManager::getMap(file.steps), file.headers.case_debut, file.headers.case_fin);
}

Labyrinth FileManager::parse(std::string path)
{
    return FileManager::parse(FileManager::readFile(path));
}

File FileManager::parse(Labyrinth l)
{
    File f;

    //headers
    f.headers.offset        = sizeof(Headers)+sizeof(SolutionHeaders);
    f.headers.case_debut    = l.getStart()->idx;
    f.headers.case_fin      = l.getEnd()->idx;
    
    //steps (aussi appelés links)
    std::map<uint16_t, std::vector<uint16_t>> links {FileManager::getUniqueLinks(l)};
    std::map<uint16_t, std::vector<uint16_t>>::iterator it;
    for (it = links.begin(); it != links.end(); it++){
        for (size_t i{0}; i < it->second.size(); i++){
            f.steps.push_back(Step{it->first, it->second[i]});
        }
    }

    //derniers headers qui ont besoin que les liens soit faits.
    f.headers.nb_cases      = f.steps.size();
    f.headers.taille_labyrinthe = (sizeof(Step) * f.steps.size());
    
    //solution
    std::vector<int> solution = Explorer::findPath(l);
    for (size_t i{0}; i < solution.size(); i++){
        uint16_t idx = solution[i];
        f.solutionSteps.push_back(SolutionStep{idx});
    }

    //sol headers
    f.solutionHeaders.offset = sizeof(Headers);
    f.solutionHeaders.taille_sol = f.solutionSteps.size() * sizeof(SolutionStep);
    
    //taille finale
    f.headers.file_size =   sizeof(Headers)
                          + sizeof(SolutionHeaders)
                          + f.headers.taille_labyrinthe
                          + f.solutionHeaders.taille_sol;

    return f;
}

std::map<uint16_t, std::vector<uint16_t>> FileManager::getUniqueLinks(Labyrinth l)
{
    std::vector<LabyrinthNode*> nodes{l.getNodes()};
    std::map<uint16_t, std::vector<uint16_t>> links; //this will contain unique links
    for (size_t i{0}; i < nodes.size(); i++){
        for (size_t j{0}; j < nodes[i]->links.size(); j++){
            int smallIdx{0};
            int bigIdx{0};
            if (nodes[i]->idx <= nodes[i]->links[j]->idx){
                smallIdx = nodes[i]->idx;
                bigIdx = nodes[i]->links[j]->idx;
            }else{
                smallIdx = nodes[i]->links[j]->idx;
                bigIdx = nodes[i]->idx;
            }

            bool contains = false;
            for (size_t k{0}; k < links[smallIdx].size(); k++){
                if (links[smallIdx][k] == bigIdx)
                    contains = true;
            }
            if (!contains)
                links[smallIdx].push_back(bigIdx);
        }
    }
    return links;
}

void FileManager::save(std::string path, File f)
{
    std::ofstream stream{ path, std::ios_base::binary };
    if (stream)
    {
        stream.write((char*)&f.headers, sizeof(f.headers));
        stream.write((char*)&f.solutionHeaders, sizeof(f.solutionHeaders));
        stream.write((char*)f.steps.data(), f.steps.size()*sizeof(Step));
        stream.write((char*)f.solutionSteps.data(), f.solutionSteps.size()*sizeof(SolutionStep));
    }
}

void FileManager::save(std::string path, Labyrinth l)
{
    FileManager::save(path, FileManager::parse(l));
}

void FileManager::save(std::string path, Labyrinth *l)
{
    FileManager::save(path, FileManager::parse(*l));
}
