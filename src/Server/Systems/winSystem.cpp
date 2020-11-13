/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** winSystem.cpp
*/

#include "winSystem.hpp"
#include "ECSEngine.hpp"
#include "entityDetails.hpp"
#include <iostream>

ECS::winSystem::winSystem(const std::shared_ptr<bool>& end) : ECS::ASystem(), _end(end)
{
}

void ECS::winSystem::update(const float dt, ECS::ECSEngine& engine)
{
    (void)dt;
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::PLAYER), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::LIFE), entities);

    for (auto& ent : entities) {
        if (engine.getComponent<ECS::Life>(ent, ECS::LIFE)._hp == 0) {
            // engine.removeEntity(ent);
            engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS)._toUpdate = false;
        }
    }
    if (entities.size() <= 0) {
        *_end = true;
        return;
    }
}