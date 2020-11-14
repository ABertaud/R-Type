/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** pirate.cpp
*/

#include "pirate.hpp"
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "entityDetails.hpp"
#include "Position.hpp"
#include "Dimensions.hpp"
#include "Velocity.hpp"
#include <map>
#include <vector>

pirate::pirate() : AMonster()
{

}

void pirate::init(ECS::ECSEngine& engine)
{
    auto ent = engine.getNewEntity();

    engine.addComponent(ent, ECS::Position(600, 0), ECS::POSITION);
    engine.addComponent(ent, ECS::Velocity(0, 5), ECS::VELOCITY);
    engine.addComponent(ent, ECS::Dimensions(200, 200), ECS::DIMENSIONS);
    engine.addComponent(ent, ECS::entityDetails(entityType::ALIEN, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
    std::cout << "He's a Pirate\n";
}

void pirate::update(const float dt, ECS::ECSEngine& engine)
{
    static int time = 0;
    std::vector<ECS::Position> pPos;
    std::map<unsigned int, ECS::Position> distance;
    unsigned int value = 0;
    unsigned int closest = -1;
    ECS::Position boss(0, 0);

    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);


    for (auto& ent: entities) {//ON CHERCHE LES PLAYERS
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (details._type == entityType::P1 || details._type == entityType::P2 || details._type == entityType::P3 || details._type == entityType::P4)
            pPos.push_back(engine.getComponent<ECS::Position>(ent, ECS::POSITION));
    }

    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (details._type == entityType::ALIEN) {
            auto&pos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
            auto&vel = engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY);

            if (time % (100 / (static_cast<int>(vel._vy))) == 0) {// plus la velocité monte, plus ca ira souvent dans le if
                
                //calculer et save la distance de chaque player par rapport au pirate
                for (const auto& it: pPos) {
                    value = (it._x - pos._x) * (it._x - pos._x) + (it._y - pos._y) * (it._y - pos._y);
                    distance.insert(std::make_pair(value, it));
                }
                //calculer et save la distance de chaque player par rapport au pirate


                //rechercher le player le plus proche
                for (auto& it: distance) {
                    if (it.first < closest) {
                        closest = it.first;
                        boss = it.second;
                    }
                }
                //rechercher le player le plus proche

                //mouvement
                if (boss._x < pos._x)
                    pos._x -=1;
                else if (boss._x > pos._x)
                    pos._x += 1;
                if (boss._y < pos._y)
                    pos._y -=1;
                else if (boss._y > pos._y)
                    pos._y += 1;
                //mouvement

                closest = -1;//reset pour le prochain pirate
                distance.clear();//reset pour le prochain pirate
            }
        }
    }
    time++;
}

extern "C" std::unique_ptr<IMonster> entryPoint()
{
    return (std::make_unique<pirate>());
}