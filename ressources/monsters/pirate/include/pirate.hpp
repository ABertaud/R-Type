/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** pirate.hpp
*/

#ifndef PIRATE_HPP_
#define PIRATE_HPP_

#include "AMonster.hpp"

class pirate : public AMonster
{
    public:
        pirate();
        pirate(const pirate& other) = default;
        pirate& operator=(const pirate& other) = default;
        void init(ECS::ECSEngine&);
        void update(const float dt, ECS::ECSEngine&);
        ~pirate() = default;
    private:
};

#endif /* !PIRATE_HPP_ */
