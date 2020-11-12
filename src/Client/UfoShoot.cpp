/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** UfoShoot
*/

#include "UfoShoot.hpp"
#include <iostream>

Graphic::UfoShoot::UfoShoot(bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(UFO_SHOOT, bonus, test)
{
}

Graphic::UfoShoot::~UfoShoot()
{}

void Graphic::UfoShoot::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::UfoShoot::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::UfoShoot::getType() const
{
    return _type;
}
