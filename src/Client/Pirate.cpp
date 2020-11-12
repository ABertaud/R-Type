/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Pirate
*/

#include "Pirate.hpp"
#include <iostream>

Graphic::Pirate::Pirate(bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(PIRATE, bonus, test)
{
}

Graphic::Pirate::~Pirate()
{}

void Graphic::Pirate::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::Pirate::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::Pirate::getType() const
{
    return _type;
}
