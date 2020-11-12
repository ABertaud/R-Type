/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Obstacle
*/

#include "Obstacle.hpp"
#include <iostream>

Graphic::Obstacle::Obstacle(bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(OBSTACLE, bonus, test)
{
}

Graphic::Obstacle::~Obstacle()
{}

void Graphic::Obstacle::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::Obstacle::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::Obstacle::getType() const
{
    return _type;
}