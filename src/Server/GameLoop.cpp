/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** GameLoop
*/

#include "GameLoop.hpp"
#include <iostream>

GameLoop::GameLoop()
{
}

void GameLoop::sendUpdates(/*enum type, enum state, posX, posY*/)
{
    int type(0);
    int state(0);
    int posX(0);
    int posY(0);
    std::string toSend("");
    toSend += std::to_string(type) + "\n";
    toSend += std::to_string(state) + "\n";
    toSend += std::to_string(posX) + "." + std::to_string(posY);
    std::cout << "DEBUG: \"" + toSend + "\" will be sent to client.\n";
}

GameLoop::~GameLoop()
{
}
