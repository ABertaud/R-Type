/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Ufo
*/

#include "Ufo.hpp"
#include <iostream>

Graphic::Ufo::Ufo(int id, bool bonus, const sf::Vector2f& test, const animation& anime) : 
Graphic::Entity(id, UFO, bonus, test, anime)
{
}

Graphic::Ufo::~Ufo()
{}

entityType Graphic::Ufo::getType() const
{
    return _type;
}
