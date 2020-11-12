/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** SpaceshipShoot
*/

#include "SpaceshipShoot.hpp"
#include <iostream>

Graphic::SpaceshipShoot::SpaceshipShoot(bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(SPACESHIP_SHOOT, bonus, test)
{
}

Graphic::SpaceshipShoot::~SpaceshipShoot()
{}

void Graphic::SpaceshipShoot::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::SpaceshipShoot::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::SpaceshipShoot::getType() const
{
    return _type;
}
