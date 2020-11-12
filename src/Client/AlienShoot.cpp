/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AlienShoot
*/

#include "AlienShoot.hpp"
#include <iostream>

Graphic::AlienShoot::AlienShoot(bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(ALIEN_SHOOT, bonus, test)
{
}

Graphic::AlienShoot::~AlienShoot()
{}

void Graphic::AlienShoot::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::AlienShoot::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::AlienShoot::getType() const
{
    return _type;
}