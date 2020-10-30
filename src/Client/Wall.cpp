/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Wall.cpp
*/

#include "Wall.hpp"
#include <iostream>

Wall::Wall(const Object &type, bool bonus, const sf::Vector2f &test) : 
AEntity(type, bonus, test)
{
}

Wall::~Wall()
{}

void Wall::update()
{
    std::cout << "update" << std::endl;
}

Object Wall::getObject() const
{
    return _type;
}