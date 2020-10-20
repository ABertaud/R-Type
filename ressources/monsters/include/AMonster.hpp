/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** AMonster.hpp
*/

#ifndef AMONSTER_HPP_
#define AMONSTER_HPP_

#include "IMonster.hpp"

class AMonster : public IMonster
{
    public:
        AMonster(unsigned int attack, int hp);
        AMonster(const AMonster &other) = default;
        AMonster &operator=(const AMonster &other) = default;
        int getHp() const;
        unsigned int getAttack() const;
        virtual void update() = 0;
        virtual ~AMonster() = default;
    protected:
    private:
        unsigned int _attack;
        int _hp;
};

#endif /* !AMONSTER_HPP_ */
