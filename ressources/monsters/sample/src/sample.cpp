/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** sample.cpp
*/

#include "sample.hpp"
#include <iostream>

sample::sample() : AMonster(5, 40)
{

}

void sample::update()
{
    std::cout << "I'M A SAMPLE" << std::endl;
}

extern "C" IMonster *entryPoint()
{
    return (new sample());
}