/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AlienShoot
*/

#ifndef ALIENSHOOT_HPP_
#define ALIENSHOOT_HPP_

#include "Entity.hpp"

namespace Graphic {
class AlienShoot : public Graphic::Entity {
    public:
        AlienShoot(bool bonus, const sf::Vector2f &test, const animation &anime);
        ~AlienShoot();
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !ALIENSHOOT_HPP_ */
