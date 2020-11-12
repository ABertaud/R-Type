/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Alien
*/

#ifndef ALIEN_HPP_
#define ALIEN_HPP_

#include "Entity.hpp"

namespace Graphic {
class Alien : public Graphic::Entity {
    public:
        Alien(bool bonus, const sf::Vector2f &test);
        ~Alien();
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !ALIEN_HPP_ */
