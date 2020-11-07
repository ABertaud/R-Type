/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** sample.cpp
*/

#include "sample.hpp"
#include <iostream>
#include <memory>

sample::sample() : AMonster()
{

}

void sample::init(ECS::ECSEngine& engine)
{
    (void)engine;
    std::cout << engine.getNewEntity() << std::endl;
    std::cout << "INIT WELL" << std::endl;
}

void sample::update()
{
    std::cout << "I'M A SAMPLE" << std::endl;
}

extern "C" std::unique_ptr<IMonster> entryPoint()
{
    return (std::make_unique<sample>());
}