/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** eventSystem.cpp
*/

#include "eventSystem.hpp"
#include "ECSEngine.hpp"
#include "Position.hpp"
#include "Dimensions.hpp"
#include "Velocity.hpp"
#include "entityDetails.hpp"
#include <iostream>

ECS::eventSystem::eventSystem(const std::shared_ptr<Buffer>& buffer) : ECS::ASystem(), _buffer(buffer)
{
    _moves.insert(std::make_pair("Up", ECS::currentMovement::UP));
    _moves.insert(std::make_pair("Down", ECS::currentMovement::DOWN));
    _moves.insert(std::make_pair("Left", ECS::currentMovement::LEFT));
    _moves.insert(std::make_pair("Right", ECS::currentMovement::RIGHT));
}

void ECS::eventSystem::update(const float dt, ECS::ECSEngine& engine)
{
    (void)dt;
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::PLAYER), engine.getEntites());

    for (auto& ent : entities) {
        ECS::Player& player = engine.getComponent<ECS::Player>(ent, ECS::PLAYER);
        if (_buffer->isDataAvailable(player._uuid) == true)
            handleEvent(_buffer->getData(player._uuid), engine, ent, player);
    }
}

void ECS::eventSystem::handleEvent(std::vector<std::string>& events, ECS::ECSEngine& engine, const Entity entity, ECS::Player& player)
{
    std::string event(events.front());

    if (std::strcmp(event.c_str(), "Off") == 0) {
        engine.removeEntity(entity);
    } else if (std::strcmp(event.c_str(), "Shoot") == 0)
        createShoot(engine, entity);
    else {
        for (auto it = _moves.begin(); it != _moves.end(); ++it)
            if (std::strcmp(event.c_str(), it->first.c_str()))
                player._direction = it->second;
    }
    events.erase(events.begin());
}

void ECS::eventSystem::createShoot(ECS::ECSEngine& engine, const Entity entity)
{
    ECS::Position& pos = engine.getComponent<ECS::Position>(entity, ECS::POSITION);
    
    Entity ent = engine.getNewEntity();
    engine.addComponent(ent, pos, ECS::POSITION);
    engine.addComponent(ent, ECS::Dimensions(100, 100), ECS::DIMENSIONS);
    engine.addComponent(ent, ECS::Velocity(30, 0), ECS::VELOCITY);
    engine.addComponent(ent, ECS::entityDetails(PLAYER_SHOOT, entityState::BASIC), ECS::ENTITY_DETAILS);
}