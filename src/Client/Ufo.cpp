/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Ufo
*/

#include "Ufo.hpp"
#include <iostream>

Graphic::Ufo::Ufo(bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(UFO, bonus, test)
{
}

Graphic::Ufo::~Ufo()
{}

void Graphic::Ufo::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::Ufo::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::Ufo::getType() const
{
    return _type;
}
