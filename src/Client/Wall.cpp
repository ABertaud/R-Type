/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Wall.cpp
*/

#include "Wall.hpp"
#include <iostream>

Graphic::Wall::Wall(bool bonus, const sf::Vector2f &test, const animation &anime) : 
Graphic::Entity(WALL, bonus, test, anime)
{
}

Graphic::Wall::~Wall()
{}

entityType Graphic::Wall::getType() const
{
    return _type;
}