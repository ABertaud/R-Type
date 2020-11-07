/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** players.hpp
*/

#ifndef PLAYERS_HPP_
#define PLAYERS_HPP_

#include "entityType.hpp"

class players
{
public:
    enum State
    {
        ACTIVE = 1,
        OFF = 2,
        READY = 3,
    };
public:
    players(const entityType &type);
    ~players();
    void setState(const State &);
    State getState()const;
    entityType getObject()const;

private:
    State _state;
    entityType _type;
};

#endif