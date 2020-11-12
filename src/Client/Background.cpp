/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Background
*/

#include "Background.hpp"
#include <iostream>

Graphic::Background::Background(bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(BACKGROUND, bonus, test)
{
}

Graphic::Background::~Background()
{}

void Graphic::Background::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::Background::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

entityType Graphic::Background::getType() const
{
    return _type;
}