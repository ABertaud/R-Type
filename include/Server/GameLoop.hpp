/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** GameLoop
*/

#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

#include "Client.hpp"
#include "buffer.hpp"

class GameLoop {
    public:
        GameLoop();
        void sendUpdates(/*enum type, enum state, posX, posY*/);
        ~GameLoop();

    protected:
    private:
};

#endif /* !GAMELOOP_HPP_ */
