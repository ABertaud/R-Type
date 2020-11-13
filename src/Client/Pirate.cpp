/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Pirate
*/

#include "Pirate.hpp"
#include <iostream>

Graphic::Pirate::Pirate(int id, bool bonus, const sf::Vector2f &test, const animation &anime) : 
Graphic::Entity(id, PIRATE, bonus, test, anime)
{
}

Graphic::Pirate::~Pirate()
{}

entityType Graphic::Pirate::getType() const
{
    return _type;
}
