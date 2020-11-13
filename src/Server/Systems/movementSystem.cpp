/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** movementSystem.cpp
*/

#include "movementSystem.hpp"
#include "ECSEngine.hpp"
#include <iostream>

ECS::movementSystem::movementSystem() : ECS::ASystem()
{
}

void ECS::movementSystem::update(const float dt, ECS::ECSEngine& engine)
{
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);

    for (auto& ent: entities) {
        if (engine.getStorage(ECS::PLAYER)->hasComponent(ent) == true)
            applyPhysic(engine.getComponent<ECS::Position>(ent, ECS::POSITION), engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY), dt, engine.getComponent<ECS::Player>(ent, ECS::PLAYER));
        else
            applyPhysic(engine.getComponent<ECS::Position>(ent, ECS::POSITION), engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY), dt);
    }
}

void ECS::movementSystem::applyPhysic(ECS::Position& pos, const ECS::Velocity& vel, const float dt)
{
    pos._x += static_cast<int>(vel._vx * dt);
    pos._y += static_cast<int>(vel._vy * dt);
}

void ECS::movementSystem::applyPhysic(ECS::Position& pos, const ECS::Velocity& vel, const float dt, ECS::Player& player)
{
    switch (player._direction) {
        case ECS::UP:
            pos._y -= static_cast<int>(vel._vy * dt);
            break;
        case ECS::DOWN:
            pos._y += static_cast<int>(vel._vy * dt);
            break;
        case ECS::RIGHT:
            pos._x += static_cast<int>(vel._vx * dt);
            break;
        case ECS::LEFT:
            pos._x -= static_cast<int>(vel._vx * dt);
            break;
        case ECS::NONE:
            break;
    }
    std::cout << "posy: " << pos._y << ", posx: " << pos._x << std::endl;
    player._direction = ECS::NONE;
}