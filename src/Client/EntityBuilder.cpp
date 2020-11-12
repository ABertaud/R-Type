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

const Graphic::AEntity &EntityBuilder::createEntity(int entityId, const entityType& entityType, bool bonus, const sf::Vector2f& entityPos)
{
    if (entityType == BACKGROUND)
        return (Graphic::Background(bonus, entityPos));
    if (entityType == P1 || entityType == P2 || entityType == P3 || entityType == P4)
        return (Graphic::Player(entityType, bonus, entityPos));
    if (entityType == WALL)
        return (Graphic::Wall(bonus, entityPos));
    if (entityType == OBSTACLE)
        return (Graphic::Obstacle(bonus, entityPos));
    if (entityType == PLAYER_SHOOT)
        return (Graphic::PlayerShoot(bonus, entityPos));
    if (entityType == ALIEN)
        return (Graphic::Alien(bonus, entityPos));
    if (entityType == ALIEN_SHOOT)
        return (Graphic::AlienShoot(bonus, entityPos));
    if (entityType == UFO)
        return (Graphic::Ufo(bonus, entityPos));
    if (entityType == UFO_SHOOT)
        return (Graphic::UfoShoot(bonus, entityPos));
    if (entityType == SPACESHIP)
        return (Graphic::Spaceship(bonus, entityPos));
    if (entityType == SPACESHIP_SHOOT)
        return (Graphic::SpaceshipShoot(bonus, entityPos));
    if (entityType == PIRATE)
        return (Graphic::Pirate(bonus, entityPos));
    if (entityType == PIRATE_SHOOT)
        return (Graphic::PirateShoot(bonus, entityPos));

}