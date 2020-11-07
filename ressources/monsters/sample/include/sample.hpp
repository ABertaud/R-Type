/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** sample.hpp
*/

#ifndef SAMPLE_HPP_
#define SAMPLE_HPP_

#include "AMonster.hpp"

class sample : public AMonster
{
    public:
        sample();
        sample(const sample& other) = default;
        sample& operator=(const sample& other) = default;
        void init(ECS::ECSEngine&);
        void update();
        ~sample() = default;
    private:
};

#endif /* !SAMPLE_HPP_ */
