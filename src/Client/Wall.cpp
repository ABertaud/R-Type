/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Wall.cpp
*/

#include "Wall.hpp"
#include <iostream>

Graphic::Wall::Wall(bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(WALL, bonus, test)
{
}

Graphic::Wall::~Wall()
{}

void Graphic::Wall::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::Wall::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::Wall::getType() const
{
    return _type;
}