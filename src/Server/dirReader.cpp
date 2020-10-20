/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** dirReader.cpp
*/

#include "dirReader.hpp"
#include <dirent.h>
#include <iostream>

dirReader::dirReader(const std::string &name) : _path(name)
{
}

void dirReader::pushLibPath(const std::string &name, std::vector<std::string> &dirPaths)
{
    if (name.find(".so") <= name.length())
        dirPaths.push_back(name);
}

std::vector<std::string> dirReader::findLibraries()
{
    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> dirPaths;

    if ((dir = opendir(_path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL)
            pushLibPath(ent->d_name, dirPaths);
        closedir(dir);
    }
    else {
        throw ErrorDirPath();
    }
    if (dirPaths.empty() == true)
        throw ErrorNoMonsters();
    return (dirPaths);
}