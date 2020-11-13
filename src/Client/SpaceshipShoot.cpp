/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** SpaceshipShoot
*/

#include "SpaceshipShoot.hpp"
#include <iostream>

Graphic::SpaceshipShoot::SpaceshipShoot(int id, bool bonus, const sf::Vector2f& test, const animation& anime) : 
Graphic::Entity(id, SPACESHIP_SHOOT, bonus, test, anime)
{
}

Graphic::SpaceshipShoot::~SpaceshipShoot()
{}

entityType Graphic::SpaceshipShoot::getType() const
{
    return _type;
}
