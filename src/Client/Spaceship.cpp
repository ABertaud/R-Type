/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Spaceship
*/

#include "Spaceship.hpp"
#include <iostream>

Graphic::Spaceship::Spaceship(bool bonus, const sf::Vector2f &test) : 
Graphic::Entity(SPACESHIP, bonus, test)
{
}

Graphic::Spaceship::~Spaceship()
{}

entityType Graphic::Spaceship::getType() const
{
    return _type;
}
