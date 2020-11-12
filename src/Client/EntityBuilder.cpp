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

const Graphic::Entity &EntityBuilder::createEntity(int entityId, const entityType& entityType, bool bonus, const sf::Vector2f& entityPos)
{
    if (entityType == BACKGROUND)
        return (Graphic::Background(bonus, entityPos, ANIMATION_0));
    else if (entityType == P1 || entityType == P2 || entityType == P3 ||  entityType == P4)
        return (Graphic::Player(entityType, bonus, entityPos, ANIMATION_0));
    else if (entityType == WALL)
        return (Graphic::Wall(bonus, entityPos, ANIMATION_0));
    else if (entityType == OBSTACLE)
        return (Graphic::Obstacle(bonus, entityPos, ANIMATION_0));
    else if (entityType == PLAYER_SHOOT)
        return (Graphic::PlayerShoot(bonus, entityPos, ANIMATION_0));
    else if (entityType == ALIEN)
        return (Graphic::Alien(bonus, entityPos, ANIMATION_0));
    else if (entityType == ALIEN_SHOOT)
        return (Graphic::AlienShoot(bonus, entityPos, ANIMATION_0));
    else if (entityType == UFO)
        return (Graphic::Ufo(bonus, entityPos, ANIMATION_0));
    else if (entityType == UFO_SHOOT)
        return (Graphic::UfoShoot(bonus, entityPos, ANIMATION_0));
    else if (entityType == SPACESHIP)
        return (Graphic::Spaceship(bonus, entityPos, ANIMATION_0));
    else if (entityType == SPACESHIP_SHOOT)
        return (Graphic::SpaceshipShoot(bonus, entityPos, ANIMATION_0));
    else if (entityType == PIRATE)
        return (Graphic::Pirate(bonus, entityPos, ANIMATION_0));
    else if (entityType == PIRATE_SHOOT)
        return (Graphic::PirateShoot(bonus, entityPos, ANIMATION_0));
}