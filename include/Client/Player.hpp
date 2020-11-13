/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Entity.hpp"

namespace Graphic {
class Player : public Graphic::Entity {
    public:
        Player(int id, const entityType& type, bool bonus, const sf::Vector2f& test, const animation& anime);
        ~Player();
        entityType getType()const;
    private:
    protected:
    };
}

#endif