/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** SpaceshipShoot
*/

#ifndef SPACESHIPSHOOT_HPP_
#define SPACESHIPSHOOT_HPP_

#include "AEntity.hpp"

namespace Graphic {
class SpaceshipShoot : public Graphic::AEntity {
    public:
        SpaceshipShoot(bool bonus, const sf::Vector2f &test);
        ~SpaceshipShoot();
        void update(const sf::Vector2f& pos);
        void update(int x, int y);
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !SPACESHIPSHOOT_HPP_ */
