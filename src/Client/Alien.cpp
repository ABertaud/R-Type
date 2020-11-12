/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Alien
*/

#include "Alien.hpp"
#include <iostream>

Graphic::Alien::Alien(bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(ALIEN, bonus, test)
{
}

Graphic::Alien::~Alien()
{}

void Graphic::Alien::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::Alien::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::Alien::getType() const
{
    return _type;
}