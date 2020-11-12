/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** PlayerShoot
*/

#include "PlayerShoot.hpp"
#include <iostream>

Graphic::PlayerShoot::PlayerShoot(bool bonus, const sf::Vector2f &test) : 
Graphic::Entity(PLAYER_SHOOT, bonus, test)
{
}

Graphic::PlayerShoot::~PlayerShoot()
{}

entityType Graphic::PlayerShoot::getType() const
{
    return _type;
}