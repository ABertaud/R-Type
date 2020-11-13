/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** PlayerShoot
*/

#include "PlayerShoot.hpp"
#include <iostream>

Graphic::PlayerShoot::PlayerShoot(int id, bool bonus, const sf::Vector2f& test, const animation& anime) : 
Graphic::Entity(id, PLAYER_SHOOT, bonus, test, anime)
{
}

Graphic::PlayerShoot::~PlayerShoot()
{}

entityType Graphic::PlayerShoot::getType() const
{
    return _type;
}