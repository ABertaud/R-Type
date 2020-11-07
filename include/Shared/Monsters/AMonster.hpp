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
        AMonster();
        AMonster(const AMonster& other) = default;
        AMonster& operator=(const AMonster& other) = default;
        virtual void update() = 0;
        virtual ~AMonster() = default;
    protected:
    private:
};

#endif /* !AMONSTER_HPP_ */
