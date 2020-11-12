/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Alien
*/

#ifndef ALIEN_HPP_
#define ALIEN_HPP_

#include "AEntity.hpp"

namespace Graphic {
class Alien : public Graphic::AEntity {
    public:
        Alien(bool bonus, const sf::Vector2f &test);
        ~Alien();
        void update(const sf::Vector2f& pos);
        void update(int x, int y);
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !ALIEN_HPP_ */
