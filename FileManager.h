#pragma once

#include "FileBinStructures.h"
#include "Labyrinth.h"

#include <string>
#include <map>
#include <vector>

namespace FileManager{
    /// @brief get the sorted binary of a file
    /// @param path : path to read
    /// @return the sorted binary of the file
    File readFile(std::string path);

    /// @brief convert an array of steps into a usable map for the Labyrinth constructor
    /// @param steps : vector full of Steps
    /// @return a map that can be used by the Labyrinth constructor
    std::map<int, std::string> getMap(std::vector<Step> steps);



    /// @brief parse sorted binary into a usable labyrinth
    /// @param file the sorted binary to parse
    /// @return the parsed labyrinth
    Labyrinth parse(File file);

    /// @brief (redifinition) read and parse a file into a labyrinth
    /// @param path path to read
    /// @return fully parsed labyrinth
    Labyrinth parse(std::string path);

    /// @brief parse a Labyrinth into a file object that can then be saved
    /// @param l : labyrinth to parse
    /// @return file object of the labyrinth
    File parse(Labyrinth l);



    /// @brief get a map containing unique links that can be put inside a file.
    /// @param l labyrinth to use
    /// @return a map with the unique links
    std::map<uint16_t, std::vector<uint16_t>> getUniqueLinks(Labyrinth l);

    /// @brief save a File to the path
    /// @param path path to save to
    /// @param f file to save
    void save(std::string path, File f);

    /// @brief Save labyrinth with solution to the path
    /// @param path path where to save
    /// @param l labyrinth to save
    void save(std::string path, Labyrinth l);

    /// @brief Save labyrinth with solution to the path
    /// @param path path where to save
    /// @param l labyrinth to save
    void save(std::string path, Labyrinth* l);
}