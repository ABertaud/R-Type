/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** gameLoop.cpp
*/

#include "gameLoop.hpp"
#include <iostream>

gameLoop::gameLoop()
{
}

void gameLoop::registerComponents()
{
    _engine.registerComponent<ECS::Position>(ECS::POSITION);
    _engine.registerComponent<ECS::Velocity>(ECS::VELOCITY);
    _engine.registerComponent<ECS::Player>(ECS::PLAYER);
    _engine.registerComponent<ECS::entityDetails>(ECS::ENTITY_DETAILS);
}

void gameLoop::registerSystems(std::vector<std::shared_ptr<Client>>& clients, const std::shared_ptr<boost::asio::ip::udp::socket>& socket, const std::shared_ptr<Buffer>& buffer)
{
    _engine.registerSystem<ECS::movementSystem>();
    _engine.registerSystem<ECS::routineSystem>(socket, clients);
    _engine.registerSystem<ECS::eventSystem>(buffer);
}

void gameLoop::prepareGame(std::vector<std::shared_ptr<Client>>& clients, const std::shared_ptr<boost::asio::ip::udp::socket>& socket, const std::shared_ptr<Buffer>& buffer)
{
    registerComponents();
    registerSystems(clients, socket, buffer);
    createPlayers(clients);
}

void gameLoop::run(std::vector<std::shared_ptr<Client>>& clients, Lobby::lobbyState &lobbyState)
{

    static std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> end;
    std::chrono::seconds time;

    while (1) {
        end = std::chrono::system_clock::now();
        time = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        if (time >= std::chrono::seconds(1)) {
            update(time.count());
            start = std::chrono::system_clock::now();
        }
    }
    for (auto& clt : clients)
        clt->setState(Client::INLOBBY);
    lobbyState = Lobby::FREE;
}

void gameLoop::update(const float dt)
{
    for (auto& system : _engine.getSystems())
        system->update(dt, _engine);
}

void gameLoop::createPlayers(std::vector<std::shared_ptr<Client>>& clients)
{
    int x = 50;
    int y = 200;

    for (auto& clt : clients) {
        auto ent = _engine.getNewEntity();
        unsigned int pNumber = clt->getPlayer();
        _engine.addComponent(ent, ECS::Position(x, y), ECS::POSITION);
        _engine.addComponent(ent, ECS::Velocity(30, 30), ECS::VELOCITY);
        _engine.addComponent(ent, ECS::Player(clt->getPlayer()), ECS::PLAYER);
        _engine.addComponent(ent, ECS::entityDetails(static_cast<entityType>(pNumber), entityState::BASIC), ECS::ENTITY_DETAILS);
    }
}