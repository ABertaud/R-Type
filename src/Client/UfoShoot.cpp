/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** UfoShoot
*/

#include "UfoShoot.hpp"
#include <iostream>

Graphic::UfoShoot::UfoShoot(bool bonus, const sf::Vector2f &test, const animation &anime) : 
Graphic::Entity(UFO_SHOOT, bonus, test, anime)
{
}

Graphic::UfoShoot::~UfoShoot()
{}

entityType Graphic::UfoShoot::getType() const
{
    return _type;
}
