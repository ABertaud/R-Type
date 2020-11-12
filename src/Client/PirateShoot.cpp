/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** PirateShoot
*/

#include "PirateShoot.hpp"
#include <iostream>

Graphic::PirateShoot::PirateShoot(bool bonus, const sf::Vector2f &test) : 
Graphic::Entity(PIRATE_SHOOT, bonus, test)
{
}

Graphic::PirateShoot::~PirateShoot()
{}

entityType Graphic::PirateShoot::getType() const
{
    return _type;
}