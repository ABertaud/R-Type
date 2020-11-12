/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Pirate
*/

#include "Pirate.hpp"
#include <iostream>

Graphic::Pirate::Pirate(bool bonus, const sf::Vector2f &test) : 
Graphic::Entity(PIRATE, bonus, test)
{
}

Graphic::Pirate::~Pirate()
{}

entityType Graphic::Pirate::getType() const
{
    return _type;
}
