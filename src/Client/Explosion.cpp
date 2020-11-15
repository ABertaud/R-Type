/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Explosion
*/

#include "Explosion.hpp"
#include <iostream>

Graphic::Explosion::Explosion(int id, bool bonus, const sf::Vector2f& test, const animationState& anime) : 
Graphic::Entity(id, ALIEN_SHOOT, bonus, test, anime)
{
}

Graphic::Explosion::~Explosion()
{
}

entityType Graphic::Explosion::getType() const
{
    return _type;
}