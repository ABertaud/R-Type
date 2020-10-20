/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AMonster.cpp
*/

#include "AMonster.hpp"

AMonster::AMonster(unsigned int attack, int hp) : _attack(attack), _hp(hp)
{
    
}

int AMonster::getHp() const
{
    return (_hp);
}

unsigned int AMonster::getAttack() const
{
    return (_attack);
}