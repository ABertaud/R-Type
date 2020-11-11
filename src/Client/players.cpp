/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** players.cpp
*/

#include "players.hpp"

players::players(const entityType &type) : _type(type)
{
}

players::~players()
{
}

void players::setState(const State &state)
{
    _state = state;
}

entityType players::getType()const
{
    return (_type);
}

players::State players::getState()const
{
    return (_state);
}