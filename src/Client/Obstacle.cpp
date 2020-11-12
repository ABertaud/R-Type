/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Obstacle
*/

#include "Obstacle.hpp"
#include <iostream>

Graphic::Obstacle::Obstacle(bool bonus, const sf::Vector2f &test) : 
Graphic::Entity(OBSTACLE, bonus, test)
{
}

Graphic::Obstacle::~Obstacle()
{}

entityType Graphic::Obstacle::getType() const
{
    return _type;
}