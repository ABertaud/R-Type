/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** IMonster.hpp
*/

#ifndef IMONSTER_HPP_
#define IMONSTER_HPP_

class IMonster {
    public:
        virtual ~IMonster() = default;
        virtual int getHp() const = 0;
        virtual unsigned int getAttack() const = 0;
        virtual void update() = 0;
    protected:
    private:
};

#endif /* !IMONSTER_HPP_ */
