/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AEntity.cpp
*/

#include "AEntity.hpp"


Graphic::AEntity::AEntity(const Object &type, bool bonus, const sf::Vector2f &test) : _type(type), 
_pos(test), _bonus(bonus)
{
}

Graphic::AEntity::~AEntity()
{}

Graphic::Object Graphic::AEntity::getObject() const
{
    return (_type);
}