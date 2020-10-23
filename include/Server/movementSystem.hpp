/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** movementSystem.hpp
*/

#ifndef MOVEMENTSYSTEM_HPP_
#define MOVEMENTSYSTEM_HPP_

#include "ASystem.hpp"
#include "Position.hpp"
#include "Velocity.hpp"

class movementSystem : public ASystem
{
public:
    movementSystem();
    movementSystem(const movementSystem &other) = default;
    movementSystem &operator=(const movementSystem &other) = default;
    void update(const float dt, ECSEngine &engine);
    void applyPhysic(Position &pos, Velocity &vel, const float dt);
    ~movementSystem() = default;
};

#endif /* !MOVEMENTSYSTEM_HPP_ */
