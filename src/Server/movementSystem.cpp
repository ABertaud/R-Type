/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** movementSystem.cpp
*/

#include "movementSystem.hpp"
#include "ECSEngine.hpp"

ECS::movementSystem::movementSystem()
{
}

void ECS::movementSystem::update(const float dt, ECS::ECSEngine& engine)
{
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);

    for (auto& ent: entities)
        applyPhysic(engine.getComponent<Position>(ent, ECS::POSITION), engine.getComponent<Velocity>(ent, ECS::VELOCITY), dt);
}

void ECS::movementSystem::applyPhysic(ECS::Position& pos, ECS::Velocity& vel, const float dt)
{
    pos._x += vel._vx * dt;
    pos._y += vel._vy * dt;
}