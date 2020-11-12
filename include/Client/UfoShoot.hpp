/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** UfoShoot
*/

#ifndef UFOSHOOT_HPP_
#define UFOSHOOT_HPP_

#include "AEntity.hpp"

namespace Graphic {
class UfoShoot : public Graphic::AEntity {
    public:
        UfoShoot(bool bonus, const sf::Vector2f &test);
        ~UfoShoot();
        void update(const sf::Vector2f& pos);
        void update(int x, int y);
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !UFOSHOOT_HPP_ */
