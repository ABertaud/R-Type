/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Wall.hpp
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include "Entity.hpp"

namespace Graphic {
class Wall : public Graphic::Entity {
    public:
        Wall(bool bonus, const sf::Vector2f &test);
        ~Wall();
        entityType getType()const;
    private:
    protected:
};
}

#endif