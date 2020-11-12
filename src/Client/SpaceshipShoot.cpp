/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** SpaceshipShoot
*/

#include "SpaceshipShoot.hpp"
#include <iostream>

Graphic::SpaceshipShoot::SpaceshipShoot(bool bonus, const sf::Vector2f &test) : 
Graphic::Entity(SPACESHIP_SHOOT, bonus, test)
{
}

Graphic::SpaceshipShoot::~SpaceshipShoot()
{}

entityType Graphic::SpaceshipShoot::getType() const
{
    return _type;
}
