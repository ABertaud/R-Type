/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Lobby.cpp
*/

#include "Lobby.hpp"
#include <iostream>

Lobby::Lobby(const std::shared_ptr<buffer>& buffer) : _uuid(boost::uuids::random_generator()()), _buffer(buffer)
{
}

void Lobby::addClient(std::shared_ptr<Client>& client)
{
    _clients.push_back(client);
}

bool Lobby::isReadyToGo()
{
    for (auto& client: _clients)
        if (client->getState() != Client::READY)
            return (false);
    return (true);
}

void Lobby::startGame()
{
    std::cout << "gameStart" << std::endl;
    for (auto clt = _clients.begin(); clt != _clients.end(); clt++) {
        (*clt)->setState(Client::INGAME);
    }
}

boost::uuids::uuid& Lobby::getUuid()
{
    return (_uuid);
}

void Lobby::removeClient(const boost::uuids::uuid& uuid)
{
    for (auto clt = _clients.begin(); clt != _clients.end(); clt++) {
        if ((*clt)->getUuid() == uuid)
            _clients.erase(clt);
    }
}