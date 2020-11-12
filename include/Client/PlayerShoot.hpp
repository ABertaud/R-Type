/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** PlayerShoot
*/

#ifndef PLAYERSHOOT_HPP_
#define PLAYERSHOOT_HPP_

#include "AEntity.hpp"

namespace Graphic {
class PlayerShoot : public Graphic::AEntity {
    public:
        PlayerShoot(bool bonus, const sf::Vector2f &test);
        ~PlayerShoot();
        void update(const sf::Vector2f& pos);
        void update(int x, int y);
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !PLAYERSHOOT_HPP_ */
