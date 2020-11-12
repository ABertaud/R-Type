/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Spaceship
*/

#ifndef SPACESHIP_HPP_
#define SPACESHIP_HPP_

#include "AEntity.hpp"

namespace Graphic {
class Spaceship : public Graphic::AEntity {
    public:
        Spaceship(bool bonus, const sf::Vector2f &test);
        ~Spaceship();
        void update(const sf::Vector2f& pos);
        void update(int x, int y);
        entityType getType()const;
    private:
    protected:
};
}
#endif /* !SPACESHIP_HPP_ */
