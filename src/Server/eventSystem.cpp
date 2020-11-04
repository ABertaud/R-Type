/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** eventSystem.cpp
*/

#include "eventSystem.hpp"

ECS::eventSystem::eventSystem(const std::shared_ptr<Buffer>& buffer) : ECS::ASystem(), _buffer(buffer)
{
}

void ECS::eventSystem::update(const float dt, ECS::ECSEngine& engine)
{
    (void)dt;
    (void)engine;
}