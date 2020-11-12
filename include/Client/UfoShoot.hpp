/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** UfoShoot
*/

#ifndef UFOSHOOT_HPP_
#define UFOSHOOT_HPP_

#include "Entity.hpp"

namespace Graphic {
class UfoShoot : public Graphic::Entity {
    public:
        UfoShoot(bool bonus, const sf::Vector2f &test, const animation &anime);
        ~UfoShoot();
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !UFOSHOOT_HPP_ */
