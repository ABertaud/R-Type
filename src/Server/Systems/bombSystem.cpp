/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** bombSystem.cpp
*/

#include "bombSystem.hpp"
#include "ECSEngine.hpp"
#include "Bomb.hpp"

ECS::bombSystem::bombSystem() : ECS::ASystem()
{
}

void ECS::bombSystem::update(const float dt, ECS::ECSEngine& engine)
{
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());

    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (details._type == entityType::BOMB)
            updateBomb(dt, ent, engine, details);
    }
}

void ECS::bombSystem::updateBomb(const float dt, const Entity ent, ECS::ECSEngine& engine, ECS::entityDetails& details)
{
    auto& bomb = engine.getComponent<ECS::Bomb>(ent, ECS::BOMB);

    bomb._dt += dt;
    if (bomb._dt >= 2)
        details._state = animationState::ANIMATION_1;
    else if (bomb._dt >= 4)
        details._state = animationState::ANIMATION_2;
    else if (bomb._dt >= 6) {
        // engine.removeEntity(ent);
        details._toUpdate = false;
    }
}