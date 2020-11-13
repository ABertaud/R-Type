/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Alien
*/

#include "Alien.hpp"
#include <iostream>

Graphic::Alien::Alien(int id, bool bonus, const sf::Vector2f& test, const animation& anime) : 
Graphic::Entity(id, ALIEN, bonus, test, anime)
{
}

Graphic::Alien::~Alien()
{}

entityType Graphic::Alien::getType() const
{
    return _type;
}