/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** ufo.hpp
*/

#ifndef UFO_HPP_
#define UFO_HPP_

#include "AMonster.hpp"

class ufo : public AMonster
{
    public:
        ufo();
        ufo(const ufo& other) = default;
        ufo& operator=(const ufo& other) = default;
        void init(ECS::ECSEngine&);
        void update(const float dt, ECS::ECSEngine&);
        ~ufo() = default;
    private:
    int _time;
    int _speed;
    int _zone;
    bool _way;
};

#endif /* !UFO_HPP_ */
