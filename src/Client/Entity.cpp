/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Entity.cpp
*/

#include "Entity.hpp"


Graphic::Entity::Entity(const entityType &type, bool bonus, const sf::Vector2f &pos) : _type(type), 
_pos(pos), _bonus(bonus), _scale({1, 1}), _animation(sf::seconds(0.2))
{

}

Graphic::Entity::~Entity()
{
}

void Graphic::Entity::update(const sf::Vector2f& pos)
{
    _pos = pos;
}

void Graphic::Entity::update(int x, int y)
{
    _pos.x = x;
    _pos.y = y;
}

void Graphic::Entity::setscale(const sf::Vector2f &scale)
{
    _scale = scale;
}

entityType Graphic::Entity::getType() const
{
    return (_type);
}

sf::Vector2f Graphic::Entity::getPos() const
{
    return (_pos);
}

Animation &Graphic::Entity::getAnimation()
{
    return (_animation);
}

int Graphic::Entity::getId(void) const
{
    return (_id);
}