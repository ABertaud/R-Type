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

    _id = ent;
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
        if (details._type == entityType::UFO && ent == _id) {
            auto& pos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
            auto& vel = engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY);

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
                    if (zone <= - 50)           //il est en haut il change de sens
                        way = false;
                    else {                      //il monte
                        vel._vy = -1;
                        zone--;
                    }
                }
            }
            if (_animation == 0) {
                details._state = static_cast<animationState>(static_cast<int>(details._state) + 1);
                if (details._state == ANIMATION_9)
                    details._state = ANIMATION_0;
                _animation = 1;
            }
        }
    }
    if (_animation > 0)
        _animation++;
    if (_animation == 5)
        _animation = 0;
    time++;
}

#if defined (_WIN32)

extern "C"  __declspec(dllexport)
void* entryPoint()
{
    return (new std::unique_ptr<ufo>(new ufo));
}

#else

extern "C" std::unique_ptr<IMonster> entryPoint()
{
    return (std::make_unique<ufo>());
}

#endif