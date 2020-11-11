/*
** EPITECH PROJECT, 2020
** B-CPP-501-rtype
** File description:
** EntityBuilder
*/

#include "EntityBuilder.hpp"
#include "Wall.hpp"

EntityBuilder::EntityBuilder()
{
}

const Graphic::AEntity &EntityBuilder::createEntity(int entityId, const entityType& entityType, bool bonus, const sf::Vector2f& entityPos)
{
    if (entityType == WALL)
        return (Graphic::Wall(entityType, bonus, entityPos));
}