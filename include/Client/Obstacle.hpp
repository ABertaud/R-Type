/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Obstacle
*/

#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include "Entity.hpp"

namespace Graphic {
class Obstacle : public Graphic::Entity {
    public:
        Obstacle(bool bonus, const sf::Vector2f &test, const animation &anime);
        ~Obstacle();
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !OBSTACLE_HPP_ */
