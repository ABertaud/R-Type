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
    (void)dt;
    (void)engine;
    // static unsigned int creationTimer = 0;

    // creationTimer += static_cast<int>(dt);
    // if ((creationTimer % 3) == 0) {
    //     _monsters.push_back(selectRandomMonster()->getInstance<IMonster>("entryPoint"));
    //     _monsters.back()->init(engine);
    // }
    // for (auto& monster : _monsters) {
    //     monster->update(dt, engine);
    // }
}