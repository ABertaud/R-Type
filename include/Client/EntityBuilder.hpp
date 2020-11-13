/*
** EPITECH PROJECT, 2020
** B-CPP-501-rtype
** File description:
** EntityManager
*/

#ifndef ENTITYBUILDER_HPP_
#define ENTITYBUILDER_HPP_

#include "Entity.hpp"

class EntityBuilder {
    public:
        EntityBuilder();
        ~EntityBuilder()=default;
        const Graphic::Entity& createEntity(int entityId, const entityType& entityType, bool bonus, const sf::Vector2f& entityPos);
};

#endif /* !ENTITYBUILDER_HPP_ */
