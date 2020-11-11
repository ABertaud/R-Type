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
    private:
    public:
        Player(const entityType &type, bool bonus, const sf::Vector2f &test);
        ~Player();
        void update();
        entityType getObject()const;   // return the type of the object
    };
}

#endif