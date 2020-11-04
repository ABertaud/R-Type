/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "IComponents.hpp"
#include "Client.hpp"

namespace ECS {
    enum currentMovement {
        UP,
        DOWN,
        RIGHT,
        LEFT,
        NONE,
    };

    struct Player : public IComponents {
        Player() = default;
        Player(const Client::playerNumber player);
        Player(const Player& other) = default;
        Player& operator=(const Player& other) = default; 
        ~Player() = default;
        Client::playerNumber _player;
        currentMovement _direction;
    };
}

#endif /* !PLAYER_HPP_ */
