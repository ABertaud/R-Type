/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** sample.cpp
*/

#include "sample.hpp"
#include <iostream>
#include <memory>
#include "entityDetails.hpp"
#include "Position.hpp"
#include "Dimensions.hpp"
#include "Velocity.hpp"

sample::sample() : AMonster()
{

}

void sample::init(ECS::ECSEngine& engine)
{
    // (void)engine;
    // auto ent = engine.getNewEntity();

    // engine.addComponent(ent, ECS::Position(100, 100), ECS::POSITION);
    // engine.addComponent(ent, ECS::Velocity(0, 5), ECS::POSITION);
    // engine.addComponent(ent, ECS::Dimensions(200, 200), ECS::DIMENSIONS);
    // engine.addComponent(ent, ECS::entityDetails(entityType::ALIEN, animationState::BASIC), ECS::ENTITY_DETAILS);
    std::cout << "INIT WELL" << std::endl;
}

void sample::update(const float dt, ECS::ECSEngine& engine)
{
    // std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    // entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);

    // for (auto& ent: entities) {
    //     auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
    //     if (details._type == entityType::ALIEN) {
    //         auto&pos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
    //         auto&vel = engine.getComponent<ECS::Velocity>(ent, ECS::VELOCITY);
    //         //updatePattern dt;
    //         //Shoot
    //     }
    // }
    std::cout << "I'M A SAMPLE" << std::endl;
}

extern "C" std::unique_ptr<IMonster> entryPoint()
{
    return (std::make_unique<sample>());
}