/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** collisionSystem.cpp
*/

#include "collisionSystem.hpp"
#include "ECSEngine.hpp"
#include <iostream>

ECS::collisionSystem::collisionSystem() : ECS::ASystem()
{
}

void ECS::collisionSystem::update(const float dt, ECS::ECSEngine& engine)
{
    (void)dt;
    (void)engine;
    std::vector<Entity> entities = _filter.filterEntities(engine.getStorage(ECS::componentType::POSITION), engine.getEntites());
    entities = _filter.filterEntities(engine.getStorage(ECS::componentType::VELOCITY), entities);

    std::vector<entityType> playerCollisionTypes = {entityType::ALIEN_SHOOT};
    std::vector<entityType> playerShootCollisionTypes = {entityType::PLAYER_SHOOT};

    for (auto& ent: entities) {
        auto& details = engine.getComponent<ECS::entityDetails>(ent, ECS::ENTITY_DETAILS);
        if (engine.getStorage(ECS::PLAYER)->hasComponent(ent) == true) {
            checkCollision(ent, entities, engine, playerCollisionTypes);
        } else if (details._type == PLAYER_SHOOT) {
            checkCollision(ent, entities, engine, playerShootCollisionTypes);
        }
    }
}

void ECS::collisionSystem::checkCollision(const Entity ent, std::vector<Entity>& entities, ECS::ECSEngine& engine, std::vector<entityType>& CollisionTypes)
{
    auto& playerPos = engine.getComponent<ECS::Position>(ent, ECS::POSITION);
    auto& playerDim = engine.getComponent<ECS::Dimensions>(ent, ECS::DIMENSIONS);
    auto& playerLife = engine.getComponent<ECS::Life>(ent, ECS::LIFE);

    Position playerPosMax(playerPos._x + playerDim._x, playerPos._y + playerDim._y);
    unsigned int posXMax = 0;
    unsigned int posYMax = 0;
    for (auto obstacle = entities.begin(); obstacle != entities.end(); obstacle++) {
        if (engine.getStorage(ECS::PLAYER)->hasComponent(*obstacle) != true) {
            auto& pos = engine.getComponent<ECS::Position>(*obstacle, ECS::POSITION);
            auto& dim = engine.getComponent<ECS::Dimensions>(*obstacle, ECS::DIMENSIONS);
            auto& details = engine.getComponent<ECS::entityDetails>(*obstacle, ECS::ENTITY_DETAILS);
            if (isPossibleCollision(details._type, CollisionTypes) == true) {
                posXMax = pos._x + dim._x;
                posYMax = pos._y + dim._y;
                Position interPos = findIntersection(playerPos, playerPosMax, pos, Position(posXMax, posYMax));
                if (interPos._x != -1) {
                    playerLife._hp -= 1;
                    if (isExplodable(details._type) == true) {
                        engine.removeEntity(*obstacle);
                        entities.erase(obstacle);
                        obstacle--;
                    }
                    // createBomb();
                }
            }
        }
    }
}

bool ECS::collisionSystem::isPossibleCollision(const entityType type, std::vector<entityType>& types)
{
    for (auto& cType : types) {
        if (cType == type)
            return (true);
    }
    return (false);
}

bool ECS::collisionSystem::isExplodable(const entityType type)
{
    if (type == entityType::ALIEN_SHOOT || type == entityType::PLAYER_SHOOT)
        return (true);
    return (false);
}

ECS::Position ECS::collisionSystem::findIntersection(const Position& playerPos, const Position& playerMaxpos, const Position& entPos, const Position& entMaxPos) const
{
    int x5 = std::max(playerPos._x, entPos._x); 
    int y5 = std::max(playerPos._y, entPos._y); 
  
    int x6 = std::min(playerMaxpos._x, entMaxPos._x); 
    int y6 = std::min(playerMaxpos._y, entMaxPos._y); 
  
    if (x5 > x6 || y5 > y6) { 
        std::cout << "No intersection" << std::endl;
        return (Position(-1, -1));
    }
    return (Position((x5 + x6) / 2, (y5 + y6) / 2));
}

void createBomb(const Position& pos, ECS::ECSEngine& engine)
{
    Entity ent = engine.getNewEntity();

    engine.addComponent(ent, pos, ECS::POSITION);
    engine.addComponent(ent, ECS::entityDetails(BOMB, entityState::BASIC), ECS::ENTITY_DETAILS);
}