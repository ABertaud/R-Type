/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Spaceship
*/

#include "Spaceship.hpp"
#include <iostream>

Graphic::Spaceship::Spaceship(int id, bool bonus, const sf::Vector2f &test, const animation &anime) : 
Graphic::Entity(id, SPACESHIP, bonus, test, anime)
{
}

Graphic::Spaceship::~Spaceship()
{}

entityType Graphic::Spaceship::getType() const
{
    return _type;
}
