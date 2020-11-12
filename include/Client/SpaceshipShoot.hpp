/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** SpaceshipShoot
*/

#ifndef SPACESHIPSHOOT_HPP_
#define SPACESHIPSHOOT_HPP_

#include "Entity.hpp"

namespace Graphic {
class SpaceshipShoot : public Graphic::Entity {
    public:
        SpaceshipShoot(bool bonus, const sf::Vector2f &test, const animation &anime);
        ~SpaceshipShoot();
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !SPACESHIPSHOOT_HPP_ */
