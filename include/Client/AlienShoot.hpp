/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AlienShoot
*/

#ifndef ALIENSHOOT_HPP_
#define ALIENSHOOT_HPP_

#include "AEntity.hpp"

namespace Graphic {
class AlienShoot : public Graphic::AEntity {
    public:
        AlienShoot(bool bonus, const sf::Vector2f &test);
        ~AlienShoot();
        void update(const sf::Vector2f& pos);
        void update(int x, int y);
        entityType getType()const;
    private:
    protected:
};
}

#endif /* !ALIENSHOOT_HPP_ */
