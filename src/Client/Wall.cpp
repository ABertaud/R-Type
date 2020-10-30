/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Wall.cpp
*/

#include "Wall.hpp"
#include <iostream>

Graphic::Wall::Wall(const Graphic::Object &type, bool bonus, const sf::Vector2f &test) : 
Graphic::AEntity(type, bonus, test)
{
}

Graphic::Wall::~Wall()
{}

void Graphic::Wall::update()
{
    std::cout << "update" << std::endl;
}

Graphic::Object Graphic::Wall::getObject() const
{
    return _type;
}