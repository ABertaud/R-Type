/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** ufo.cpp
*/

#include "ufo.hpp"
#include <iostream>
#include <memory>
#include "entityDetails.hpp"
#include "Position.hpp"
#include "Dimensions.hpp"
#include "Velocity.hpp"

ufo::ufo() : AMonster()
{

}

void ufo::init(ECS::ECSEngine& engine)
{
    auto ent = engine.getNewEntity();

    engine.addComponent(ent, ECS::Position(1116, rand() % 700 + 100), ECS::POSITION);
    engine.addComponent(ent, ECS::Velocity(0, 20), ECS::VELOCITY);
    engine.addComponent(ent, ECS::Dimensions(33, 37), ECS::DIMENSIONS);
    engine.addComponent(ent, ECS::entityDetails(entityType::UFO, animationState::ANIMATION_0), ECS::ENTITY_DETAILS);
}

void ufo::update(const float dt, ECS::ECSEngine& engine)
{
    static int time = 0;
    static int speed = 5;
    static int zone = 0;
    static bool way = rand() % 2;

    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);

    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (details._type == entityType::UFO) {
            auto& pos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
            auto& vel = engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY);
        std::cout << zone << "\n";

            if (time % (100 / speed) == 0) {    // plus la velocité monte, plus ca ira souvent dans le if
                vel._vx = -3;
                if (way == false) {             //il va descendre
                    if (zone >= 50)             //il est en bas il change de sens
                        way = true;
                    else {                      //il descend
                        vel._vy = 1;
                        zone++;
                    }
                } else {                        //il va monter
                    if (zone <= - 50)          //il est en haut il change de sens
                        way = false;
                    else {                      //il monte
                        vel._vy = -1;
                        zone--;
                    }
                }
            }
        }
    }
    time++;
}

extern "C" std::unique_ptr<IMonster> entryPoint()
{
    return (std::make_unique<ufo>());
}