/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Explosion.hpp
*/

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include "Entity.hpp"

namespace Graphic {
class Explosion : public Graphic::Entity {
    public:
        Explosion(int id, bool bonus, const sf::Vector2f& test, const animationState& anime);
        ~Explosion();
        entityType getType()const;
    private:
    protected:
};
}

#endif