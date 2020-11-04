/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Lobby.cpp
*/

#include "Lobby.hpp"
#include <thread>
#include <iostream>
#include "gameLoop.hpp"

Lobby::Lobby() : _uuid(boost::uuids::random_generator()()), _state(FREE)
{
    _available.push(Client::P1);
    _available.push(Client::P2);
    _available.push(Client::P3);
    _available.push(Client::P4);
}

void Lobby::addClient(std::shared_ptr<Client>& client)
{
    client->setPlayer(_available.front());
    _available.pop();
    _clients.push_back(client);
}

bool Lobby::isReadyToGo()
{
    for (auto& client: _clients)
        if (client->getState() != Client::READY)
            return (false);
    return (true);
}

void Lobby::startGame(const std::shared_ptr<boost::asio::ip::udp::socket>& socket, const std::shared_ptr<Buffer>& buffer)
{
    auto game = std::make_shared<gameLoop>();

    _state = INGAME;
    for (auto clt = _clients.begin(); clt != _clients.end(); clt++) {
        socket->async_send_to(boost::asio::buffer("/Started"), (*clt)->getEndpoint(),
        boost::bind(&Lobby::handleSend, this, "/Started",
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
        (*clt)->setState(Client::INGAME);
    }
    game->prepareGame(_clients, socket, buffer);
    std::thread test(&gameLoop::run, game, std::ref(_clients), std::ref(_state));
    test.detach();
    // game->run(_clients);
}

boost::uuids::uuid& Lobby::getUuid()
{
    return (_uuid);
}

void Lobby::removeClient(const boost::uuids::uuid& uuid)
{
    for (auto clt = _clients.begin(); clt != _clients.end(); clt++) {
        if ((*clt)->getUuid() == uuid) {
            _available.push((*clt)->getPlayer());
            (*clt)->setPlayer(Client::SPEC);
            _clients.erase(clt);
        }
    }
}

bool Lobby::isRoomFull()
{
    if (_clients.size() >= 4)
        return (true);    
    return (false);
}

void Lobby::handleSend(const std::string& message, const boost::system::error_code& error, std::size_t bytesTransferred)
{
    (void)message;
    (void)error;
    (void)bytesTransferred;
}

bool Lobby::hasClient(const std::shared_ptr<Client>& client)
{
    for (auto& clt : _clients)
        if (client == clt)
            return (true);
    return (false);
}