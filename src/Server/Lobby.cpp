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
#include "Zipper.hpp"
#include "boost/uuid/uuid_io.hpp"

Lobby::Lobby() : _uuid(boost::uuids::random_generator()()), _state(FREE)
{
    _available.push(Client::P1);
    _available.push(Client::P2);
    _available.push(Client::P3);
    _available.push(Client::P4);
}

void Lobby::addClient(std::shared_ptr<Client>& client)
{
    _clients.push_back(client);
    _players.push_back(std::make_shared<Client::playerNumber>(_available.front()));
    _available.pop();
}

bool Lobby::isReadyToGo()
{

    for (auto it : Zipper::zip(_clients, _players)) {
        if (it.get<0>()->getState() != Client::READY && *it.get<1>() != Client::SPEC)
            return (false);
    }
    return (true);
}

void Lobby::startGame(const std::shared_ptr<boost::asio::ip::udp::socket>& socket, const std::shared_ptr<Buffer>& buffer)
{
    auto game = std::make_shared<gameLoop>();
    unsigned int playerIndex = 0;
    _state = INGAME;

    for (auto clt = _clients.begin(); clt != _clients.end(); clt++, playerIndex++) {
        if (*_players.at(playerIndex) == Client::SPEC) {
            _clients.erase(clt);
        } else { 
            socket->async_send_to(boost::asio::buffer("/Started"), (*clt)->getEndpoint(),
            boost::bind(&Lobby::handleSend, this, "/Started",
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
            (*clt)->setState(Client::INGAME);
        }
    }
    game->prepareGame(_clients, _players, socket, buffer);
    std::thread test(&gameLoop::run, game, std::ref(_clients), std::ref(_players), std::ref(_state));
    test.detach();
    // game->run(_clients);
}

boost::uuids::uuid& Lobby::getUuid()
{
    return (_uuid);
}

void Lobby::removeClient(const std::shared_ptr<Client>& client)
{
    unsigned int playerIndex = 0;

    for (auto clt = _clients.begin(); clt != _clients.end(); clt++, playerIndex++) {
        if ((*clt)->getUuid() == client->getUuid()) {
            if ((*clt)->getState() == Client::INGAME) {
                _available.push(*_players.at(playerIndex));
                *_players.at(playerIndex) = Client::SPEC;
            } else {
                _available.push(*_players.at(playerIndex));
                _clients.erase(clt);
                _players.erase(_players.begin() + playerIndex);
                break;
            }
        }
    }
}

bool Lobby::isRoomFull()
{
    if (_available.size() <= 0)
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

Client::playerNumber Lobby::getPlayerNumber(const std::shared_ptr<Client>& client)
{
    for (auto it : Zipper::zip(_clients, _players)) {
        if (it.get<0>() == client)
            return (*it.get<1>());
    }
    return (Client::SPEC);
}

Lobby::lobbyState Lobby::getState() const
{
    return (_state);
}