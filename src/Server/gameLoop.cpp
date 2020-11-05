/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** gameLoop.cpp
*/

#include "gameLoop.hpp"
#include "movementSystem.hpp"
#include "eventSystem.hpp"
#include "routineSystem.hpp"
#include "winSystem.hpp"
#include "Zipper.hpp"
#include <iostream>

gameLoop::gameLoop() : _end(std::make_shared<bool>())
{
}

void gameLoop::registerComponents()
{
    _engine.registerComponent<ECS::Position>(ECS::POSITION);
    _engine.registerComponent<ECS::Velocity>(ECS::VELOCITY);
    _engine.registerComponent<ECS::Player>(ECS::PLAYER);
    _engine.registerComponent<ECS::entityDetails>(ECS::ENTITY_DETAILS);
    _engine.registerComponent<ECS::Life>(ECS::LIFE);
}

void gameLoop::registerSystems(std::vector<std::shared_ptr<Client>>& clients, std::vector<std::shared_ptr<Client::playerNumber>>& players, const std::shared_ptr<boost::asio::ip::udp::socket>& socket, const std::shared_ptr<Buffer>& buffer)
{
    _engine.registerSystem<ECS::movementSystem>();
    _engine.registerSystem<ECS::routineSystem>(socket, clients, players);
    _engine.registerSystem<ECS::eventSystem>(buffer);
    _engine.registerSystem<ECS::winSystem>(_end);
}

void gameLoop::prepareGame(std::vector<std::shared_ptr<Client>>& clients, std::vector<std::shared_ptr<Client::playerNumber>>& players, const std::shared_ptr<boost::asio::ip::udp::socket>& socket, const std::shared_ptr<Buffer>& buffer)
{
    registerComponents();
    registerSystems(clients, players, socket, buffer);
    createPlayers(clients, players);
}

void gameLoop::run(std::vector<std::shared_ptr<Client>>& clients, std::vector<std::shared_ptr<Client::playerNumber>>& players, Lobby::lobbyState &lobbyState)
{
    static std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::seconds time;
    unsigned int playerIndex = 0;

    while (*_end == false) {
        end = std::chrono::system_clock::now();
        time = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        if (time >= std::chrono::seconds(1)) {
            update(time.count());
            start = std::chrono::system_clock::now();
        }
    }
    for (auto clt = clients.begin(); clt != clients.end() && playerIndex != players.size(); clt++, playerIndex++) {
        if (*players.at(playerIndex) != Client::SPEC)
            (*clt)->setState(Client::INLOBBY);
        else {
            (*clt)->setState(Client::NONE);
            clients.erase(clt);
            players.erase(players.begin() + playerIndex);
            clt--;
            playerIndex--;
        }
    }
    lobbyState = Lobby::FREE;
}

void gameLoop::update(const float dt)
{
    for (auto& system : _engine.getSystems())
        system->update(dt, _engine);
}

void gameLoop::createPlayers(std::vector<std::shared_ptr<Client>>& clients, std::vector<std::shared_ptr<Client::playerNumber>>& players)
{
    int x = 50;
    int y = 200;

      for (auto it : Zipper::zip(clients, players)) {
        auto ent = _engine.getNewEntity();
        unsigned int pNumber = *it.get<1>();
        _engine.addComponent(ent, ECS::Position(x, y), ECS::POSITION);
        _engine.addComponent(ent, ECS::Velocity(30, 30), ECS::VELOCITY);
        _engine.addComponent(ent, ECS::Player(*it.get<1>(), it.get<0>()->getUuid()), ECS::PLAYER);
        _engine.addComponent(ent, ECS::entityDetails(static_cast<entityType>(pNumber), entityState::BASIC), ECS::ENTITY_DETAILS);
        _engine.addComponent(ent, ECS::Life(3), ECS::LIFE);
    }
}