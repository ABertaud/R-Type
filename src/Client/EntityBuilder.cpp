/*
** EPITECH PROJECT, 2020
** B-CPP-501-rtype
** File description:
** EntityBuilder
*/

#include "EntityBuilder.hpp"
#include "Wall.hpp"
#include "Player.hpp"
#include "Background.hpp"
#include "Obstacle.hpp"
#include "PlayerShoot.hpp"
#include "Alien.hpp"
#include "AlienShoot.hpp"
#include "Ufo.hpp"
#include "UfoShoot.hpp"
#include "Spaceship.hpp"
#include "SpaceshipShoot.hpp"
#include "Pirate.hpp"
#include "PirateShoot.hpp"

EntityBuilder::EntityBuilder()
{
}

const Graphic::Entity& EntityBuilder::createEntity(int entityId, const entityType& entityType, bool bonus, const sf::Vector2f& entityPos)
{
    if (entityType == BACKGROUND)
        return (Graphic::Background(entityId, bonus, entityPos, ANIMATION_0));
    else if (entityType == P1 || entityType == P2 || entityType == P3 ||  entityType == P4)
        return (Graphic::Player(entityId, entityType, bonus, entityPos, ANIMATION_0));
    else if (entityType == WALL)
        return (Graphic::Wall(entityId, bonus, entityPos, ANIMATION_0));
    else if (entityType == OBSTACLE)
        return (Graphic::Obstacle(entityId, bonus, entityPos, ANIMATION_0));
    else if (entityType == PLAYER_SHOOT)
        return (Graphic::PlayerShoot(entityId, bonus, entityPos, ANIMATION_0));
    else if (entityType == ALIEN)
        return (Graphic::Alien(entityId, bonus, entityPos, ANIMATION_0));
    else if (entityType == ALIEN_SHOOT)
        return (Graphic::AlienShoot(entityId, bonus, entityPos, ANIMATION_0));
    else if (entityType == UFO)
        return (Graphic::Ufo(entityId, bonus, entityPos, ANIMATION_0));
    else if (entityType == UFO_SHOOT)
        return (Graphic::UfoShoot(entityId, bonus, entityPos, ANIMATION_0));
    else if (entityType == SPACESHIP)
        return (Graphic::Spaceship(entityId, bonus, entityPos, ANIMATION_0));
    else if (entityType == SPACESHIP_SHOOT)
        return (Graphic::SpaceshipShoot(entityId, bonus, entityPos, ANIMATION_0));
    else if (entityType == PIRATE)
        return (Graphic::Pirate(entityId, bonus, entityPos, ANIMATION_0));
    else if (entityType == PIRATE_SHOOT)
        return (Graphic::PirateShoot(entityId, bonus, entityPos, ANIMATION_0));
}