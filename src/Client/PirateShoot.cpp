/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** PirateShoot
*/

#include "PirateShoot.hpp"
#include <iostream>

Graphic::PirateShoot::PirateShoot(bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(PIRATE_SHOOT, bonus, test)
{
}

Graphic::PirateShoot::~PirateShoot()
{}

void Graphic::PirateShoot::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::PirateShoot::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::PirateShoot::getType() const
{
    return _type;
}