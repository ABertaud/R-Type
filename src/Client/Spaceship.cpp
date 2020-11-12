/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Spaceship
*/

#include "Spaceship.hpp"
#include <iostream>

Graphic::Spaceship::Spaceship(bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(SPACESHIP, bonus, test)
{
}

Graphic::Spaceship::~Spaceship()
{}

void Graphic::Spaceship::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::Spaceship::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::Spaceship::getType() const
{
    return _type;
}
