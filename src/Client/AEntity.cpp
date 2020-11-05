/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AEntity.cpp
*/

#include "AEntity.hpp"


Graphic::AEntity::AEntity(const entityType &type, bool bonus, const sf::Vector2f &pos) : _type(type), 
_pos(pos), _bonus(bonus), _scale({1, 1})
{

}

Graphic::AEntity::~AEntity()
{}

void Graphic::AEntity::setscale(const sf::Vector2f &scale)
{
    _scale = scale;
}

entityType Graphic::AEntity::getObject() const
{
    return (_type);
}

sf::Vector2f Graphic::AEntity::getPos() const
{
    return (_pos);
}