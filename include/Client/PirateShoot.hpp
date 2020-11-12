/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** PirateShoot
*/

#ifndef PIRATESHOOT_HPP_
#define PIRATESHOOT_HPP_

#include "AEntity.hpp"

namespace Graphic {
class PirateShoot : public Graphic::AEntity {
    public:
        PirateShoot(bool bonus, const sf::Vector2f &test);
        ~PirateShoot();
        void update(const sf::Vector2f& pos);
        void update(int x, int y);
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !PIRATESHOOT_HPP_ */
