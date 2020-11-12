/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Obstacle
*/

#ifndef OBSTACLE_HPP_
#define OBSTACLE_HPP_

#include "AEntity.hpp"

namespace Graphic {
class Obstacle : public Graphic::AEntity {
    public:
        Obstacle(bool bonus, const sf::Vector2f &test);
        ~Obstacle();
        void update(const sf::Vector2f& pos);
        void update(int x, int y);
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !OBSTACLE_HPP_ */
