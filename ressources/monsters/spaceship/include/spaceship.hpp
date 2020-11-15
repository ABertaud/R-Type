/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** spaceship.hpp
*/

#ifndef SPACESHIP_HPP_
#define SPACESHIP_HPP_

#include "AMonster.hpp"
#include "Position.hpp"

class spaceship : public AMonster
{
    public:
        spaceship();
        spaceship(const spaceship& other) = default;
        spaceship& operator=(const spaceship& other) = default;
        void init(ECS::ECSEngine&);
        void update(const float dt, ECS::ECSEngine&);
        ~spaceship() = default;
    private:
        void createShoot(const ECS::Position& pos, ECS::ECSEngine& engine);
};

#endif /* !SPACESHIP_HPP_ */
