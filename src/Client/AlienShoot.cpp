/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AlienShoot
*/

#include "AlienShoot.hpp"
#include <iostream>

Graphic::AlienShoot::AlienShoot(bool bonus, const sf::Vector2f &test, const animation &anime) : 
Graphic::Entity(ALIEN_SHOOT, bonus, test, anime)
{
}

Graphic::AlienShoot::~AlienShoot()
{
}

entityType Graphic::AlienShoot::getType() const
{
    return _type;
}