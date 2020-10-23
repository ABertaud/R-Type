/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** movementSystem.cpp
*/

#include "movementSystem.hpp"
#include "ECSEngine.hpp"

movementSystem::movementSystem()
{
}

void movementSystem::update(const float dt, ECSEngine &engine)
{
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(componentType::VELOCITY), entities);

    for (auto &ent: entities)
        applyPhysic(engine.getComponent<Position>(ent, POSITION), engine.getComponent<Velocity>(ent, VELOCITY), dt);
}

void movementSystem::applyPhysic(Position &pos, Velocity &vel, const float dt)
{
    pos._x += vel._vx * dt;
    pos._y += vel._vy * dt;
}