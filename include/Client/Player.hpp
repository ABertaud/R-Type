/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "AEntity.hpp"

namespace Graphic {
class Player : public Graphic::AEntity {
    public:
        Player(const entityType &type, bool bonus, const sf::Vector2f &test);
        ~Player();
        void update(const sf::Vector2f& pos);
        void update(int x, int y);
        entityType getType()const;
    private:
    protected:
    };
}

#endif