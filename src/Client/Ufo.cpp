/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Ufo
*/

#include "Ufo.hpp"
#include <iostream>

Graphic::Ufo::Ufo(bool bonus, const sf::Vector2f &test) : 
Graphic::Entity(UFO, bonus, test)
{
}

Graphic::Ufo::~Ufo()
{}

entityType Graphic::Ufo::getType() const
{
    return _type;
}
