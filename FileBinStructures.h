#pragma once

#include <cstdint>
#include <vector>
#include <string>

#pragma pack(push, 1)
struct Headers
{
    uint16_t file_type{ 0x6969 }; // Type du fichier
    uint32_t file_size{ 0 }; //en octets
    uint32_t offset{ 0 }; //en octets
    uint32_t taille_labyrinthe{0}; //en octets
    uint16_t nb_cases{0}; //nombre de cases dans le labyrinthe
    uint16_t case_debut{0}; //numéro de la case du début
    uint16_t case_fin{0}; //numéro de la case finale
};

struct Step
{
    uint16_t case_a{0};
    uint16_t case_b{0};
};

struct SolutionHeaders
{
    uint32_t taille_sol{0}; //taille de la solution
    uint32_t offset{0}; //offset par rapport au début du fichier
};

struct SolutionStep
{
    uint16_t step{0};
};

struct File
{
    Headers headers;
    std::vector<Step> steps{};
    SolutionHeaders solutionHeaders;
    std::vector<SolutionStep> solutionSteps{};
};

#pragma pack(pop)