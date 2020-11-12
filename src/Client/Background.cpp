/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Background
*/

#include "Background.hpp"
#include <iostream>

Graphic::Background::Background(bool bonus, const sf::Vector2f &test, const animation &anime) : 
Graphic::Entity(BACKGROUND, bonus, test, anime)
{
}

Graphic::Background::~Background()
{}

entityType Graphic::Background::getType() const
{
    return _type;
}