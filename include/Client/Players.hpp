/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Players.hpp
*/

#ifndef PLAYERS_HPP_
#define PLAYERS_HPP_

#include "entityType.hpp"

class Players
{
public:
    enum State
    {
        ACTIVE = 1,
        OFF = 2,
        READY = 3,
    };
public:
    Players(const entityType &type);
    ~Players();
    void setState(const State &);
    State getState()const;
    entityType getType()const;

private:
    State _state;
    entityType _type;
};

#endif