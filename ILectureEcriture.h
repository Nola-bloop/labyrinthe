#pragma once

#include <string>

class ILectureEcriture
{
public:
    virtual void lireLabyrinthe(const std::string path)=0;
    virtual void ecrireSolution(const std::string path)=0;
};