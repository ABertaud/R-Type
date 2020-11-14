/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** monsterSystem.cpp
*/

#include "monsterSystem.hpp"
#include "dirReader.hpp"
#include <memory>

ECS::monsterSystem::monsterSystem(const std::string& libPath)
{
    dirReader dir(libPath);
    std::vector<std::string> pathToDLL = dir.findLibraries();

    for (auto& path : pathToDLL) {
        _loaders.push_back(std::unique_ptr<DLLoader>{new DLLoader(path)});
    }
}

std::unique_ptr<DLLoader>& ECS::monsterSystem::selectRandomMonster()
{
    int toLoad = rand() % _loaders.size();

    return (_loaders.at(toLoad));
}

void ECS::monsterSystem::update(const float dt, ECS::ECSEngine& engine)
{
    static unsigned int creationTimer = 0;
    static unsigned int lap = 0;
    static unsigned int level = 1;

    creationTimer++;
    if ((creationTimer % (100 / level)) == 0) {
        _monsters.push_back(selectRandomMonster()->getInstance<IMonster>("entryPoint"));
        _monsters.back()->init(engine);
    }
    // for (auto& monster : _monsters) {
    //     monster->update(dt, engine);
    // }
    // if (creationTimer >= 100 / level) {
    //     creationTimer = 0;
    //     lap++;
    // }
    // if (lap == 4) {
    //     level = 2;
    // }
    // if (lap == 16) {
    //     level = 8;
    // }
    // if (lap == 64) {
    //     level = 32;
    // }
}